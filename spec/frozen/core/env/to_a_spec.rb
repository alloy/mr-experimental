require File.dirname(__FILE__) + '/../../spec_helper'

describe "ENV.to_a" do

  it "returns the ENV as an array" do
    ENV["foo"] = "bar"
    a = ENV.to_a
    a.is_a?(Array).should == true
    a.find { |e| e.first == "foo" }.should == ["foo", "bar"]
    ENV.delete "foo"
  end

  ruby_version_is "1.9" do
    it "returns the entries in the locale encoding" do
      ENV.to_a.each do |key, value|
        key.encoding.should == Encoding.find('locale')
        value.encoding.should == Encoding.find('locale')
      end
    end
  end
end
