require File.dirname(__FILE__) + '/../../../spec_helper'

describe :numeric_real, :shared => true do
  before(:each) do
    @numbers = [
      20,             # Integer
      398.72,         # Float
      Rational(3, 4), # Rational
      bignum_value, # Bignum
      Float::MAX * 2, # Infinity
      0/0.0           # NaN
    ].map{|n| [n,-n]}.flatten 
  end

  it "returns self" do
    @numbers.each do |number| 
      if number.to_f.nan?
        number.real.nan?.should be_true
      else
        number.real.should == number
      end
    end
  end  

  it "raises an ArgumentError if given any arguments" do
   @numbers.each do |number| 
     lambda { number.real(number) }.should raise_error(ArgumentError)
   end
  end
end
