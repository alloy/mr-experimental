#
# OnigEncodingDefine(foo, Foo) = {
#   ..
#   "Shift_JIS", /* Canonical Name */
#   ..
# };
# ENC_ALIAS("SJIS", "Shift_JIS")
# ENC_REPLICATE("Windows-31J", "Shift_JIS")
# ENC_ALIAS("CP932", "Windows-31J")
#

def check_duplication(defs, name, fn, line)
  if defs[name]
    raise ArgumentError, "%s:%d: encoding %s is already registered(%s:%d)" %
      [fn, line, name, *defs[name]]
  else
    defs[name.upcase] = [fn,line]
  end
end

count = 0
lines = []
encodings = []
defs = {}
encdir = ARGV[0]
outhdr = ARGV[1] || 'encdb.h'
Dir.open(encdir) {|d| d.grep(/.+\.[ch]\z/)}.sort_by {|e|
  e.scan(/(\d+)|(\D+)/).map {|n,a| a||[n.size,n.to_i]}.flatten
}.each do |fn|
  open(File.join(encdir,fn)) do |f|
    orig = nil
    name = nil
    f.each_line do |line|
      if (/^OnigEncodingDefine/ =~ line)..(/"(.*?)"/ =~ line)
        if $1
          check_duplication(defs, $1, fn, $.)
          encodings << $1
          count += 1
        end
      else
        case line
        when /^\s*rb_enc_register\(\s*"([^"]+)"/
          count += 1
          line = nil
        when /^ENC_REPLICATE\(\s*"([^"]+)"\s*,\s*"([^"]+)"/
          raise ArgumentError,
          '%s:%d: ENC_REPLICATE: %s is not defined yet. (replica %s)' %
            [fn, $., $2, $1] unless defs[$2.upcase]
          count += 1
        when /^ENC_ALIAS\(\s*"([^"]+)"\s*,\s*"([^"]+)"/
          raise ArgumentError,
          '%s:%d: ENC_ALIAS: %s is not defined yet. (alias %s)' %
            [fn, $., $2, $1] unless defs[$2.upcase]
        when /^ENC_DUMMY\(\s*"([^"]+)"/
          count += 1
        else
          next
        end
        check_duplication(defs, $1, fn, $.)
        lines << line.sub(/;.*/m, ";\n") if line
      end
    end
  end
end

result = encodings.map {|e| %[ENC_DEFINE("#{e}");\n]}.join + lines.join + 
  "\n#define ENCODING_COUNT #{count}\n"
mode = IO::RDWR|IO::CREAT
mode |= IO::BINARY if defined?(IO::BINARY)
open(outhdr, mode) do |f|
  unless f.read == result
    f.rewind
    f.truncate(0)
    f.print result
  end
end
