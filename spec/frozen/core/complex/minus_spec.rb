require File.dirname(__FILE__) + '/../../shared/complex/minus'

ruby_version_is "1.9" do
  describe "Complex#- with Complex" do
    it_behaves_like(:complex_minus_complex, :-)
  end

  describe "Complex#- with Integer" do
    it_behaves_like(:complex_minus_integer, :-)
  end

  describe "Complex#- with Object" do
    it_behaves_like(:complex_minus_object, :-)
  end
end
