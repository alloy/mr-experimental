require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/../../fixtures/constants'

describe "Module#remove_const" do
  it "removes the constant specified by a String or Symbol from the receiver's constant table" do
    ConstantSpecs::ModuleM::CS_CONST252 = :const252
    ConstantSpecs::ModuleM::CS_CONST252.should == :const252

    ConstantSpecs::ModuleM.send :remove_const, :CS_CONST252
    lambda { ConstantSpecs::ModuleM::CS_CONST252 }.should raise_error(NameError)

    ConstantSpecs::ModuleM::CS_CONST253 = :const253
    ConstantSpecs::ModuleM::CS_CONST253.should == :const253

    ConstantSpecs::ModuleM.send :remove_const, "CS_CONST253"
    lambda { ConstantSpecs::ModuleM::CS_CONST253 }.should raise_error(NameError)
  end

  it "returns the value of the removed constant" do
    ConstantSpecs::ModuleM::CS_CONST254 = :const254
    ConstantSpecs::ModuleM.send(:remove_const, :CS_CONST254).should == :const254
  end

  it "raises a NameError if the constant is not defined directly in the module" do
    ConstantSpecs::ModuleM::CS_CONST255 = :const255
    ConstantSpecs::ContainerA::CS_CONST255.should == :const255
    lambda do
      ConstantSpecs::ContainerA.send :remove_const, :CS_CONST255
    end.should raise_error(NameError)
  end

  it "raises a NameError if the name does not start with a capital letter" do
    lambda { ConstantSpecs.send :remove_const, "name" }.should raise_error(NameError)
  end

  it "raises a NameError if the name starts with a non-alphabetic character" do
    lambda { ConstantSpecs.send :remove_const, "__CONSTX__" }.should raise_error(NameError)
    lambda { ConstantSpecs.send :remove_const, "@Name" }.should raise_error(NameError)
    lambda { ConstantSpecs.send :remove_const, "!Name" }.should raise_error(NameError)
    lambda { ConstantSpecs.send :remove_const, "::Name" }.should raise_error(NameError)
  end

  it "raises a NameError if the name contains non-alphabetic characters except '_'" do
    ConstantSpecs::ModuleM::CS_CONST256 = :const256
    ConstantSpecs::ModuleM.send :remove_const, "CS_CONST256"
    lambda { ConstantSpecs.send :remove_const, "Name=" }.should raise_error(NameError)
    lambda { ConstantSpecs.send :remove_const, "Name?" }.should raise_error(NameError)
  end

  it "calls #to_str to convert the given name to a String" do
    ConstantSpecs::CS_CONST257 = :const257
    name = mock("CS_CONST257")
    name.should_receive(:to_str).and_return("CS_CONST257")
    ConstantSpecs.send(:remove_const, name).should == :const257
  end

  it "raises a TypeError if conversion to a String by calling #to_str fails" do
    name = mock('123')
    lambda { ConstantSpecs.send :remove_const, name }.should raise_error(TypeError)

    name.should_receive(:to_str).and_return(123)
    lambda { ConstantSpecs.send :remove_const, name }.should raise_error(TypeError)
  end

  ruby_version_is "" ... "1.9" do
    it "is a private method" do
      Module.private_methods.should include("remove_const")
    end
  end

  ruby_version_is "1.9" do
    it "is a private method" do
      Module.private_methods.should include(:remove_const)
    end
  end
end

