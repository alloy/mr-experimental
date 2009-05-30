require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Method#name" do
  ruby_version_is '1.8.7' do
    it "returns the name of the method" do
      "abc".method(:upcase).name.should == :upcase
    end
    
    it "returns the name even when aliased" do
      obj = MethodSpecs::Methods.new
      obj.method(:foo).name.should == :foo
      obj.method(:bar).name.should == :bar
      obj.method(:bar).unbind.bind(obj).name.should == :bar
    end
  end
end