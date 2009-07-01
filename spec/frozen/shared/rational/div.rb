require File.dirname(__FILE__) + '/../../spec_helper'
require 'rational'

describe :rational_div_rat, :shared => true do
  it "performs integer division and returns the result" do 
    Rational(2, 3).div(Rational(2, 3)).should == 1
    Rational(-2, 9).div(Rational(-9, 2)).should == 0
  end
  
  it "raises a ZeroDivisionError when the argument has a numerator of 0" do
    lambda { Rational(3, 4).div(Rational(0, 3)) }.should raise_error(ZeroDivisionError)
  end    
 
  # 1.8 doesn't accept Floats for Rational() arguments
  ruby_version_is "1.9" do
    it "raises a ZeroDivisionError when the argument has a numerator of 0.0" do
      lambda { Rational(3, 4).div(Rational(0.0, 3)) }.should raise_error(ZeroDivisionError)
    end
  end
end  

describe :rational_div_float, :shared => true do

  # The version guard is necessary because 1.8 can't cope with Floats passed
  # to Rational(), so we need to simplify the examples accordingly.
  
  ruby_version_is "1.9" do
    it "performs integer division and returns the result" do 
      Rational(2, 3).div(30.333).should == 0
      Rational(2, 9).div(Rational(-8.6)).should == -1
      Rational(3.12).div(0.5).should == 6
    end
  end
  
  ruby_version_is ""..."1.9" do
    it "performs integer division and returns the result" do 
      Rational(2, 3).div(30.333).should == 0
      Rational(7, 12).div(0.5).should == 1
    end
  end

  ruby_version_is ""..."1.9" do
    it "raises a FloatDomainError when the argument is 0.0" do
      lambda { Rational(3, 4).div(0.0) }.should raise_error(FloatDomainError)
    end    
  end

  ruby_version_is "1.9" do
    it "raises a ZeroDivisionError when the argument is 0.0" do
      lambda { Rational(3, 4).div(0.0) }.should raise_error(ZeroDivisionError)
    end    
  end
end  

describe :rational_div_int, :shared => true do
  it "performs integer division and returns the result" do 
    Rational(2, 1).div(1).should == 2
    Rational(25, 5).div(-50).should == -1
  end
  
  it "raises a ZeroDivisionError when the argument is 0" do
    lambda { Rational(3, 4).div(0) }.should raise_error(ZeroDivisionError)
  end    
end  

describe :rational_div, :shared => true do
  it "returns an Integer" do 
    Rational(229, 21).div(82).should be_kind_of(Integer)
  end
  
  it "raises an ArgumentError if passed more than one argument" do
    lambda { Rational(3, 4).div(2,3) }.should raise_error(ArgumentError)
  end    

  ruby_bug "#1648", "1.8.7" do
    it "raises a TypeError if passed a non-numeric argument" do
      lambda { Rational(3, 4).div([]) }.should raise_error(TypeError)
    end
  end  
end  
