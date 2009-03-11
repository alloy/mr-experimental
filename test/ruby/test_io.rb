require 'test/unit'
require 'tmpdir'
require 'io/nonblock'
require 'socket'
require 'stringio'
require 'timeout'
require 'tempfile'
require_relative 'envutil'

class TestIO < Test::Unit::TestCase
  def test_gets_rs
    # default_rs
    r, w = IO.pipe
    w.print "aaa\nbbb\n"
    w.close
    assert_equal "aaa\n", r.gets
    assert_equal "bbb\n", r.gets
    assert_nil r.gets
    r.close

    # nil
    r, w = IO.pipe
    w.print "a\n\nb\n\n"
    w.close
    assert_equal "a\n\nb\n\n", r.gets(nil)
    assert_nil r.gets("")
    r.close

    # "\377"
    r, w = IO.pipe('ascii-8bit')
    w.print "\377xyz"
    w.close
    r.binmode
    assert_equal("\377", r.gets("\377"), "[ruby-dev:24460]")
    r.close

    # ""
    r, w = IO.pipe
    w.print "a\n\nb\n\n"
    w.close
    assert_equal "a\n\n", r.gets(""), "[ruby-core:03771]"
    assert_equal "b\n\n", r.gets("")
    assert_nil r.gets("")
    r.close
  end

  # This test cause SEGV.
  def test_ungetc
    r, w = IO.pipe
    w.close
    assert_raise(IOError, "[ruby-dev:31650]") { 20000.times { r.ungetc "a" } }
  ensure
    r.close
  end

  def test_each_byte
    r, w = IO.pipe
    w << "abc def"
    w.close
    r.each_byte {|byte| break if byte == 32 }
    assert_equal("def", r.read, "[ruby-dev:31659]")
  ensure
    r.close
  end

  def test_rubydev33072
    assert_raise(Errno::ENOENT, "[ruby-dev:33072]") do
      File.read("empty", nil, nil, {})
    end
  end

  def with_pipe
    r, w = IO.pipe
    begin
      yield r, w
    ensure
      r.close unless r.closed?
      w.close unless w.closed?
    end
  end

  def with_read_pipe(content)
    r, w = IO.pipe
    w << content
    w.close
    begin
      yield r
    ensure
      r.close
    end
  end

  def mkcdtmpdir
    Dir.mktmpdir {|d|
      Dir.chdir(d) {
        yield
      }
    }
  end

  def test_copy_stream
    mkcdtmpdir {|d|

      content = "foobar"
      File.open("src", "w") {|f| f << content }
      ret = IO.copy_stream("src", "dst")
      assert_equal(content.bytesize, ret)
      assert_equal(content, File.read("dst"))

      # overwrite by smaller file.
      content = "baz"
      File.open("src", "w") {|f| f << content }
      ret = IO.copy_stream("src", "dst")
      assert_equal(content.bytesize, ret)
      assert_equal(content, File.read("dst"))

      ret = IO.copy_stream("src", "dst", 2)
      assert_equal(2, ret)
      assert_equal(content[0,2], File.read("dst"))

      ret = IO.copy_stream("src", "dst", 0)
      assert_equal(0, ret)
      assert_equal("", File.read("dst"))

      ret = IO.copy_stream("src", "dst", nil, 1)
      assert_equal(content.bytesize-1, ret)
      assert_equal(content[1..-1], File.read("dst"))

      assert_raise(Errno::ENOENT) {
        IO.copy_stream("nodir/foo", "dst")
      }

      assert_raise(Errno::ENOENT) {
        IO.copy_stream("src", "nodir/bar")
      }

      with_pipe {|r, w|
        ret = IO.copy_stream("src", w)
        assert_equal(content.bytesize, ret)
        w.close
        assert_equal(content, r.read)
      }

      with_pipe {|r, w|
        w.close
        assert_raise(IOError) { IO.copy_stream("src", w) }
      }

      pipe_content = "abc"
      with_read_pipe(pipe_content) {|r|
        ret = IO.copy_stream(r, "dst")
        assert_equal(pipe_content.bytesize, ret)
        assert_equal(pipe_content, File.read("dst"))
      }

      with_read_pipe("abc") {|r1|
        assert_equal("a", r1.getc)
        with_pipe {|r2, w2|
          w2.sync = false
          w2 << "def"
          ret = IO.copy_stream(r1, w2)
          assert_equal(2, ret)
          w2.close
          assert_equal("defbc", r2.read)
        }
      }

      with_read_pipe("abc") {|r1|
        assert_equal("a", r1.getc)
        with_pipe {|r2, w2|
          w2.sync = false
          w2 << "def"
          ret = IO.copy_stream(r1, w2, 1)
          assert_equal(1, ret)
          w2.close
          assert_equal("defb", r2.read)
        }
      }

      with_read_pipe("abc") {|r1|
        assert_equal("a", r1.getc)
        with_pipe {|r2, w2|
          ret = IO.copy_stream(r1, w2)
          assert_equal(2, ret)
          w2.close
          assert_equal("bc", r2.read)
        }
      }

      with_read_pipe("abc") {|r1|
        assert_equal("a", r1.getc)
        with_pipe {|r2, w2|
          ret = IO.copy_stream(r1, w2, 1)
          assert_equal(1, ret)
          w2.close
          assert_equal("b", r2.read)
        }
      }

      with_read_pipe("abc") {|r1|
        assert_equal("a", r1.getc)
        with_pipe {|r2, w2|
          ret = IO.copy_stream(r1, w2, 0)
          assert_equal(0, ret)
          w2.close
          assert_equal("", r2.read)
        }
      }

      with_pipe {|r1, w1|
        w1 << "abc"
        assert_equal("a", r1.getc)
        with_pipe {|r2, w2|
          w1 << "def"
          w1.close
          ret = IO.copy_stream(r1, w2)
          assert_equal(5, ret)
          w2.close
          assert_equal("bcdef", r2.read)
        }
      }

      with_pipe {|r, w|
        ret = IO.copy_stream("src", w, 1, 1)
        assert_equal(1, ret)
        w.close
        assert_equal(content[1,1], r.read)
      }

      with_read_pipe("abc") {|r1|
        assert_equal("a", r1.getc)
        with_pipe {|r2, w2|
          w2.nonblock = true
          s = w2.syswrite("a" * 100000)
          t = Thread.new { sleep 0.1; r2.read }
          ret = IO.copy_stream(r1, w2)
          w2.close
          assert_equal(2, ret)
          assert_equal("a" * s + "bc", t.value)
        }
      }

      bigcontent = "abc" * 123456
      File.open("bigsrc", "w") {|f| f << bigcontent }
      ret = IO.copy_stream("bigsrc", "bigdst")
      assert_equal(bigcontent.bytesize, ret)
      assert_equal(bigcontent, File.read("bigdst"))

      File.unlink("bigdst")
      ret = IO.copy_stream("bigsrc", "bigdst", nil, 100)
      assert_equal(bigcontent.bytesize-100, ret)
      assert_equal(bigcontent[100..-1], File.read("bigdst"))

      File.unlink("bigdst")
      ret = IO.copy_stream("bigsrc", "bigdst", 30000, 100)
      assert_equal(30000, ret)
      assert_equal(bigcontent[100, 30000], File.read("bigdst"))

      File.open("bigsrc") {|f|
        assert_equal(0, f.pos)
        ret = IO.copy_stream(f, "bigdst", nil, 10)
        assert_equal(bigcontent.bytesize-10, ret)
        assert_equal(bigcontent[10..-1], File.read("bigdst"))
        assert_equal(0, f.pos)
        ret = IO.copy_stream(f, "bigdst", 40, 30)
        assert_equal(40, ret)
        assert_equal(bigcontent[30, 40], File.read("bigdst"))
        assert_equal(0, f.pos)
      }

      with_pipe {|r, w|
        w.close
        assert_raise(IOError) { IO.copy_stream("src", w) }
      }

      megacontent = "abc" * 1234567
      File.open("megasrc", "w") {|f| f << megacontent }

      with_pipe {|r1, w1|
        with_pipe {|r2, w2|
          t1 = Thread.new { w1 << megacontent; w1.close }
          t2 = Thread.new { r2.read }
          r1.nonblock = true
          w2.nonblock = true
          ret = IO.copy_stream(r1, w2)
          assert_equal(megacontent.bytesize, ret)
          w2.close
          t1.join
          assert_equal(megacontent, t2.value)
        }
      }

      with_pipe {|r1, w1|
        with_pipe {|r2, w2|
          t1 = Thread.new { w1 << megacontent; w1.close }
          t2 = Thread.new { r2.read }
          ret = IO.copy_stream(r1, w2)
          assert_equal(megacontent.bytesize, ret)
          w2.close
          t1.join
          assert_equal(megacontent, t2.value)
        }
      }

      with_pipe {|r, w|
        t = Thread.new { r.read }
        ret = IO.copy_stream("megasrc", w)
        assert_equal(megacontent.bytesize, ret)
        w.close
        assert_equal(megacontent, t.value)
      }
    }
  end

  def test_copy_stream_rbuf
    mkcdtmpdir {|d|
      with_pipe {|r, w|
        File.open("foo", "w") {|f| f << "abcd" }
        File.open("foo") {|f|
          f.read(1)
          assert_equal(3, IO.copy_stream(f, w, 10, 1))
        }
        w.close
        assert_equal("bcd", r.read)
      }
    }
  end

  def with_socketpair
    s1, s2 = UNIXSocket.pair
    begin
      yield s1, s2
    ensure
      s1.close unless s1.closed?
      s2.close unless s2.closed?
    end
  end

  def test_copy_stream_socket
    return unless defined? UNIXSocket
    mkcdtmpdir {|d|

      content = "foobar"
      File.open("src", "w") {|f| f << content }

      with_socketpair {|s1, s2|
        ret = IO.copy_stream("src", s1)
        assert_equal(content.bytesize, ret)
        s1.close
        assert_equal(content, s2.read)
      }

      bigcontent = "abc" * 123456
      File.open("bigsrc", "w") {|f| f << bigcontent }

      with_socketpair {|s1, s2|
        t = Thread.new { s2.read }
        ret = IO.copy_stream("bigsrc", s1)
        assert_equal(bigcontent.bytesize, ret)
        s1.close
        result = t.value
        assert_equal(bigcontent, result)
      }

      with_socketpair {|s1, s2|
        t = Thread.new { s2.read }
        ret = IO.copy_stream("bigsrc", s1, 10000)
        assert_equal(10000, ret)
        s1.close
        result = t.value
        assert_equal(bigcontent[0,10000], result)
      }

      File.open("bigsrc") {|f|
        assert_equal(0, f.pos)
        with_socketpair {|s1, s2|
          t = Thread.new { s2.read }
          ret = IO.copy_stream(f, s1, nil, 100)
          assert_equal(bigcontent.bytesize-100, ret)
          assert_equal(0, f.pos)
          s1.close
          result = t.value
          assert_equal(bigcontent[100..-1], result)
        }
      }

      File.open("bigsrc") {|f|
        assert_equal(bigcontent[0,100], f.read(100))
        assert_equal(100, f.pos)
        with_socketpair {|s1, s2|
          t = Thread.new { s2.read }
          ret = IO.copy_stream(f, s1)
          assert_equal(bigcontent.bytesize-100, ret)
          assert_equal(bigcontent.length, f.pos)
          s1.close
          result = t.value
          assert_equal(bigcontent[100..-1], result)
        }
      }

      megacontent = "abc" * 1234567
      File.open("megasrc", "w") {|f| f << megacontent }

      with_socketpair {|s1, s2|
        t = Thread.new { s2.read }
        s1.nonblock = true
        ret = IO.copy_stream("megasrc", s1)
        assert_equal(megacontent.bytesize, ret)
        s1.close
        result = t.value
        assert_equal(megacontent, result)
      }
    }
  end

  def test_copy_stream_strio
    src = StringIO.new("abcd")
    dst = StringIO.new
    ret = IO.copy_stream(src, dst)
    assert_equal(4, ret)
    assert_equal("abcd", dst.string)
    assert_equal(4, src.pos)
  end

  def test_copy_stream_strio_len
    src = StringIO.new("abcd")
    dst = StringIO.new
    ret = IO.copy_stream(src, dst, 3)
    assert_equal(3, ret)
    assert_equal("abc", dst.string)
    assert_equal(3, src.pos)
  end

  def test_copy_stream_strio_off
    src = StringIO.new("abcd")
    with_pipe {|r, w|
      assert_raise(ArgumentError) {
        IO.copy_stream(src, w, 3, 1)
      }
    }
  end

  def test_copy_stream_fname_to_strio
    mkcdtmpdir {|d|
      File.open("foo", "w") {|f| f << "abcd" }
      src = "foo"
      dst = StringIO.new
      ret = IO.copy_stream(src, dst, 3)
      assert_equal(3, ret)
      assert_equal("abc", dst.string)
    }
  end

  def test_copy_stream_strio_to_fname
    mkcdtmpdir {|d|
      # StringIO to filename
      src = StringIO.new("abcd")
      ret = IO.copy_stream(src, "fooo", 3)
      assert_equal(3, ret)
      assert_equal("abc", File.read("fooo"))
      assert_equal(3, src.pos)
    }
  end

  def test_copy_stream_io_to_strio
    mkcdtmpdir {|d|
      # IO to StringIO
      File.open("bar", "w") {|f| f << "abcd" }
      File.open("bar") {|src|
        dst = StringIO.new
        ret = IO.copy_stream(src, dst, 3)
        assert_equal(3, ret)
        assert_equal("abc", dst.string)
        assert_equal(3, src.pos)
      }
    }
  end

  def test_copy_stream_strio_to_io
    mkcdtmpdir {|d|
      # StringIO to IO
      src = StringIO.new("abcd")
      ret = File.open("baz", "w") {|dst|
        IO.copy_stream(src, dst, 3)
      }
      assert_equal(3, ret)
      assert_equal("abc", File.read("baz"))
      assert_equal(3, src.pos)
    }
  end

  def test_copy_stream_strio_flush
    with_pipe {|r, w|
      w.sync = false
      w.write "zz"
      src = StringIO.new("abcd")
      IO.copy_stream(src, w)
      t = Thread.new {
        w.close
      }
      assert_equal("zzabcd", r.read)
      t.join
    }
  end

  def test_copy_stream_strio_rbuf
    with_pipe {|r, w|
      w << "abcd"
      w.close
      assert_equal("a", r.read(1))
      sio = StringIO.new
      IO.copy_stream(r, sio)
      assert_equal("bcd", sio.string)
    }
  end

  def test_copy_stream_src_wbuf
    mkcdtmpdir {|d|
      with_pipe {|r, w|
        File.open("foe", "w+") {|f|
          f.write "abcd\n"
          f.rewind
          f.write "xy"
          IO.copy_stream(f, w)
        }
        assert_equal("xycd\n", File.read("foe"))
        w.close
        assert_equal("cd\n", r.read)
        r.close
      }
    }
  end

  def test_copy_stream_dst_rbuf
    mkcdtmpdir {|d|
      with_pipe {|r, w|
        w << "xyz"
        w.close
        File.open("fom", "w+") {|f|
          f.write "abcd\n"
          f.rewind
          assert_equal("abc", f.read(3))
          f.ungetc "c"
          IO.copy_stream(r, f)
        }
        assert_equal("abxyz", File.read("fom"))
      }
    }
  end

  def safe_4
    Thread.new do
      Timeout.timeout(10) do
        $SAFE = 4
        yield
      end
    end.join
  end

  def pipe
    r, w = IO.pipe
    Timeout.timeout(10) do
      yield(r, w)
    end
  ensure
    r.close unless !r || r.closed?
    w.close unless !w || w.closed?
  end

  def pipe2(&b)
    a = []
    a << IO.pipe while true
  rescue Errno::EMFILE, Errno::ENFILE, Errno::ENOMEM
    yield(*a.last)
  ensure
    a.each do |r, w|
      r.close unless !r || r.closed?
      w.close unless !w || w.closed?
    end
  end

  def ruby(*args)
    args = ['-e', '$>.write($<.read)'] if args.empty?
    ruby = EnvUtil.rubybin
    f = IO.popen([ruby] + args, 'r+')
    yield(f)
  ensure
    f.close unless !f || f.closed?
  end

  def test_try_convert
    assert_equal(STDOUT, IO.try_convert(STDOUT))
    assert_equal(nil, IO.try_convert("STDOUT"))
  end

  def test_ungetc2
    pipe do |r, w|
      r.ungetc("0" * 10000)
      w.write("1" * 10000)
      w.close
      assert_equal("0" * 10000 + "1" * 10000, r.read)
    end
  end

  def test_write_non_writable
    pipe do |r, w|
      assert_raise(IOError) do
        r.write "foobarbaz"
      end
    end
  end

  def test_dup
    ruby do |f|
      f2 = f.dup
      f.puts "foo"
      f2.puts "bar"
      f.close_write
      f2.close_write
      assert_equal("foo\nbar\n", f.read)
      assert_equal("", f2.read)
    end

    pipe2 do |r, w|
      assert_raise(Errno::EMFILE, Errno::ENFILE, Errno::NOMEM) do
        r2, w2 = r.dup, w.dup
      end
    end
  end

  def test_inspect
    pipe do |r, w|
      assert(r.inspect =~ /^#<IO:0x[0-9a-f]+>$/)
      assert_raise(SecurityError) do
        safe_4 { r.inspect }
      end
    end
  end

  def test_readpartial
    pipe do |r, w|
      w.write "foobarbaz"
      w.close
      assert_raise(ArgumentError) { r.readpartial(-1) }
      assert_equal("fooba", r.readpartial(5))
      r.readpartial(5, s = "")
      assert_equal("rbaz", s)
    end
  end

  def test_readpartial_error
    pipe do |r, w|
      s = ""
      t = Thread.new { r.readpartial(5, s) }
      0 until s.size == 5
      s.clear
      w.write "foobarbaz"
      w.close
      assert_raise(RuntimeError) { t.join }
    end
  end

  def test_read
    pipe do |r, w|
      w.write "foobarbaz"
      w.close
      assert_raise(ArgumentError) { r.read(-1) }
      assert_equal("fooba", r.read(5))
      r.read(nil, s = "")
      assert_equal("rbaz", s)
    end
  end

  def test_read_error
    pipe do |r, w|
      s = ""
      t = Thread.new { r.read(5, s) }
      0 until s.size == 5
      s.clear
      w.write "foobarbaz"
      w.close
      assert_raise(RuntimeError) { t.join }
    end
  end

  def test_write_nonblock
    pipe do |r, w|
      w.write_nonblock(1)
      w.close
      assert_equal("1", r.read)
    end
  end

  def test_gets
    pipe do |r, w|
      w.write "foobarbaz"
      w.close
      assert_equal("", r.gets(0))
      assert_equal("foobarbaz", r.gets(9))
    end
  end

  def test_close_read
    ruby do |f|
      f.close_read
      f.write "foobarbaz"
      assert_raise(IOError) { f.read }
    end
  end

  def test_close_read_pipe
    pipe do |r, w|
      r.close_read
      assert_raise(Errno::EPIPE) { w.write "foobarbaz" }
    end
  end

  def test_close_read_security_error
    pipe do |r, w|
      assert_raise(SecurityError) do
        safe_4 { r.close_read }
      end
    end
  end

  def test_close_read_non_readable
    pipe do |r, w|
      assert_raise(IOError) do
        w.close_read
      end
    end
  end

  def test_close_write
    ruby do |f|
      f.write "foobarbaz"
      f.close_write
      assert_equal("foobarbaz", f.read)
    end
  end

  def test_close_write_security_error
    pipe do |r, w|
      assert_raise(SecurityError) do
        safe_4 { r.close_write }
      end
    end
  end

  def test_close_write_non_readable
    pipe do |r, w|
      assert_raise(IOError) do
        r.close_write
      end
    end
  end

  def test_pid
    r, w = IO.pipe
    assert_equal(nil, r.pid)
    assert_equal(nil, w.pid)

    pipe = IO.popen(EnvUtil.rubybin, "r+")
    pid1 = pipe.pid
    pipe.puts "p $$"
    pipe.close_write
    pid2 = pipe.read.chomp.to_i
    assert_equal(pid2, pid1)
    assert_equal(pid2, pipe.pid)
    pipe.close
    assert_raise(IOError) { pipe.pid }
  end

  def make_tempfile
    t = Tempfile.new("foo")
    t.puts "foo"
    t.puts "bar"
    t.puts "baz"
    t.close
    t
  end

  def test_set_lineno
    t = make_tempfile

    ruby("-e", <<-SRC, t.path) do |f|
      open(ARGV[0]) do |f|
        p $.
        f.gets; p $.
        f.gets; p $.
        f.lineno = 1000; p $.
        f.gets; p $.
        f.gets; p $.
        f.rewind; p $.
        f.gets; p $.
        f.gets; p $.
        f.gets; p $.
        f.gets; p $.
      end
    SRC
      assert_equal("nil,1,2,2,1001,1001,1001,1,2,3,3", f.read.chomp.gsub("\n", ","))
    end

    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      r.gets; assert_equal(1, $.)
      r.gets; assert_equal(2, $.)
      r.lineno = 1000; assert_equal(2, $.)
      r.gets; assert_equal(1001, $.)
      r.gets; assert_equal(1001, $.)
    end
  end

  def test_readline
    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      r.readline; assert_equal(1, $.)
      r.readline; assert_equal(2, $.)
      r.lineno = 1000; assert_equal(2, $.)
      r.readline; assert_equal(1001, $.)
      assert_raise(EOFError) { r.readline }
    end
  end

  def test_each_char
    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      a = []
      r.each_char {|c| a << c }
      assert_equal(%w(f o o) + ["\n"] + %w(b a r) + ["\n"] + %w(b a z) + ["\n"], a)
    end
  end

  def test_lines
    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      e = r.lines
      assert_equal("foo\n", e.next)
      assert_equal("bar\n", e.next)
      assert_equal("baz\n", e.next)
      assert_raise(StopIteration) { e.next }
    end
  end

  def test_bytes
    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      e = r.bytes
      (%w(f o o) + ["\n"] + %w(b a r) + ["\n"] + %w(b a z) + ["\n"]).each do |c|
        assert_equal(c.ord, e.next)
      end
      assert_raise(StopIteration) { e.next }
    end
  end

  def test_chars
    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      e = r.chars
      (%w(f o o) + ["\n"] + %w(b a r) + ["\n"] + %w(b a z) + ["\n"]).each do |c|
        assert_equal(c, e.next)
      end
      assert_raise(StopIteration) { e.next }
    end
  end

  def test_readbyte
    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      (%w(f o o) + ["\n"] + %w(b a r) + ["\n"] + %w(b a z) + ["\n"]).each do |c|
        assert_equal(c.ord, r.readbyte)
      end
      assert_raise(EOFError) { r.readbyte }
    end
  end

  def test_readchar
    pipe do |r, w|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      (%w(f o o) + ["\n"] + %w(b a r) + ["\n"] + %w(b a z) + ["\n"]).each do |c|
        assert_equal(c, r.readchar)
      end
      assert_raise(EOFError) { r.readchar }
    end
  end

  def test_close_on_exec
    # xxx
    ruby do |f|
      assert_equal(false, f.close_on_exec?)
      f.close_on_exec = true
      assert_equal(true, f.close_on_exec?)
      f.close_on_exec = false
      assert_equal(false, f.close_on_exec?)
    end

    pipe do |r, w|
      assert_equal(false, r.close_on_exec?)
      r.close_on_exec = true
      assert_equal(true, r.close_on_exec?)
      r.close_on_exec = false
      assert_equal(false, r.close_on_exec?)

      assert_equal(false, w.close_on_exec?)
      w.close_on_exec = true
      assert_equal(true, w.close_on_exec?)
      w.close_on_exec = false
      assert_equal(false, w.close_on_exec?)
    end
  end

  def test_close_security_error
    pipe do |r, w|
      assert_raise(SecurityError) do
        safe_4 { r.close }
      end
    end
  end

  def test_sysseek
    t = make_tempfile

    open(t.path) do |f|
      f.sysseek(-4, IO::SEEK_END)
      assert_equal("baz\n", f.read)
    end

    open(t.path) do |f|
      a = [f.getc, f.getc, f.getc]
      a.reverse_each {|c| f.ungetc c }
      assert_raise(IOError) { f.sysseek(1) }
    end
  end

  def test_syswrite
    t = make_tempfile

    open(t.path, "w") do |f|
      o = Object.new
      def o.to_s; "FOO\n"; end
      f.syswrite(o)
    end
    assert_equal("FOO\n", File.read(t.path))
  end

  def test_sysread
    t = make_tempfile

    open(t.path) do |f|
      a = [f.getc, f.getc, f.getc]
      a.reverse_each {|c| f.ungetc c }
      assert_raise(IOError) { f.sysread(1) }
    end
  end

  def test_flag
    t = make_tempfile

    assert_raise(ArgumentError) do
      open(t.path, "z") { }
    end

    assert_raise(ArgumentError) do
      open(t.path, "rr") { }
    end
  end

  def test_sysopen
    t = make_tempfile
    
    fd = IO.sysopen(t.path)
    assert_kind_of(Integer, fd)
    f = IO.for_fd(fd)
    assert_equal("foo\nbar\nbaz\n", f.read)
    f.close
    
    fd = IO.sysopen(t.path, "w", 0666)
    assert_kind_of(Integer, fd)
    f = IO.for_fd(fd)
    f.write("FOO\n")
    f.close
    
    fd = IO.sysopen(t.path, "r")
    assert_kind_of(Integer, fd)
    f = IO.for_fd(fd)
    assert_equal("FOO\n", f.read)
    f.close
  end

  def test_open_redirect
    o = Object.new
    def o.to_open; self; end
    assert_equal(o, open(o))
    o2 = nil
    open(o) do |f|
      o2 = f
    end
    assert_equal(o, o2)
  end

  def test_open_pipe
    open("|" + EnvUtil.rubybin, "r+") do |f|
      f.puts "puts 'foo'"
      f.close_write
      assert_equal("foo\n", f.read)
    end
  end

  def test_reopen
    t = make_tempfile

    pipe do |r, w|
      assert_raise(SecurityError) do
        safe_4 { r.reopen(t.path) }
      end
    end
  end

  def test_foreach
    a = []
    IO.foreach("|" + EnvUtil.rubybin + " -e 'puts :foo; puts :bar; puts :baz'") {|x| a << x }
    assert_equal(["foo\n", "bar\n", "baz\n"], a)

    t = make_tempfile

    a = []
    IO.foreach(t.path, {:mode => "r" }) {|x| a << x }
    assert_equal(["foo\n", "bar\n", "baz\n"], a)

    a = []
    IO.foreach(t.path, {:open_args => [] }) {|x| a << x }
    assert_equal(["foo\n", "bar\n", "baz\n"], a)

    a = []
    IO.foreach(t.path, {:open_args => ["r"] }) {|x| a << x }
    assert_equal(["foo\n", "bar\n", "baz\n"], a)
  end

  def test_printf
    pipe do |r, w|
      printf(w, "foo %s baz\n", "bar")
      w.close_write
      assert_equal("foo bar baz\n", r.read)
    end
  end

  def test_print
    t = make_tempfile

    EnvUtil.rubyexec("-", t.path) do |w, r, e|
      w.puts "print while $<.gets"
      w.close
      assert_equal("", e.read)
      assert_equal("foo\nbar\nbaz\n", r.read)
    end
  end

  def test_putc
    pipe do |r, w|
      w.putc "A"
      w.putc "BC"
      w.putc 68
      w.close_write
      assert_equal("ABD", r.read)
    end

    EnvUtil.rubyexec do |w, r, e|
      w.puts "putc 65"
      w.close
      assert_equal("", e.read)
      assert_equal("A", r.read)
    end
  end

  def test_puts_recursive_array
    a = ["foo"]
    a << a
    pipe do |r, w|
      w.puts a
      w.close
      assert_equal("foo\n[...]\n", r.read)
    end
  end

  def test_display
    pipe do |r, w|
      "foo".display(w)
      w.close
      assert_equal("foo", r.read)
    end

    EnvUtil.rubyexec do |w, r, e|
      w.puts "'foo'.display"
      w.close
      assert_equal("", e.read)
      assert_equal("foo", r.read)
    end
  end

  def test_set_stdout
    assert_raise(TypeError) { $> = Object.new }

    EnvUtil.rubyexec do |w, r, e|
      w.puts "$> = $stderr"
      w.puts "puts 'foo'"
      w.close
      assert_equal("foo\n", e.read)
      assert_equal("", r.read)
    end
  end

  def test_initialize
    t = make_tempfile
    
    fd = IO.sysopen(t.path)
    assert_kind_of(Integer, fd)
    f = IO.new(fd, "w")
    f.write("FOO\n")
    f.close

    assert_equal("foo\nbar\nbaz\n", File.read(t.path))

    pipe do |r, w|
      assert_raise(RuntimeError) do
        o = Object.new
        class << o; self; end.instance_eval do
          define_method(:to_io) { r }
        end
        w.instance_eval { initialize(o) }
      end
    end

    pipe do |r, w|
      r, w = IO.new(r), IO.new(w)
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      assert_equal("foo\nbar\nbaz\n", r.read)
    end

    pipe do |r, w|
      assert_raise(ArgumentError) { IO.new(r, "r+") }
    end

    f = open(t.path)
    assert_raise(RuntimeError) do
      f.instance_eval { initialize }
    end
  end
  
  def test_new_with_block
    EnvUtil.rubyexec do |w, r, e|
      w.puts "r, w = IO.pipe"
      w.puts "IO.new(r) {}"
      w.close
      assert_not_equal("", e.read)
      assert_equal("", r.read)
    end
  end

  def test_readline2
    EnvUtil.rubyexec("-e", <<-SRC) do |w, r, e|
      puts readline
      puts readline
      puts readline
      begin
        puts readline
      rescue EOFError
        puts "end"
      end
    SRC
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      assert_equal("", e.read)
      assert_equal("foo\nbar\nbaz\nend\n", r.read)
    end
  end

  def test_readlines
    EnvUtil.rubyexec("-e", "p readlines") do |w, r, e|
      w.puts "foo"
      w.puts "bar"
      w.puts "baz"
      w.close
      assert_equal("", e.read)
      assert_equal("[\"foo\\n\", \"bar\\n\", \"baz\\n\"]\n", r.read)
    end
  end

  def test_s_read
    t = make_tempfile

    assert_equal("bar\n", File.read(t.path, 4, 4))
  end

  def test_uninitialized
    assert_raise(IOError) { IO.allocate.print "" }
  end
end
