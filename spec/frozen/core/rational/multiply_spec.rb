require File.dirname(__FILE__) + '/../../shared/rational/multiply'

ruby_version_is "1.9" do
  describe "Rational#*" do
    it_behaves_like(:rational_multiply, :*)
  end

  describe "Rational#* passed a Rational" do
    it_behaves_like(:rational_multiply_rat, :*)
  end

  describe "Rational#* passed a Float" do
    it_behaves_like(:rational_multiply_float, :*)
  end

  describe "Rational#* passed an Integer" do
    it_behaves_like(:rational_multiply_int, :*)
  end
end
