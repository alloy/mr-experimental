#! ./miniruby

exit if defined?(CROSS_COMPILING)
load './rbconfig.rb'
include RbConfig

ruby = "./#{CONFIG['ruby_install_name']}#{CONFIG['EXEEXT']}"
unless File.exist? ruby
  print "#{ruby} is not found.\n"
  print "Try `make' first, then `make test', please.\n"
  exit false
end

if File.exist? CONFIG['LIBRUBY_SO']
  case RUBY_PLATFORM
  when /-hpux/
    dldpath = "SHLIB_PATH"
  when /-aix/
    dldpath = "LIBPATH"
  when /-beos/
    dldpath = "LIBRARY_PATH"
  when /-darwin/
    dldpath = "DYLD_LIBRARY_PATH"
  else
    dldpath = "LD_LIBRARY_PATH"
  end
  x = ENV[dldpath]
  x = x ? ".:"+x : "."
  ENV[dldpath] = x
end

if /linux/ =~ RUBY_PLATFORM and File.exist? CONFIG['LIBRUBY_SO']
  ENV["LD_PRELOAD"] = "./#{CONFIG['LIBRUBY_SO']}"
end

$stderr.reopen($stdout)
error = ''

srcdir = File.dirname(__FILE__)
`#{ruby} -I.ext/#{RUBY_PLATFORM} -I#{srcdir}/lib #{srcdir}/sample/test.rb`.each_line do |line|
  if line =~ /^end of test/
    print "\ntest succeeded\n"
    exit true
  end
  error << line if %r:^(sample/test.rb|not): =~ line
end
print error
print "test failed\n"
exit false
