require File.dirname(__FILE__) + '/../../spec_helper'

describe "ENV.keys" do

  it "returns all the keys" do
    ENV.keys.sort.should == ENV.to_hash.keys.sort
  end

  ruby_version_is "1.9" do
    it "returns the keys in the locale encoding" do
      ENV.keys.each do |key|
        key.encoding.should == Encoding.find('locale')
      end
    end
  end
end
