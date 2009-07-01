require File.dirname(__FILE__) + '/../../spec_helper'

ruby_version_is "1.9" do
  describe "Encoding.default_external" do
    before(:all) do
      @original_encoding = Encoding.default_external
    end

    after(:all) do
      Encoding.default_external = @original_encoding
    end

    it "returns an Encoding object" do
      Encoding.default_external.should be_an_instance_of(Encoding)
    end

    it "returns the default external encoding" do
      Encoding.default_external = Encoding::UTF_8
      Encoding.default_external.should == Encoding::UTF_8
    end
  end

  describe "Encoding.default_external=" do
    before(:all) do
      @original_encoding = Encoding.default_external
    end

    after(:all) do
      Encoding.default_external = @original_encoding
    end

    it "sets the default external encoding" do
      Encoding.default_external = Encoding::UTF_8
      Encoding.default_external.should == Encoding::UTF_8
    end

    it "can accept a name of an encoding as a String" do
      Encoding.default_external = 'sjis'
      Encoding.default_external.should == Encoding::SHIFT_JIS
    end

    it "calls #to_s on arguments that are neither Strings nor Encodings" do
      string = mock('string')
      string.should_receive(:to_str).twice.and_return('ascii')
      Encoding.default_external = string
      Encoding.default_external.should == Encoding::ASCII
    end

    it "raises a TypeError unless the argument is an Encoding or convertible to a String" do
      lambda { Encoding.default_external = [] }.should raise_error(TypeError)
    end

    it "raises an ArgumentError if the argument is nil" do
      lambda { Encoding.default_external = nil }.should raise_error(ArgumentError)
    end
  end
end
