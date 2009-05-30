require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Hash#empty?" do
  it "returns true if the hash has no entries" do
    new_hash.empty?.should == true
    new_hash(1 => 1).empty?.should == false
  end

  it "returns true if the hash has no entries and has a default value" do
    new_hash(5).empty?.should == true
    new_hash { 5 }.empty?.should == true
    new_hash { |hsh, k| hsh[k] = k }.empty?.should == true
  end
end
