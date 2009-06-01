require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'
require File.dirname(__FILE__) + '/shared/iteration'

describe "Hash#each_key" do
  it "calls block once for each key, passing key" do
    r = new_hash
    h = new_hash(1 => -1, 2 => -2, 3 => -3, 4 => -4)
    h.each_key { |k| r[k] = k }.should equal(h)
    r.should == new_hash(1 => 1, 2 => 2, 3 => 3, 4 => 4)
  end

  it "processes keys in the same order as keys()" do
    keys = []
    h = new_hash(1 => -1, 2 => -2, 3 => -3, 4 => -4)
    h.each_key { |k| keys << k }
    keys.should == h.keys
  end

  it_behaves_like(:hash_iteration_no_block, :each_key)
end
