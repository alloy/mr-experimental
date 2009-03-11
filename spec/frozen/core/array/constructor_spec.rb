require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Array.[]" do
  it "returns a new array populated with the given elements" do
    obj = Object.new
    Array.[](5, true, nil, 'a', "Ruby", obj).should == [5, true, nil, "a", "Ruby", obj]

    a = ArraySpecs::MyArray.[](5, true, nil, 'a', "Ruby", obj)
    a.class.should == ArraySpecs::MyArray
    a.inspect.should == [5, true, nil, "a", "Ruby", obj].inspect
  end
end

describe "Array[]" do
  it "is a synonym for .[]" do
    obj = Object.new
    Array[5, true, nil, 'a', "Ruby", obj].should == Array.[](5, true, nil, "a", "Ruby", obj)

    a = ArraySpecs::MyArray[5, true, nil, 'a', "Ruby", obj]
    a.class.should == ArraySpecs::MyArray
    a.inspect.should == [5, true, nil, "a", "Ruby", obj].inspect
  end
end
