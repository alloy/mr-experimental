require File.dirname(__FILE__) + '/../../shared/rational/inspect'

ruby_version_is ""..."1.9" do
  describe "Rational#inspect" do
    it_behaves_like(:rational_inspect, :inspect)
  end
end
