require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Kernel.local_variables" do
  it "is a private method" do
    Kernel.should have_private_instance_method(:local_variables)
  end
  
  ruby_version_is ""..."1.9" do
    it "contains locals as they are added" do
      a = 1
      b = 2
      local_variables.should include("a", "b")
    end

    it "is accessable from bindings" do
      def local_var_foo
        a = 1
        b = 2
        binding      
      end
      foo_binding = local_var_foo()
      res = eval("local_variables",foo_binding)
      res.should include("a", "b")
    end
  end

  ruby_version_is "1.9" do
    it "contains locals as they are added" do
      a = 1
      b = 2
      local_variables.should include(:a, :b)
    end

    it "is accessable from bindings" do
      def local_var_foo
        a = 1
        b = 2
        binding      
      end
      foo_binding = local_var_foo()
      res = eval("local_variables",foo_binding)
      res.should include(:a, :b)
    end
  end
end

describe "Kernel#local_variables" do
  it "needs to be reviewed for spec completeness"
end
