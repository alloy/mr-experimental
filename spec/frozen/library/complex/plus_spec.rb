require File.dirname(__FILE__) + '/../../shared/complex/plus'

ruby_version_is ""..."1.9" do

  require 'complex'

  describe "Complex#+ with Complex" do
    it_behaves_like(:complex_plus_complex, :+)
  end

  describe "Complex#+ with Integer" do
    it_behaves_like(:complex_plus_integer, :+)
  end

  describe "Complex#+ with Object" do
    it_behaves_like(:complex_plus_object, :+)
  end
end
