require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

# Modifying a collection while the contents are being iterated
# gives undefined behavior. See
# http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-core/23633

describe "Array#each" do
  it "yields each element to the block" do
    a = []
    x = [1, 2, 3]
    x.each { |item| a << item }.should equal(x)
    a.should == [1, 2, 3]
  end

  it "yields each element to a block that takes multiple arguments" do
    a = [[1, 2], :a, [3, 4]]
    b = []

    a.each { |x, y| b << x }
    b.should == [1, :a, 3]

    b = []
    a.each { |x, y| b << y }
    b.should == [2, nil, 4]
  end

  ruby_version_is '' ... '1.8.7' do
    it 'raises a LocalJumpError if no block given' do
      lambda{ [1,2].each }.should raise_error(LocalJumpError)
    end
  end

  ruby_version_is '1.8.7' do
    it 'returns an Enumerator if no block given' do
      [1,2].each.should be_kind_of(enumerator_class)
    end
  end
end
