require File.dirname(__FILE__) + '/../../spec_helper'

ruby_version_is "1.9" do
  describe "Numeric#abs2" do
    before(:each) do
      @numbers = [
        0,
        0.0,
        1,
        20, 
        bignum_value, 
        278202.292871, 
        72829, 
        3.333333333333,
        0.1,
        1/0.0
      ].map { |n| [-n, n] }.flatten
    end

    it "returns the square of the absolute value of self" do
      @numbers.each do |number|
        number.abs2.should eql(number.abs ** 2)
      end
    end
    
    it "calls #* on self" do
      number = mock_numeric('numeric')
      number.should_receive(:*).and_return(:result)
      number.abs2.should == :result
    end

    it "returns NaN when self is NaN" do
      (0/0.0).abs2.nan?.should be_true
    end
  end
end
