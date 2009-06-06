require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/common'

ruby_version_is "1.9.2" do
  describe "Dir.home" do
    it "returns the current user's home directory as a string if called without arguments" do
      Dir.home.should == home_directory
    end

    it "returns the named user's home directory as a string if called with an argument" do
      Dir.home(ENV['USER']).should == home_directory
    end

    it "raises an ArgumentError if the named user doesn't exist" do
      lambda { Dir.home('geuw2n288dh2k') }.should raise_error(ArgumentError)
    end  
  end  
end
