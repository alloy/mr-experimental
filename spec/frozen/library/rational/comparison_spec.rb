require File.dirname(__FILE__) + '/../../shared/rational/comparison'

ruby_version_is ""..."1.9" do
  describe "Rational#<=> when passed a Rational object" do
    it_behaves_like(:rational_cmp_rat, :<=>)
  end

  describe "Rational#<=> when passed a Integer object" do
    it_behaves_like(:rational_cmp_int, :<=>)
  end

  describe "Rational#<=> when passed a Float object" do
    it_behaves_like(:rational_cmp_float, :<=>)
  end

  describe "Rational#<=> when passed an Object that responds to #coerce" do
    it_behaves_like(:rational_cmp_coerce, :<=>)
  end

  describe "Rational#<=> when passed a non-Numeric Object that doesn't respond to #coerce" do
    it_behaves_like(:rational_cmp_other, :<=>)
  end
end
