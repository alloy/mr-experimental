#!/usr/bin/env ruby
#--
# Copyright 2006 by Chad Fowler, Rich Kilmer, Jim Weirich and others.
# All rights reserved.
# See LICENSE.txt for permissions.
#++

require 'test/unit'
require File.join(File.expand_path(File.dirname(__FILE__)), 'gemutilities')
require 'webrick'
require 'zlib'
require 'rubygems/remote_fetcher'

# = Testing Proxy Settings
#
# These tests check the proper proxy server settings by running two
# web servers.  The web server at http://localhost:#{SERVER_PORT}
# represents the normal gem server and returns a gemspec with a rake
# version of 0.4.11.  The web server at http://localhost:#{PROXY_PORT}
# represents the proxy server and returns a different dataset where
# rake has version 0.4.2.  This allows us to detect which server is
# returning the data.
#
# Note that the proxy server is not a *real* proxy server.  But our
# software doesn't really care, as long as we hit the proxy URL when a
# proxy is configured.
#
class TestGemRemoteFetcher < RubyGemTestCase

  include Gem::DefaultUserInteraction

  SERVER_DATA = <<-EOY
--- !ruby/object:Gem::Cache
gems:
  rake-0.4.11: !ruby/object:Gem::Specification
    rubygems_version: "0.7"
    specification_version: 1
    name: rake
    version: !ruby/object:Gem::Version
      version: 0.4.11
    date: 2004-11-12
    summary: Ruby based make-like utility.
    require_paths:
      - lib
    author: Jim Weirich
    email: jim@weirichhouse.org
    homepage: http://rake.rubyforge.org
    rubyforge_project: rake
    description: Rake is a Make-like program implemented in Ruby. Tasks and dependencies are specified in standard Ruby syntax.
    autorequire:
    default_executable: rake
    bindir: bin
    has_rdoc: true
    required_ruby_version: !ruby/object:Gem::Version::Requirement
      requirements:
        -
          - ">"
          - !ruby/object:Gem::Version
            version: 0.0.0
      version:
    platform: ruby
    files:
      - README
    test_files: []
    library_stubs:
    rdoc_options:
    extra_rdoc_files:
    executables:
      - rake
    extensions: []
    requirements: []
    dependencies: []
  EOY

  PROXY_DATA = SERVER_DATA.gsub(/0.4.11/, '0.4.2')

  # don't let 1.8 and 1.9 autotest collide
  RUBY_VERSION =~ /(\d+)\.(\d+)\.(\d+)/
  # don't let parallel runners collide
  PROXY_PORT = process_based_port + 100 + $1.to_i * 100 + $2.to_i * 10 + $3.to_i
  SERVER_PORT = process_based_port + 200 + $1.to_i * 100 + $2.to_i * 10 + $3.to_i

  def setup
    super
    self.class.start_servers
    self.class.enable_yaml = true
    self.class.enable_zip = false
    ENV.delete 'http_proxy'
    ENV.delete 'HTTP_PROXY'
    ENV.delete 'http_proxy_user'
    ENV.delete 'HTTP_PROXY_USER'
    ENV.delete 'http_proxy_pass'
    ENV.delete 'HTTP_PROXY_PASS'

    base_server_uri = "http://localhost:#{SERVER_PORT}"
    @proxy_uri = "http://localhost:#{PROXY_PORT}"

    @server_uri = base_server_uri + "/yaml"
    @server_z_uri = base_server_uri + "/yaml.Z"

    # REFACTOR: copied from test_gem_dependency_installer.rb
    @gems_dir = File.join @tempdir, 'gems'
    @cache_dir = File.join @gemhome, 'cache'
    FileUtils.mkdir @gems_dir

    @a1, @a1_gem = util_gem 'a', '1' do |s| s.executables << 'a_bin' end

    Gem::RemoteFetcher.instance_variable_set :@fetcher, nil
  end

  def test_self_fetcher
    fetcher = Gem::RemoteFetcher.fetcher
    assert_not_nil fetcher
    assert_kind_of Gem::RemoteFetcher, fetcher
  end

  def test_self_fetcher_with_proxy
    proxy_uri = 'http://proxy.example.com'
    Gem.configuration[:http_proxy] = proxy_uri
    fetcher = Gem::RemoteFetcher.fetcher
    assert_not_nil fetcher
    assert_kind_of Gem::RemoteFetcher, fetcher
    assert_equal proxy_uri, fetcher.instance_variable_get(:@proxy_uri).to_s
  end

  def test_self_fetcher_with_proxy_URI
    proxy_uri = URI.parse 'http://proxy.example.com'
    Gem.configuration[:http_proxy] = proxy_uri
    fetcher = Gem::RemoteFetcher.fetcher
    assert_not_nil fetcher
    assert_kind_of Gem::RemoteFetcher, fetcher
    assert_equal proxy_uri, fetcher.instance_variable_get(:@proxy_uri)
  end

  def test_fetch_size_bad_uri
    fetcher = Gem::RemoteFetcher.new nil

    e = assert_raise ArgumentError do
      fetcher.fetch_size 'gems.example.com/yaml'
    end

    assert_equal 'uri is not an HTTP URI', e.message
  end

  def test_fetch_size_socket_error
    fetcher = Gem::RemoteFetcher.new nil
    def fetcher.connect_to(host, port)
      raise SocketError
    end

    uri = 'http://gems.example.com/yaml'
    e = assert_raise Gem::RemoteFetcher::FetchError do
      fetcher.fetch_size uri
    end

    assert_equal "SocketError (SocketError)\n\tgetting size of #{uri}", e.message
  end

  def test_no_proxy
    use_ui @ui do
      fetcher = Gem::RemoteFetcher.new nil
      assert_data_from_server fetcher.fetch_path(@server_uri)
      assert_equal SERVER_DATA.size, fetcher.fetch_size(@server_uri)
    end
  end

  def util_fuck_with_fetcher data, blow = false
    fetcher = Gem::RemoteFetcher.fetcher
    fetcher.instance_variable_set :@test_data, data

    unless blow then
      def fetcher.fetch_path arg
        @test_arg = arg
        @test_data
      end
    else
      def fetcher.fetch_path arg
        # OMG I'm such an ass
        class << self; remove_method :fetch_path; end
        def self.fetch_path arg
          @test_arg = arg
          @test_data
        end

        raise Gem::RemoteFetcher::FetchError, "haha!"
      end
    end

    fetcher
  end

  def test_download
    a1_data = nil
    File.open @a1_gem, 'rb' do |fp|
      a1_data = fp.read
    end

    fetcher = util_fuck_with_fetcher a1_data

    a1_cache_gem = File.join(@gemhome, 'cache', "#{@a1.full_name}.gem")
    assert_equal a1_cache_gem, fetcher.download(@a1, 'http://gems.example.com')
    assert_equal("http://gems.example.com/gems/a-1.gem",
                 fetcher.instance_variable_get(:@test_arg).to_s)
    assert File.exist?(a1_cache_gem)
  end

  def test_download_cached
    FileUtils.mv @a1_gem, @cache_dir

    inst = Gem::RemoteFetcher.fetcher

    assert_equal File.join(@gemhome, 'cache', "#{@a1.full_name}.gem"),
                 inst.download(@a1, 'http://gems.example.com')
  end

  def test_download_local
    FileUtils.mv @a1_gem, @tempdir
    local_path = File.join @tempdir, "#{@a1.full_name}.gem"
    inst = nil

    Dir.chdir @tempdir do
      inst = Gem::RemoteFetcher.fetcher
    end

    assert_equal File.join(@gemhome, 'cache', "#{@a1.full_name}.gem"),
                 inst.download(@a1, local_path)
  end

  def test_download_install_dir
    a1_data = nil
    File.open @a1_gem, 'rb' do |fp|
      a1_data = fp.read
    end

    fetcher = util_fuck_with_fetcher a1_data

    install_dir = File.join @tempdir, 'more_gems'

    a1_cache_gem = File.join install_dir, 'cache', "#{@a1.full_name}.gem"
    actual = fetcher.download(@a1, 'http://gems.example.com', install_dir)

    assert_equal a1_cache_gem, actual
    assert_equal("http://gems.example.com/gems/a-1.gem",
                 fetcher.instance_variable_get(:@test_arg).to_s)

    assert File.exist?(a1_cache_gem)
  end

  unless win_platform? then # File.chmod doesn't work
    def test_download_local_read_only
      FileUtils.mv @a1_gem, @tempdir
      local_path = File.join @tempdir, "#{@a1.full_name}.gem"
      inst = nil
      File.chmod 0555, File.join(@gemhome, 'cache')

      Dir.chdir @tempdir do
        inst = Gem::RemoteFetcher.fetcher
      end

      assert_equal File.join(@tempdir, "#{@a1.full_name}.gem"),
        inst.download(@a1, local_path)
    ensure
      File.chmod 0755, File.join(@gemhome, 'cache')
    end
  end

  def test_download_platform_legacy
    original_platform = 'old-platform'

    e1, e1_gem = util_gem 'e', '1' do |s|
      s.platform = Gem::Platform::CURRENT
      s.instance_variable_set :@original_platform, original_platform
    end

    e1_data = nil
    File.open e1_gem, 'rb' do |fp|
      e1_data = fp.read
    end

    fetcher = util_fuck_with_fetcher e1_data, :blow_chunks

    e1_cache_gem = File.join(@gemhome, 'cache', "#{e1.full_name}.gem")

    assert_equal e1_cache_gem, fetcher.download(e1, 'http://gems.example.com')

    assert_equal("http://gems.example.com/gems/#{e1.original_name}.gem",
                 fetcher.instance_variable_get(:@test_arg).to_s)
    assert File.exist?(e1_cache_gem)
  end

  def test_download_unsupported
    inst = Gem::RemoteFetcher.fetcher

    e = assert_raise Gem::InstallError do
      inst.download @a1, 'ftp://gems.rubyforge.org'
    end

    assert_equal 'unsupported URI scheme ftp', e.message
  end

  def test_explicit_proxy
    use_ui @ui do
      fetcher = Gem::RemoteFetcher.new @proxy_uri
      assert_equal PROXY_DATA.size, fetcher.fetch_size(@server_uri)
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end
  end

  def test_explicit_proxy_with_user_auth
    use_ui @ui do
      uri = URI.parse @proxy_uri
      uri.user, uri.password = 'foo', 'bar'
      fetcher = Gem::RemoteFetcher.new uri.to_s
      proxy = fetcher.instance_variable_get("@proxy_uri")
      assert_equal 'foo', proxy.user
      assert_equal 'bar', proxy.password
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end

    use_ui @ui do
      uri = URI.parse @proxy_uri
      uri.user, uri.password = 'domain%5Cuser', 'bar'
      fetcher = Gem::RemoteFetcher.new uri.to_s
      proxy = fetcher.instance_variable_get("@proxy_uri")
      assert_equal 'domain\user', URI.unescape(proxy.user)
      assert_equal 'bar', proxy.password
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end

    use_ui @ui do
      uri = URI.parse @proxy_uri
      uri.user, uri.password = 'user', 'my%20pass'
      fetcher = Gem::RemoteFetcher.new uri.to_s
      proxy = fetcher.instance_variable_get("@proxy_uri")
      assert_equal 'user', proxy.user
      assert_equal 'my pass', URI.unescape(proxy.password)
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end
  end

  def test_explicit_proxy_with_user_auth_in_env
    use_ui @ui do
      ENV['http_proxy'] = @proxy_uri
      ENV['http_proxy_user'] = 'foo'
      ENV['http_proxy_pass'] = 'bar'
      fetcher = Gem::RemoteFetcher.new nil
      proxy = fetcher.instance_variable_get("@proxy_uri")
      assert_equal 'foo', proxy.user
      assert_equal 'bar', proxy.password
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end

    use_ui @ui do
      ENV['http_proxy'] = @proxy_uri
      ENV['http_proxy_user'] = 'foo\user'
      ENV['http_proxy_pass'] = 'my bar'
      fetcher = Gem::RemoteFetcher.new nil
      proxy = fetcher.instance_variable_get("@proxy_uri")
      assert_equal 'foo\user', URI.unescape(proxy.user)
      assert_equal 'my bar', URI.unescape(proxy.password)
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end
  end

  def test_fetch_path_io_error
    fetcher = Gem::RemoteFetcher.new nil

    def fetcher.open_uri_or_path(uri) raise EOFError; end

    e = assert_raise Gem::RemoteFetcher::FetchError do
      fetcher.fetch_path 'uri'
    end

    assert_equal 'EOFError: EOFError reading uri', e.message
  end

  def test_fetch_path_socket_error
    fetcher = Gem::RemoteFetcher.new nil

    def fetcher.open_uri_or_path(uri) raise SocketError; end

    e = assert_raise Gem::RemoteFetcher::FetchError do
      fetcher.fetch_path 'uri'
    end

    assert_equal 'SocketError: SocketError reading uri', e.message
  end

  def test_fetch_path_system_call_error
    fetcher = Gem::RemoteFetcher.new nil

    def fetcher.open_uri_or_path(uri);
      raise Errno::ECONNREFUSED, 'connect(2)'
    end

    e = assert_raise Gem::RemoteFetcher::FetchError do
      fetcher.fetch_path 'uri'
    end

    assert_match %r|ECONNREFUSED:.*connect\(2\) reading uri\z|,
                 e.message
  end

  def test_get_proxy_from_env_empty
    orig_env_HTTP_PROXY = ENV['HTTP_PROXY']
    orig_env_http_proxy = ENV['http_proxy']

    ENV['HTTP_PROXY'] = ''
    ENV.delete 'http_proxy'

    fetcher = Gem::RemoteFetcher.new nil

    assert_equal nil, fetcher.send(:get_proxy_from_env)

  ensure
    orig_env_HTTP_PROXY.nil? ? ENV.delete('HTTP_PROXY') :
                               ENV['HTTP_PROXY'] = orig_env_HTTP_PROXY
    orig_env_http_proxy.nil? ? ENV.delete('http_proxy') :
                               ENV['http_proxy'] = orig_env_http_proxy
  end

  def test_implicit_no_proxy
    use_ui @ui do
      ENV['http_proxy'] = 'http://fakeurl:12345'
      fetcher = Gem::RemoteFetcher.new :no_proxy
      assert_data_from_server fetcher.fetch_path(@server_uri)
    end
  end

  def test_implicit_proxy
    use_ui @ui do
      ENV['http_proxy'] = @proxy_uri
      fetcher = Gem::RemoteFetcher.new nil
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end
  end

  def test_implicit_upper_case_proxy
    use_ui @ui do
      ENV['HTTP_PROXY'] = @proxy_uri
      fetcher = Gem::RemoteFetcher.new nil
      assert_data_from_proxy fetcher.fetch_path(@server_uri)
    end
  end

  def test_implicit_proxy_no_env
    use_ui @ui do
      fetcher = Gem::RemoteFetcher.new nil
      assert_data_from_server fetcher.fetch_path(@server_uri)
    end
  end

  def test_open_uri_or_path
    fetcher = Gem::RemoteFetcher.new nil

    conn = Object.new
    def conn.started?() true end
    def conn.request(req)
      unless defined? @requested then
        @requested = true
        res = Net::HTTPRedirection.new nil, 301, nil
        res.add_field 'Location', 'http://gems.example.com/real_path'
        res
      else
        res = Net::HTTPOK.new nil, 200, nil
        def res.body() 'real_path' end
        res
      end
    end

    conn = { 'gems.example.com:80' => conn }
    fetcher.instance_variable_set :@connections, conn

    fetcher.send :open_uri_or_path, 'http://gems.example.com/redirect' do |io|
      assert_equal 'real_path', io.read
    end
  end

  def test_open_uri_or_path_limited_redirects
    fetcher = Gem::RemoteFetcher.new nil

    conn = Object.new
    def conn.started?() true end
    def conn.request(req)
      res = Net::HTTPRedirection.new nil, 301, nil
      res.add_field 'Location', 'http://gems.example.com/redirect'
      res
    end

    conn = { 'gems.example.com:80' => conn }
    fetcher.instance_variable_set :@connections, conn

    e = assert_raise Gem::RemoteFetcher::FetchError do
      fetcher.send :open_uri_or_path, 'http://gems.example.com/redirect'
    end

    assert_equal 'too many redirects', e.message
  end

  def test_zip
    use_ui @ui do
      self.class.enable_zip = true
      fetcher = Gem::RemoteFetcher.new nil
      assert_equal SERVER_DATA.size, fetcher.fetch_size(@server_uri), "probably not from proxy"
      zip_data = fetcher.fetch_path(@server_z_uri)
      assert zip_data.size < SERVER_DATA.size, "Zipped data should be smaller"
    end
  end

  def test_no_zip
    use_ui @ui do
      self.class.enable_zip = false
      fetcher = Gem::RemoteFetcher.new nil
      assert_error { fetcher.fetch_path(@server_z_uri) }
    end
  end

  def test_yaml_error_on_size
    use_ui @ui do
      self.class.enable_yaml = false
      fetcher = Gem::RemoteFetcher.new nil
      assert_error { fetcher.size }
    end
  end

  private

  def assert_error(exception_class=Exception)
    got_exception = false
    begin
      yield
    rescue exception_class => ex
      got_exception = true
    end
    assert got_exception, "Expected exception conforming to #{exception_class}"
  end

  def assert_data_from_server(data)
    assert_block("Data is not from server") { data =~ /0\.4\.11/ }
  end

  def assert_data_from_proxy(data)
    assert_block("Data is not from proxy") { data =~ /0\.4\.2/ }
  end

  class NilLog < WEBrick::Log
    def log(level, data) #Do nothing
    end
  end

  class << self
    attr_reader :normal_server, :proxy_server
    attr_accessor :enable_zip, :enable_yaml

    def start_servers
      @normal_server ||= start_server(SERVER_PORT, SERVER_DATA)
      @proxy_server  ||= start_server(PROXY_PORT, PROXY_DATA)
      @enable_yaml = true
      @enable_zip = false
    end

    private

    def start_server(port, data)
      Thread.new do
        begin
          null_logger = NilLog.new
          s = WEBrick::HTTPServer.new(
            :Port            => port,
            :DocumentRoot    => nil,
            :Logger          => null_logger,
            :AccessLog       => null_logger
            )
          s.mount_proc("/kill") { |req, res| s.shutdown }
          s.mount_proc("/yaml") { |req, res|
            if @enable_yaml
              res.body = data
              res['Content-Type'] = 'text/plain'
              res['content-length'] = data.size
            else
              res.status = "404"
              res.body = "<h1>NOT FOUND</h1>"
              res['Content-Type'] = 'text/html'
            end
          }
          s.mount_proc("/yaml.Z") { |req, res|
            if @enable_zip
              res.body = Zlib::Deflate.deflate(data)
              res['Content-Type'] = 'text/plain'
            else
              res.status = "404"
              res.body = "<h1>NOT FOUND</h1>"
              res['Content-Type'] = 'text/html'
            end
          }
          s.start
        rescue Exception => ex
          abort ex.message
          puts "ERROR during server thread: #{ex.message}"
        end
      end
      sleep 0.2                 # Give the servers time to startup
    end
  end

end

