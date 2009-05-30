# -*- encoding: utf-8 -*-
require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes.rb'

ruby_version_is '1.8.7' do
  describe "String#start_with?" do
    it "returns true only if beginning match" do
      s = "hello"
      s.start_with?('h').should be_true
      s.start_with?('hel').should be_true
      s.start_with?('el').should be_false
    end

    it "returns true only if any beginning match" do
      "hello".start_with?('x', 'y', 'he', 'z').should be_true
    end

    it "converts its argument using :to_str" do
      s = "hello"
      find = mock('h')
      find.should_receive(:to_str).and_return("h")
      s.start_with?(find).should be_true
    end

    it "ignores arguments not convertible to string" do
      "hello".start_with?().should be_false
      "hello".start_with?(1).should be_false
      "hello".start_with?(["h"]).should be_false
      "hello".start_with?(1, nil, "h").should be_true
    end

    it "uses only the needed arguments" do
      find = mock('h')
      find.should_not_receive(:to_str)
      "hello".start_with?("h",find).should be_true
    end
  
    it "works for multibyte strings" do
      old_kcode = $KCODE
      begin
        $KCODE = "UTF-8"
        "céréale".start_with?("cér").should be_true
      ensure
        $KCODE = old_kcode
      end
    end
  end
end