require File.dirname(__FILE__) + '/../../spec_helper'
require 'etc'

platform_is :windows do
  describe "Etc.getpwnam" do
    it "returns nil" do
      Etc.getpwnam(1).should == nil
      Etc.getpwnam(nil).should == nil
      Etc.getpwnam('nil').should == nil
    end
  end
end

platform_is_not :windows do
  describe "Etc.getpwnam" do
    ruby_version_is "" ... "1.9" do
      it "returns a Passwd struct instance for the given user" do
        pw = Etc.getpwnam(`whoami`.strip)
        pw.is_a?(Struct::Passwd).should == true
      end
    end

    ruby_version_is "1.9" do
      it "returns a Etc::Passwd struct instance for the given user" do
        pw = Etc.getpwnam(`whoami`.strip)
        pw.is_a?(Etc::Passwd).should == true
      end
    end

    it "only accepts strings as argument" do
      lambda {
        Etc.getpwnam(123)
        Etc.getpwnam(nil)
      }.should raise_error(TypeError)
    end
  end
end
