require 'test/unit'
require 'thread'
require_relative 'envutil'

class TestThread < Test::Unit::TestCase
  def ruby(*r, &b)
    EnvUtil.rubyexec(*r, &b)
  end

  class Thread < ::Thread
    Threads = []
    def self.new(*)
      th = super
      th.abort_on_exception = true
      Threads << th
      th
    end
  end

  def setup
    Thread::Threads.clear
  end

  def teardown
    Thread::Threads.each do |t|
      t.kill if t.alive?
      begin
        t.join
      rescue Exception
      end
    end
  end

  def test_mutex_synchronize
    m = Mutex.new
    r = 0
    max = 100
    (1..max).map{
      Thread.new{
        i=0
        while i<max*max
          i+=1
          m.synchronize{
            r += 1
          }
        end
      }
    }.each{|e|
      e.join
    }
    assert_equal(max * max * max, r)
  end

  def test_condvar
    mutex = Mutex.new
    condvar = ConditionVariable.new
    result = []
    mutex.synchronize do
      t = Thread.new do
        mutex.synchronize do
          result << 1
          condvar.signal
        end
      end

      result << 0
      condvar.wait(mutex)
      result << 2
      t.join
    end
    assert_equal([0, 1, 2], result)
  end

  def test_condvar_wait_not_owner
    mutex = Mutex.new
    condvar = ConditionVariable.new

    assert_raises(ThreadError) { condvar.wait(mutex) }
  end

  def test_condvar_wait_exception_handling
    # Calling wait in the only thread running should raise a ThreadError of
    # 'stopping only thread'
    mutex = Mutex.new
    condvar = ConditionVariable.new

    locked = false
    thread = Thread.new do
      Thread.current.abort_on_exception = false
      mutex.synchronize do
        begin
          condvar.wait(mutex)
        rescue Exception
          locked = mutex.locked?
          raise
        end
      end
    end

    until thread.stop?
      sleep(0.1)
    end

    thread.raise Interrupt, "interrupt a dead condition variable"
    assert_raises(Interrupt) { thread.value }
    assert(locked)
  end

  def test_local_barrier
    dir = File.dirname(__FILE__)
    lbtest = File.join(dir, "lbtest.rb")
    $:.unshift File.join(File.dirname(dir), 'ruby')
    require 'envutil'
    $:.shift
    10.times {
      result = `#{EnvUtil.rubybin} #{lbtest}`
      assert(!$?.coredump?, '[ruby-dev:30653]')
      assert_equal("exit.", result[/.*\Z/], '[ruby-dev:30653]')
    }
  end

  def test_priority
    c1 = c2 = 0
    t1 = Thread.new { loop { c1 += 1 } }
    t1.priority = -1
    t2 = Thread.new { loop { c2 += 1 } }
    t2.priority = -3
    assert_equal(-1, t1.priority)
    assert_equal(-3, t2.priority)
    sleep 0.5
    t1.kill
    t2.kill
    assert(c1 > c2 * 2, "[ruby-dev:33124]")
  end

  def test_new
    assert_raise(ThreadError) do
      Thread.new
    end

    t1 = Thread.new { sleep }
    assert_raise(ThreadError) do
      t1.instance_eval { initialize { } }
    end

    t2 = Thread.new(&method(:sleep).to_proc)
    assert_raise(ThreadError) do
      t2.instance_eval { initialize { } }
    end

  ensure
    t1.kill if t1
    t2.kill if t2
  end

  def test_join
    t = Thread.new { sleep }
    assert_nil(t.join(0.5))

  ensure
    t.kill if t
  end

  def test_join2
    t1 = Thread.new { sleep(1.5) }
    t2 = Thread.new do
      t1.join(1)
    end
    t3 = Thread.new do
      sleep 0.5
      t1.join
    end
    assert_nil(t2.value)
    assert_equal(t1, t3.value)

  ensure
    t1.kill if t1
    t2.kill if t2
    t3.kill if t3
  end

  def test_kill_main_thread
    ruby do |w, r, e|
      w.puts "p 1"
      w.puts "Thread.kill Thread.current"
      w.puts "p 2"
      w.close
      assert_equal("1", r.read.chomp)
    end
  end

  def test_exit
    s = 0
    Thread.new do
      s += 1
      Thread.exit
      s += 2
    end.join
    assert_equal(1, s)
  end

  def test_wakeup
    s = 0
    t = Thread.new do
      s += 1
      Thread.stop
      s += 1
    end
    sleep 0.5
    assert_equal(1, s)
    t.wakeup
    sleep 0.5
    assert_equal(2, s)
    assert_raise(ThreadError) { t.wakeup }

  ensure
    t.kill if t
  end

  def test_stop
    ruby do |w, r, e|
      w.puts "begin"
      w.puts "  Thread.stop"
      w.puts "  p 1"
      w.puts "rescue ThreadError"
      w.puts "  p 2"
      w.puts "end"
      w.close
      assert_equal("2", r.read.chomp)
    end
  end

  def test_list
    ruby do |w, r, e|
      w.puts "t1 = Thread.new { sleep }"
      w.puts "t2 = Thread.new { loop { } }"
      w.puts "t3 = Thread.new { }.join"
      w.puts "p [Thread.current, t1, t2].sort_by {|t| t.object_id }"
      w.puts "p Thread.list.sort_by {|t| t.object_id }"
      w.close
      assert_equal(r.gets, r.gets)
    end
  end

  def test_main
    ruby do |w, r, e|
      w.puts "p Thread.main == Thread.current"
      w.puts "Thread.new { p Thread.main == Thread.current }.join"
      w.close
      assert_equal("true", r.gets.chomp)
      assert_equal("false", r.gets.chomp)
    end
  end

  def test_abort_on_exception
    ruby do |w, r, e|
      w.puts "p Thread.abort_on_exception"
      w.puts "begin"
      w.puts "  Thread.new { raise }"
      w.puts "  sleep 0.5"
      w.puts "  p 1"
      w.puts "rescue"
      w.puts "  p 2"
      w.puts "end"
      w.close_write
      assert_equal("false", r.gets.chomp)
      assert_equal("1", r.gets.chomp)
      assert_equal("", e.read)
    end

    ruby do |w, r, e|
      w.puts "Thread.abort_on_exception = true"
      w.puts "p Thread.abort_on_exception"
      w.puts "begin"
      w.puts "  Thread.new { raise }"
      w.puts "  sleep 0.5"
      w.puts "  p 1"
      w.puts "rescue"
      w.puts "  p 2"
      w.puts "end"
      w.close_write
      assert_equal("true", r.gets.chomp)
      assert_equal("2", r.gets.chomp)
      assert_equal("", e.read)
    end

    ruby('-d') do |w, r, e|
      w.puts "p Thread.abort_on_exception"
      w.puts "begin"
      w.puts "  Thread.new { raise }"
      w.puts "  sleep 0.5"
      w.puts "  p 1"
      w.puts "rescue"
      w.puts "  p 2"
      w.puts "end"
      w.close_write
      assert_equal("false", r.gets.chomp)
      assert_equal("2", r.gets.chomp)
      assert_not_equal("", e.read)
    end

    ruby do |w, r, e|
      w.puts "p Thread.abort_on_exception"
      w.puts "begin"
      w.puts "  t = Thread.new { sleep 0.5; raise }"
      w.puts "  t.abort_on_exception = true"
      w.puts "  p t.abort_on_exception"
      w.puts "  sleep 1"
      w.puts "  p 1"
      w.puts "rescue"
      w.puts "  p 2"
      w.puts "end"
      w.close_write
      assert_equal("false", r.gets.chomp)
      assert_equal("true", r.gets.chomp)
      assert_equal("2", r.gets.chomp)
      assert_equal("", e.read)
    end
  end

  def test_status_and_stop_p
    a = ::Thread.new { raise("die now") }
    b = Thread.new { Thread.stop }
    c = Thread.new { Thread.exit }
    d = Thread.new { sleep }
    e = Thread.current
    sleep 0.5
    d.kill

    assert_equal(nil, a.status)
    assert_equal("sleep", b.status)
    assert_equal(false, c.status)
    assert_match(/^#<TestThread::Thread:.* dead>$/, c.inspect)
    assert_equal("aborting", d.status)
    assert_equal("run", e.status)

    assert(a.stop?)
    assert(b.stop?)
    assert(c.stop?)
    assert(!d.stop?)
    assert(!e.stop?)

  ensure
    a.kill if a
    b.kill if b
    c.kill if c
    d.kill if d
  end

  def test_safe_level
    t = Thread.new { $SAFE = 3; sleep }
    sleep 0.5
    assert_equal(0, Thread.current.safe_level)
    assert_equal(3, t.safe_level)

  ensure
    t.kill if t
  end

  def test_thread_local
    t = Thread.new { sleep }

    assert_equal(false, t.key?(:foo))

    t["foo"] = "foo"
    t["bar"] = "bar"
    t["baz"] = "baz"

    assert_equal(true, t.key?(:foo))
    assert_equal(true, t.key?("foo"))
    assert_equal(false, t.key?(:qux))
    assert_equal(false, t.key?("qux"))

    assert_equal([:foo, :bar, :baz], t.keys)

  ensure
    t.kill if t
  end

  def test_thread_local_security
    t = Thread.new { sleep }

    assert_raise(SecurityError) do
      Thread.new { $SAFE = 4; t[:foo] }.join
    end

    assert_raise(SecurityError) do
      Thread.new { $SAFE = 4; t[:foo] = :baz }.join
    end

    assert_raise(RuntimeError) do
      Thread.new do
        Thread.current[:foo] = :bar
        Thread.current.freeze
        Thread.current[:foo] = :baz
      end.join
    end
  end

  def test_select_wait
    assert_nil(IO.select(nil, nil, nil, 1))
    t = Thread.new do
      IO.select(nil, nil, nil, nil)
    end
    sleep 0.5
    t.kill
  end

  def test_mutex_deadlock
    m = Mutex.new
    m.synchronize do
      assert_raise(ThreadError) do
        m.synchronize do
          assert(false)
        end
      end
    end
  end

  def test_mutex_interrupt
    m = Mutex.new
    m.lock
    t = Thread.new do
      m.lock
      :foo
    end
    sleep 0.5
    t.kill
    assert_nil(t.value)
  end

  def test_mutex_illegal_unlock
    m = Mutex.new
    m.lock
    assert_raise(ThreadError) do
      Thread.new do
        m.unlock
      end.join
    end
  end

  def test_recursive_error
    o = Object.new
    def o.inspect
      Thread.current[:__recursive_key__][:inspect] = nil
      super
    end
    assert_raise(TypeError) { [o].inspect }
  end
end

class TestThreadGroup < Test::Unit::TestCase
  def test_thread_init
    thgrp = ThreadGroup.new
    Thread.new{
      thgrp.add(Thread.current)
      assert_equal(thgrp, Thread.new{sleep 1}.group)
    }.join
  end

  def test_frozen_thgroup
    thgrp = ThreadGroup.new

    t = Thread.new{1}
    Thread.new{
      thgrp.add(Thread.current)
      thgrp.freeze
      assert_raise(ThreadError) do
        Thread.new{1}.join
      end
      assert_raise(ThreadError) do
        thgrp.add(t)
      end
      assert_raise(ThreadError) do
        ThreadGroup.new.add Thread.current
      end
    }.join
    t.join
  end

  def test_enclosed_thgroup
    thgrp = ThreadGroup.new
    assert_equal(false, thgrp.enclosed?)

    t = Thread.new{1}
    Thread.new{
      thgrp.add(Thread.current)
      thgrp.enclose
      assert_equal(true, thgrp.enclosed?)
      assert_nothing_raised do
        Thread.new{1}.join
      end
      assert_raise(ThreadError) do
        thgrp.add t
      end
      assert_raise(ThreadError) do
        ThreadGroup.new.add Thread.current
      end
    }.join
    t.join
  end

  def test_uninitialized
    c = Class.new(Thread)
    c.class_eval { def initialize; end }
    assert_raise(ThreadError) { c.new.start }
  end
end
