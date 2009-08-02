require File.dirname(__FILE__) + '/../../spec_helper'

ruby_version_is "1.9" do
  describe "Proc#curry" do
    before(:each) do
      @proc_add = proc {|x,y,z| (x||0) + (y||0) + (z||0) }
      @lambda_add = lambda {|x,y,z| (x||0) + (y||0) + (z||0) }
    end

    it "returns a Proc when called on a proc" do
      p = proc { true }
      p.curry.should be_an_instance_of(Proc)
    end

    it "returns a Proc when called on a lambda" do
      p = lambda { true }
      p.curry.should be_an_instance_of(Proc)
    end

    it "calls the curried proc with the arguments if sufficient arguments have been given" do
      @proc_add.curry[1][2][3].should == 6
      @lambda_add.curry[1][2][3].should == 6
    end

    it "returns a Proc that consumes the remainder of the arguments unless sufficient arguments have been given" do
      proc2 = @proc_add.curry[1][2]
      proc2.should be_an_instance_of(Proc)
      proc2.call(3).should == 6

      lambda2 = @lambda_add.curry[1][2]
      lambda2.should be_an_instance_of(Proc)
      lambda2.call(3).should == 6
      
      @proc_add.curry.call(1,2,3).should == 6
      @lambda_add.curry.call(1,2,3).should == 6
    end
    
    it "can be called multiple times on the same Proc" do
      @proc_add.curry
      lambda { @proc_add.curry }.should_not raise_error

      @lambda_add.curry
      lambda { @lambda_add.curry }.should_not raise_error
    end

    it "can be passed superfluous arguments if created from a proc" do
      lambda { @proc_add.curry[1,2,3,4].should == 6 }.should_not 
        raise_error(ArgumentError)
      lambda { @proc_add.curry[1,2].curry[3,4,5,6].should == 6 }.should_not 
        raise_error(ArgumentError)
    end

    it "raises an ArgumentError if passed superfluous arguments when created from a lambda" do
      lambda { @lambda_add.curry[1,2,3,4] }.should raise_error(ArgumentError)
      lambda { @lambda_add.curry[1,2].curry[3,4,5,6] }.should raise_error(ArgumentError)
    end

    it "returns Procs with arities of -1" do
      @proc_add.curry.arity.should == -1
      @lambda_add.curry.arity.should == -1
      l = lambda { |*a| }
      l.curry.arity.should == -1
    end
  end

  describe "Proc#curry with arity argument" do
    before(:each) do
      @proc_add = proc {|x,y,z| (x||0) + (y||0) + (z||0) }
      @lambda_add = lambda {|x,y,z| (x||0) + (y||0) + (z||0) }
    end

    it "accepts an optional Integer argument for the arity" do
      lambda { @proc_add.curry(3) }.should_not raise_error
      lambda { @lambda_add.curry(3) }.should_not raise_error
    end

    it "returns a Proc when called on a proc" do
      @proc_add.curry(3).should be_an_instance_of(Proc)
    end

    it "returns a Proc when called on a lambda" do
      @lambda_add.curry(3).should be_an_instance_of(Proc)
    end

    # [ruby-core:24127]
    it "retains the lambda-ness of the Proc on which its called" do
      @lambda_add.curry(3).lambda?.should be_true
      @proc_add.curry(3).lambda?.should be_false
    end

    it "raises an ArgumentError if called on a lambda that requires more than _arity_ arguments" do
      p = lambda { true }
      lambda { p.curry(2) }.should raise_error(ArgumentError)
    end

    it "raises an ArgumentError if called on a lambda that requires fewer than _arity_ arguments" do
      p = lambda { true }
      lambda { p.curry(4) }.should raise_error(ArgumentError)
    end

    it "calls the curried proc with the arguments if _arity_ arguments have been given" do
      @proc_add.curry(3)[1][2][3].should == 6
      @lambda_add.curry(3)[1][2][3].should == 6
    end

    it "returns a Proc that consumes the remainder of the arguments when fewer than _arity_ arguments are given" do
      proc2 = @proc_add.curry(3)[1][2]
      proc2.should be_an_instance_of(Proc)
      proc2.call(3).should == 6

      lambda2 = @lambda_add.curry(3)[1][2]
      lambda2.should be_an_instance_of(Proc)
      lambda2.call(3).should == 6
    end
    
    it "can be specified multiple times on the same Proc" do
      @proc_add.curry(2)
      lambda { @proc_add.curry(1) }.should_not raise_error

      @lambda_add.curry(3)
      lambda { @lambda_add.curry(3) }.should_not raise_error
    end

    it "can be passed more than _arity_ arguments if created from a proc" do
      lambda { @proc_add.curry(3)[1,2,3,4].should == 6 }.should_not 
        raise_error(ArgumentError)
      lambda { @proc_add.curry(1)[1,2].curry(3)[3,4,5,6].should == 6 }.should_not 
        raise_error(ArgumentError)
    end

    it "raises an ArgumentError if passed more than _arity_ arguments when created from a lambda" do
      lambda { @lambda_add.curry(3)[1,2,3,4] }.should raise_error(ArgumentError)
      lambda { @lambda_add.curry(1)[1,2].curry(3)[3,4,5,6] }.should raise_error(ArgumentError)
    end

    it "returns Procs with arities of -1 regardless of the value of _arity_" do
      @proc_add.curry(1).arity.should == -1
      @proc_add.curry(2).arity.should == -1
      @lambda_add.curry(3).arity.should == -1
      l = lambda { |*a| }
      l.curry(3).arity.should == -1
    end
  end
end
