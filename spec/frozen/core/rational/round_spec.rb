require File.dirname(__FILE__) + '/../../shared/rational/round'

ruby_version_is "1.9" do
  describe "Rational#round" do
    it_behaves_like(:rational_round, :round)
  end
end
