require File.dirname(__FILE__) + '/../../spec_helper'

describe "ENV.values_at" do

  it "returns an array of the values referenced by the parameters as keys" do
    ENV["foo"] = "oof"
    ENV["bar"] = "rab"
    ENV.values_at.should == []
    ENV.values_at("bar", "foo").should == ["rab", "oof"]
    ENV.delete "foo"
    ENV.delete "bar"
  end

  ruby_version_is "1.9" do
    it "uses the locale encoding" do
      ENV.values_at(ENV.keys.first).first.encoding.should == Encoding.find('locale')
    end
  end
end
