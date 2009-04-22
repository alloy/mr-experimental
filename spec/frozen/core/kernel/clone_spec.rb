require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Kernel#clone" do
  before :each do
    ScratchPad.clear
    @obj = KernelSpecs::Duplicate.new 1, :a
  end

  it "calls #initialize_copy on the new instance" do
    clone = @obj.clone
    ScratchPad.recorded.should_not == @obj.object_id
    ScratchPad.recorded.should == clone.object_id
  end

  it "copies instance variables" do
    clone = @obj.clone
    clone.one.should == 1
    clone.two.should == :a
  end

  it "copies singleton methods" do
    def @obj.special() :the_one end
    clone = @obj.clone
    clone.special.should == :the_one
  end

  it "copies modules included in the singleton class" do
    class << @obj
      include KernelSpecs::DuplicateM
    end

    clone = @obj.clone
    clone.repr.should == "KernelSpecs::Duplicate"
  end

  it "copies constants defined in the singleton class" do
    class << @obj
      CLONE = :clone
    end

    clone = @obj.clone
    class << clone
      CLONE.should == :clone
    end
  end
end
