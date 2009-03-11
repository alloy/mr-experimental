require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/../../fixtures/constants'

describe "Module.constants" do
  it "returns an array of the names of all toplevel constants" do
    count = Module.constants.size
    module ConstantSpecsAdded
      CS_CONST1 = 1
    end
    Module.constants.size.should == count + 1
  end

  ruby_version_is "" ... "1.9" do
    it "returns an array of String names" do
      # This in NOT an exhaustive list
      Module.constants.should include("Array", "Bignum", "Class", "Comparable", "Dir",
                                      "Enumerable", "ENV", "Exception", "FalseClass",
                                      "File", "Fixnum", "Float", "Hash", "Integer", "IO",
                                      "Kernel", "Math", "Method", "Module", "NilClass",
                                      "Numeric", "Object", "Range", "Regexp", "String",
                                      "Symbol", "Thread", "Time", "TrueClass")
    end
  end

  ruby_version_is "1.9" do
    it "returns an array of Symbol names" do
      # This in NOT an exhaustive list
      Module.constants.should include(:Array, :Bignum, :Class, :Comparable, :Dir,
                                      :Enumerable, :ENV, :Exception, :FalseClass,
                                      :File, :Fixnum, :Float, :Hash, :Integer, :IO,
                                      :Kernel, :Math, :Method, :Module, :NilClass,
                                      :Numeric, :Object, :Range, :Regexp, :String,
                                      :Symbol, :Thread, :Time, :TrueClass)
    end
  end
end

describe "Module#constants" do
  ruby_version_is "" ... "1.9" do
    it "returns an array of String names of all constants defined in the module" \
       "and all included modules" do
      ConstantSpecs::ContainerA.constants.sort.should == [
        "CS_CONST10", "CS_CONST23", "CS_CONST24", "CS_CONST5", "ChildA"
      ]
    end

    it "includes names of constants defined after a module is included" do
      ConstantSpecs::ModuleM::CS_CONST250 = :const250
      ConstantSpecs::ContainerA.constants.should include("CS_CONST250")
    end
  end

  ruby_version_is "1.9" do
    it "returns an array of Symbol names of all constants defined in the module" \
       "and all included modules" do
      ConstantSpecs::ContainerA.constants.sort.should == [
        :CS_CONST10, :CS_CONST23, :CS_CONST24, :CS_CONST5, :ChildA
      ]
    end

    it "includes names of constants defined after a module is included" do
      ConstantSpecs::ModuleM::CS_CONST251 = :const251
      ConstantSpecs::ContainerA.constants.should include(:CS_CONST251)
    end
  end
end
