require File.dirname(__FILE__) + '/../../spec_helper'

ruby_version_is "1.9" do
  describe "Fiber.yield" do

    it "passes control to the Fiber's caller" do
      step = 0
      fiber = Fiber.new { step = 1; Fiber.yield; step = 2; Fiber.yield; step = 3 }
      fiber.resume
      step.should == 1
      fiber.resume
      step.should == 2
    end

    it "returns its arguments to the caller" do
      fiber = Fiber.new { true; Fiber.yield :glark; true }
      fiber.resume.should == :glark
    end  

    it "returns nil to the caller if given no arguments" do
      fiber = Fiber.new { true; Fiber.yield; true }
      fiber.resume.should be_nil
    end

    it "returns to the Fiber the value of the #resume call that invoked it" do
      fiber = Fiber.new { Fiber.yield.should == :caller }
      fiber.resume
      fiber.resume :caller
    end
    
    it "raises a FiberError if called from the root Fiber" do
      lambda{ Fiber.yield }.should raise_error(FiberError)
    end  
  end
end
