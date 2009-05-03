require File.dirname(__FILE__) + '/../../../spec_helper'
require File.dirname(__FILE__) + '/../fixtures/classes'

describe "UNIXSocket#peeraddr" do

  platform_is_not :windows do
    before :each do
      @path = SocketSpecs.socket_path
      File.unlink(@path) if File.exists?(@path)

      @server = UNIXServer.open(@path)
      @client = UNIXSocket.open(@path)
    end

    after :each do
      @client.close
      @server.close
      File.unlink(@path) if File.exists?(@path)
    end

    it "returns the address familly and path of the server end of the connection" do
      @client.peeraddr.should == ["AF_UNIX", @path]
    end

    it "raises an error in server sockets" do
      lambda { @server.peeraddr }.should raise_error
    end
  end

end
