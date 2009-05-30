require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/shared/to_s'

ruby_version_is ""..."1.9" do
  describe "Exception#to_str" do
    it_behaves_like :to_s, :to_str
  end  
end

ruby_version_is "1.9" do
  describe "Exception#to_str" do
    it "has been deprecated" do
      Exception.new.should_not respond_to(:to_str)
    end 
  end  
end

