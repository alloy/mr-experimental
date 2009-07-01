require File.dirname(__FILE__) + '/../../../spec_helper'
require File.dirname(__FILE__) + '/shared/atan'

ruby_version_is ""..."1.9" do
  describe "Math#atan" do
    it_behaves_like :complex_math_atan, :_, IncludesMath.new

    it "should be private" do
      IncludesMath.should have_private_instance_method(:atan)
    end
  end

  describe "Math#atan!" do
    it_behaves_like :complex_math_atan_bang, :_, IncludesMath.new

    it "should be private" do
      IncludesMath.should have_private_instance_method(:atan!)
    end
  end

  describe "Math.atan" do
    it_behaves_like :complex_math_atan, :_, Math
  end

  describe "Math.atan!" do
    it_behaves_like :complex_math_atan_bang, :_, Math
  end
end
