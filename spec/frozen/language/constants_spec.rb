require File.dirname(__FILE__) + '/../spec_helper'
require File.dirname(__FILE__) + '/../fixtures/constants'

# Read the documentation in fixtures/constants.rb for the guidelines and
# rationale for the structure and organization of these specs.

describe "Literal (A::X) constant resolution" do
  describe "with statically assigned constants" do
    it "searches the immediate class or module scope first" do
      ConstantSpecs::ClassA::CS_CONST10.should == :const10_10
      ConstantSpecs::ModuleA::CS_CONST10.should == :const10_1
      ConstantSpecs::ParentA::CS_CONST10.should == :const10_5
      ConstantSpecs::ContainerA::CS_CONST10.should == :const10_2
      ConstantSpecs::ContainerA::ChildA::CS_CONST10.should == :const10_3
    end

    it "searches a module included in the immediate class before the superclass" do
      ConstantSpecs::ContainerA::ChildA::CS_CONST15.should == :const15_1
    end

    it "searches the superclass before a module included in the superclass" do
      ConstantSpecs::ContainerA::ChildA::CS_CONST11.should == :const11_1
    end

    it "searches a module included in the superclass" do
      ConstantSpecs::ContainerA::ChildA::CS_CONST12.should == :const12_1
    end

    it "searches the superclass chain" do
      ConstantSpecs::ContainerA::ChildA::CS_CONST13.should == :const13
    end

    it "searches Object if no class or module qualifier is given" do
      CS_CONST1.should == :const1
      CS_CONST10.should == :const10_1
    end

    it "searches Object if a toplevel qualifier (::X) is given" do
      ::CS_CONST1.should == :const1
      ::CS_CONST10.should == :const10_1
    end

    it "does not search the singleton class of the class or module" do
      lambda do
        ConstantSpecs::ContainerA::ChildA::CS_CONST14
      end.should raise_error(NameError)
      lambda { ConstantSpecs::CS_CONST14 }.should raise_error(NameError)
    end
  end

  describe "with dynamically assigned constants" do
    it "searches the immediate class or module scope first" do
      ConstantSpecs::ClassB::CS_CONST101 = :const101_1
      ConstantSpecs::ClassB::CS_CONST101.should == :const101_1

      ConstantSpecs::ParentB::CS_CONST101 = :const101_2
      ConstantSpecs::ParentB::CS_CONST101.should == :const101_2

      ConstantSpecs::ContainerB::CS_CONST101 = :const101_3
      ConstantSpecs::ContainerB::CS_CONST101.should == :const101_3

      ConstantSpecs::ContainerB::ChildB::CS_CONST101 = :const101_4
      ConstantSpecs::ContainerB::ChildB::CS_CONST101.should == :const101_4

      ConstantSpecs::ModuleA::CS_CONST101 = :const101_5
      ConstantSpecs::ModuleA::CS_CONST101.should == :const101_5
    end

    it "searches a module included in the immediate class before the superclass" do
      ConstantSpecs::ParentB::CS_CONST102 = :const102_1
      ConstantSpecs::ModuleF::CS_CONST102 = :const102_2
      ConstantSpecs::ContainerB::ChildB::CS_CONST102.should == :const102_2
    end

    it "searches the superclass before a module included in the superclass" do
      ConstantSpecs::ModuleE::CS_CONST103 = :const103_1
      ConstantSpecs::ParentB::CS_CONST103 = :const103_2
      ConstantSpecs::ContainerB::ChildB::CS_CONST103.should == :const103_2
    end

    it "searches a module included in the superclass" do
      ConstantSpecs::ModuleA::CS_CONST104 = :const104_1
      ConstantSpecs::ModuleE::CS_CONST104 = :const104_2
      ConstantSpecs::ContainerB::ChildB::CS_CONST104.should == :const104_2
    end

    it "searches the superclass chain" do
      ConstantSpecs::ModuleA::CS_CONST105 = :const105
      ConstantSpecs::ContainerB::ChildB::CS_CONST105.should == :const105
    end

    it "searches Object if no class or module qualifier is given" do
      CS_CONST106 = :const106
      CS_CONST106.should == :const106
    end

    it "searches Object if a toplevel qualifier (::X) is given" do
      ::CS_CONST107 = :const107
      ::CS_CONST107.should == :const107
    end

    it "does not search the singleton class of the class or module" do
      class << ConstantSpecs::ContainerB::ChildB
        CS_CONST108 = :const108_1
      end

      lambda do
        ConstantSpecs::ContainerB::ChildB::CS_CONST108
      end.should raise_error(NameError)

      module ConstantSpecs
        class << self
          CS_CONST108 = :const108_2
        end
      end

      lambda { ConstantSpecs::CS_CONST108 }.should raise_error(NameError)
    end

    it "returns the updated value when a constant is reassigned" do
      ConstantSpecs::ClassB::CS_CONST109 = :const109_1
      ConstantSpecs::ClassB::CS_CONST109.should == :const109_1

      ConstantSpecs::ClassB::CS_CONST109 = :const109_2
      ConstantSpecs::ClassB::CS_CONST109.should == :const109_2
    end
  end

  it "raises a NameError if no constant is defined in the search path" do
    lambda { ConstantSpecs::ParentA::CS_CONSTX }.should raise_error(NameError)
  end

  it "sends #const_missing to the original class or module scope" do
    ConstantSpecs::ClassA::CS_CONSTX.should == :CS_CONSTX
  end

  it "evaluates the qualifier" do
    ConstantSpecs.get_const::CS_CONST2.should == :const2
  end

  it "raises a TypeError if a non-class or non-module qualifier is given" do
    lambda { CS_CONST1::CS_CONST }.should raise_error(TypeError)
    lambda { 1::CS_CONST         }.should raise_error(TypeError)
    lambda { "mod"::CS_CONST     }.should raise_error(TypeError)
    lambda { false::CS_CONST     }.should raise_error(TypeError)
  end
end

describe "Constant resolution within methods" do
  describe "with statically assigned constants" do
    it "searches the immediate class or module scope first" do
      ConstantSpecs::ClassA.const10.should == :const10_10
      ConstantSpecs::ParentA.const10.should == :const10_5
      ConstantSpecs::ContainerA.const10.should == :const10_2
      ConstantSpecs::ContainerA::ChildA.const10.should == :const10_3

      ConstantSpecs::ClassA.new.const10.should == :const10_10
      ConstantSpecs::ParentA.new.const10.should == :const10_5
      ConstantSpecs::ContainerA::ChildA.new.const10.should == :const10_3
    end

    it "searches a module included in the immediate class before the superclass" do
      ConstantSpecs::ContainerA::ChildA.const15.should == :const15_1
      ConstantSpecs::ContainerA::ChildA.new.const15.should == :const15_1
    end

    it "searches the superclass before a module included in the superclass" do
      ConstantSpecs::ContainerA::ChildA.const11.should == :const11_1
      ConstantSpecs::ContainerA::ChildA.new.const11.should == :const11_1
    end

    it "searches a module included in the superclass" do
      ConstantSpecs::ContainerA::ChildA.const12.should == :const12_1
      ConstantSpecs::ContainerA::ChildA.new.const12.should == :const12_1
    end

    it "searches the superclass chain" do
      ConstantSpecs::ContainerA::ChildA.const13.should == :const13
      ConstantSpecs::ContainerA::ChildA.new.const13.should == :const13
    end

    it "searches the lexical scope of the method not the receiver's immediate class" do
      ConstantSpecs::ContainerA::ChildA.const19.should == :const19_1
    end

    it "searches the lexical scope of a singleton method" do
      ConstantSpecs::CS_CONST18.const17.should == :const17_1
    end

    it "does not search the lexical scope of the caller" do
      lambda { ConstantSpecs::ClassA.const16 }.should raise_error(NameError)
    end

    it "searches the lexical scope of a block" do
      ConstantSpecs::ClassA.const22.should == :const22_1
    end

    it "searches Object as a lexical scope only if Object is explicitly opened" do
      ConstantSpecs::ContainerA::ChildA.const20.should == :const20_1
      ConstantSpecs::ContainerA::ChildA.const21.should == :const21_1
    end

    it "does not search the lexical scope of qualifying modules" do
      lambda do
        ConstantSpecs::ContainerA::ChildA.const23
      end.should raise_error(NameError)
    end
  end

  describe "with dynamically assigned constants" do
    it "searches the immediate class or module scope first" do
      ConstantSpecs::ModuleA::CS_CONST201 = :const201_1

      class ConstantSpecs::ClassB; CS_CONST201 = :const201_2; end
      ConstantSpecs::ParentB::CS_CONST201 = :const201_3
      ConstantSpecs::ContainerB::CS_CONST201 = :const201_4
      ConstantSpecs::ContainerB::ChildB::CS_CONST201 = :const201_5

      ConstantSpecs::ClassB.const201.should == :const201_2
      ConstantSpecs::ParentB.const201.should == :const201_3
      ConstantSpecs::ContainerB.const201.should == :const201_4
      ConstantSpecs::ContainerB::ChildB.const201.should == :const201_5

      ConstantSpecs::ClassB.new.const201.should == :const201_2
      ConstantSpecs::ParentB.new.const201.should == :const201_3
      ConstantSpecs::ContainerB::ChildB.new.const201.should == :const201_5
    end

    it "searches a module included in the immediate class before the superclass" do
      ConstantSpecs::ParentB::CS_CONST202 = :const202_2
      ConstantSpecs::ContainerB::ChildB::CS_CONST202 = :const202_1

      ConstantSpecs::ContainerB::ChildB.const202.should == :const202_1
      ConstantSpecs::ContainerB::ChildB.new.const202.should == :const202_1
    end

    it "searches the superclass before a module included in the superclass" do
      ConstantSpecs::ParentB::CS_CONST203 = :const203_1
      ConstantSpecs::ModuleE::CS_CONST203 = :const203_2

      ConstantSpecs::ContainerB::ChildB.const203.should == :const203_1
      ConstantSpecs::ContainerB::ChildB.new.const203.should == :const203_1
    end

    it "searches a module included in the superclass" do
      ConstantSpecs::ModuleA::CS_CONST204 = :const204_2
      ConstantSpecs::ModuleE::CS_CONST204 = :const204_1

      ConstantSpecs::ContainerB::ChildB.const204.should == :const204_1
      ConstantSpecs::ContainerB::ChildB.new.const204.should == :const204_1
    end

    it "searches the superclass chain" do
      ConstantSpecs::ModuleA::CS_CONST205 = :const205

      ConstantSpecs::ContainerB::ChildB.const205.should == :const205
      ConstantSpecs::ContainerB::ChildB.new.const205.should == :const205
    end

    it "searches the lexical scope of the method not the receiver's immediate class" do
      ConstantSpecs::ContainerB::ChildB::CS_CONST206 = :const206_2
      class ConstantSpecs::ContainerB::ChildB
        class << self
          CS_CONST206 = :const206_1
        end
      end

      ConstantSpecs::ContainerB::ChildB.const206.should == :const206_1
    end

    it "searches the lexical scope of a singleton method" do
      ConstantSpecs::CS_CONST207 = :const207_1
      ConstantSpecs::ClassB::CS_CONST207 = :const207_2

      ConstantSpecs::CS_CONST208.const207.should == :const207_1
    end

    it "does not search the lexical scope of the caller" do
      ConstantSpecs::ClassB::CS_CONST209 = :const209

      lambda { ConstantSpecs::ClassB.const209 }.should raise_error(NameError)
    end

    it "searches the lexical scope of a block" do
      ConstantSpecs::ClassB::CS_CONST210 = :const210_1
      ConstantSpecs::ParentB::CS_CONST210 = :const210_2

      ConstantSpecs::ClassB.const210.should == :const210_1
    end

    it "searches Object as a lexical scope only if Object is explicitly opened" do
      Object::CS_CONST211 = :const211_1
      ConstantSpecs::ParentB::CS_CONST211 = :const211_2
      ConstantSpecs::ContainerB::ChildB.const211.should == :const211_1

      Object::CS_CONST212 = :const212_2
      ConstantSpecs::ParentB::CS_CONST212 = :const212_1
      ConstantSpecs::ContainerB::ChildB.const212.should == :const212_1
    end

    it "returns the updated value when a constant is reassigned" do
      ConstantSpecs::ParentB::CS_CONST213 = :const213_1
      ConstantSpecs::ContainerB::ChildB.const213.should == :const213_1
      ConstantSpecs::ContainerB::ChildB.new.const213.should == :const213_1

      ConstantSpecs::ParentB::CS_CONST213 = :const213_2
      ConstantSpecs::ContainerB::ChildB.const213.should == :const213_2
      ConstantSpecs::ContainerB::ChildB.new.const213.should == :const213_2
    end

    it "does not search the lexical scope of qualifying modules" do
      ConstantSpecs::ContainerB::CS_CONST214 = :const214

      lambda do
        ConstantSpecs::ContainerB::ChildB.const214
      end.should raise_error(NameError)
    end
  end

  it "raises a NameError if no constant is defined in the search path" do
    lambda { ConstantSpecs::ParentA.constx }.should raise_error(NameError)
  end

  it "sends #const_missing to the original class or module scope" do
    ConstantSpecs::ClassA.constx.should == :CS_CONSTX
    ConstantSpecs::ClassA.new.constx.should == :CS_CONSTX
  end
end
