require File.dirname(__FILE__) + '/../../spec_helper'

ruby_version_is "1.9" do
  
  require File.dirname(__FILE__) + '/../../shared/complex/arg'
  
  describe "Complex#arg" do
    it_behaves_like(:complex_arg, :arg)
  end
end
