require File.dirname(__FILE__) + '/../../shared/rational/to_r'

ruby_version_is "1.9" do
  describe "Rational#to_r" do
    it_behaves_like(:rational_to_r, :to_r)
  end
end
