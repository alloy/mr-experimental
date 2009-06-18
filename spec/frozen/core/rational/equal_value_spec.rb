require File.dirname(__FILE__) + '/../../shared/rational/equal_value'

ruby_version_is "1.9" do
  describe "Rational#==" do
    it_behaves_like(:rational_equal_value, :==)
  end

  describe "Rational#== when passed a Rational" do
    it_behaves_like(:rational_equal_value_rat, :==)
  end

  describe "Rational#== when passed a Float" do
    it_behaves_like(:rational_equal_value_float, :==)
  end

  describe "Rational#== when passed an Integer" do
    it_behaves_like(:rational_equal_value_int, :==)
  end
end  
