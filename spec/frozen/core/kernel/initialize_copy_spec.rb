require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Kernel#initialize_copy" do
  it "is a private method" do
    Kernel.should have_private_instance_method(:initialize_copy)
  end
end
