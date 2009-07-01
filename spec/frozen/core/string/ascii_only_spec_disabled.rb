# -*- encoding: utf-8 -*-
require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes.rb'

ruby_version_is '1.9' do
  describe "String#ascii_only?" do
    it "returns true if the String contains only US-ASCII characters" do
      "hello".ascii_only?.should be_true
    end
    
    it "returns true if the String contains only US-ASCII characters
    and is encoded as US-ASCII" do
      "hello".force_encoding(Encoding::US_ASCII).ascii_only?.should be_true
      "hello".encode(Encoding::US_ASCII).ascii_only?.should be_true
    end

    it "returns true if the String contains only US-ASCII characters
    and is encoded as UTF-8" do
      "hello".force_encoding('UTF-8').ascii_only?.should be_true
      "hello".encode('UTF-8').ascii_only?.should be_true
    end
    
    it "returns true for all single-character US-ASCII Strings" do
      0.upto(127) do |n|
        n.chr.ascii_only?.should be_true
      end
    end

    it "returns false for the first non-US-ASCII single-character String" do
      chr = 128.chr
      chr.encoding.should == Encoding::ASCII_8BIT
      chr.ascii_only?.should be_false
    end
    
    it "returns false if the String contains only non-US-ASCII characters" do
      "\u{6666}".ascii_only?.should be_false
    end
    
    it "returns false if the String contains only non-US-ASCII characters
    and is encoded as UTF-8" do
      "\u{6666}".force_encoding('UTF-8').ascii_only?.should be_false
      "\u{6666}".encode('UTF-8').ascii_only?.should be_false
    end
    
    it "returns false if the String contains only non-ASCII characters
    and is encoded as US-ASCII" do
      "\u{6666}".force_encoding(Encoding::US_ASCII).ascii_only?.should be_false
    end
    
    it "returns false if the String contains US-ASCII and non-US-ASCII characters" do
      "hello, \u{6666}".ascii_only?.should be_false
    end

    it "returns false if the String contains US-ASCII and non-US-ASCII characters
    and is encoded as US-ASCII" do
      "hello, \u{6666}".force_encoding(Encoding::US_ASCII).ascii_only?.should be_false
    end
    
    it "returns false if the String contains US-ASCII and non-US-ASCII characters
    and is encoded as UTF-8" do
      "hello, \u{6666}".encode('UTF-8').ascii_only?.should be_false
      "hello, \u{6666}".force_encoding('UTF-8').ascii_only?.should be_false
    end
    
    it "accepts no arguments" do
      lambda { "Glark".ascii_only?('?') }.should raise_error(ArgumentError)
    end
    
    it "returns true for the empty String" do
      ''.ascii_only?.should be_true
      ''.encode('UTF-8').ascii_only?.should be_true
    end
  end
end
