require File.dirname(__FILE__) + '/../../shared/complex/to_s'

ruby_version_is ""..."1.9" do

  require 'complex'

  describe "Complex#to_s when self's real component is 0" do
    it_behaves_like(:complex_to_s_0, :to_s)
  end

  describe "Complex#to_s" do
    it_behaves_like(:complex_to_s, :to_s)
  end
end
