# encoding: utf-8

# See ./rakelib/*.rake for all tasks.

desc "Same as all"
task :default => :all

desc "Same as framework:install"
task :install => 'framework:install'

desc "Generate and install RDoc/RI"
task :install_doc do
  doc_op = '.ext/rdoc'
  unless File.exist?(doc_op)
    sh "./miniruby -I./lib bin/rdoc --all --ri --op \"#{doc_op}\""
  end
  sh "./miniruby instruby.rb #{INSTRUBY_ARGS} --install=rdoc --rdoc-output=\"#{doc_op}\""
end

desc "Same as macruby:build"
task :macruby => 'macruby:build'

# The old test tasks are now commented since we are switching to RubySpec
# for regression testing. We still add a task to run the VM regression test
# suite, though.
desc "Run the VM regression test suite"
task :test_vm do
  sh "/usr/bin/ruby test_vm.rb"
end
=begin
desc "Run the sample tests"
task :sample_test do
  sh "./miniruby rubytest.rb"
end

desc "Run the unit tests"
task :unit_tests do
  sh "./miniruby test/macruby_runner.rb"
end

desc "Run all tests"
task :test => [:sample_test, :unit_tests]
=end

desc "Clean local and extension build files"
task :clean => ['clean:local', 'clean:ext']

desc "Build MacRuby and extensions"
task :all => [:macruby, :extensions]

desc "Create an archive (GIT only)"
task :git_archive do
  sh "git archive --format=tar --prefix=MacRuby-HEAD/ HEAD | gzip >MacRuby-HEAD.tar.gz"
end

desc "Run all 'known good' specs (task alias for spec:ci)"
task :spec => 'spec:ci'

desc "Run IRB"
task :irb do
  exec './miniruby -I./lib ./bin/irb'
end