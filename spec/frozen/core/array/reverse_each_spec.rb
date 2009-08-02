require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

# Modifying a collection while the contents are being iterated
# gives undefined behavior. See
# http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-core/23633

describe "Array#reverse_each" do
  before :each do
    ScratchPad.record []
  end

  it "traverses array in reverse order and pass each element to block" do
    [1, 3, 4, 6].reverse_each { |i| ScratchPad << i }
    ScratchPad.recorded.should == [6, 4, 3, 1]
  end

  it "returns self" do
    a = [:a, :b, :c]
    a.reverse_each { |x| }.should equal(a)
  end

  it "yields only the top level element of an empty recursive arrays" do
    empty = ArraySpecs.empty_recursive_array
    empty.reverse_each { |i| ScratchPad << i }
    ScratchPad.recorded.should == [empty]
  end

  it "yields only the top level element of a recursive array" do
    array = ArraySpecs.recursive_array
    array.reverse_each { |i| ScratchPad << i }
    ScratchPad.recorded.should == [array, array, array, array, array, 3.0, 'two', 1]
  end

  ruby_version_is '' ... '1.8.7' do
    it 'raises a LocalJumpError if no block given' do
      lambda{ [1,2].reverse_each }.should raise_error(LocalJumpError)
    end
  end

  ruby_version_is '1.8.7' do
    it 'returns an Enumerator if no block given' do
      [1,2].reverse_each.should be_kind_of(enumerator_class)
    end
  end
end
