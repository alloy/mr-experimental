require File.dirname(__FILE__) + '/../../../spec_helper'

ruby_version_is "1.9" do
  describe "Encoding::Converter#primitive_convert" do
    it "accepts a nil source buffer" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert(nil,"") }.should_not raise_error
    end

    it "accepts a String as the source buffer" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("","") }.should_not raise_error
    end

    it "accepts nil for the destination byte offset" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("","", nil) }.should_not raise_error
    end

    it "accepts an integer for the destination byte offset" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("","a", 1) }.should_not raise_error
    end

    it "raises an ArgumentError if the destination byte offset is greater than the bytesize of the destination buffer" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("","am", 0) }.should_not raise_error
      lambda { ec.primitive_convert("","am", 1) }.should_not raise_error
      lambda { ec.primitive_convert("","am", 2) }.should_not raise_error
      lambda { ec.primitive_convert("","am", 3) }.should raise_error(ArgumentError)
    end

    it "uses the destination byte offset to determine where to write the result in the destination buffer" do
      dest = "aa"
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      ec.primitive_convert("b",dest, nil, 0)
      dest.should == "aa"

      ec.primitive_convert("b",dest, nil, 1)
      dest.should == "aab"

      ec.primitive_convert("b",dest, nil, 2)
      dest.should == "aabbb"
    end

    it "accepts nil for the destination bytesize" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("","", nil, nil) }.should_not raise_error
    end

    it "accepts an integer for the destination bytesize" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("","", nil, 0) }.should_not raise_error
    end

    it "allows a destination bytesize value greater than the bytesize of the source buffer" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("am","", nil, 3) }.should_not raise_error
    end

    it "allows a destination bytesize value less than the bytesize of the source buffer" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      lambda { ec.primitive_convert("am","", nil, 1) }.should_not raise_error
    end

    it "uses destination bytesize as the maximumn bytesize of the destination buffer" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      source = "glark"
      dest = ""
      ec.primitive_convert("glark",dest, nil, 1)
      dest.bytesize.should == 1
    end

    it "allows a destination buffer of unlimited size if destination bytesize is nil" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      source = "glark".force_encoding('utf-8')
      dest = ""
      ec.primitive_convert("glark",dest, nil, nil)
      dest.bytesize.should == source.bytesize
    end

    it "accepts an options hash" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      ec.primitive_convert("","",nil,nil, {:after_output => true})\
        .should_not raise_error(ArgumentError)
    end

    it "sets the destination buffer's encoding to the destination encoding if the conversion suceeded" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      dest = "".force_encoding('utf-8')
      dest.encoding.should == Encoding::UTF_8
      ec.primitive_convert("\u{98}",dest).should == :finished
      dest.encoding.should == Encoding::ISO_8859_1
    end

    it "sets the destination buffer's encoding to the destination encoding if the conversion failed" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      dest = "".force_encoding('utf-8')
      dest.encoding.should == Encoding::UTF_8
      ec.primitive_convert("\u{9878}",dest).should == :undefined_conversion
      dest.encoding.should == Encoding::ISO_8859_1
    end

    it "returns :incomplete_input when source buffer ends unexpectedly and :partial_input isn't specified" do
      ec = Encoding::Converter.new("EUC-JP", "ISO-8859-1")
      ec.primitive_convert("\xa4", "", nil, nil, :partial_input => false).should == :incomplete_input
    end

    it "returns :source_buffer_empty when source buffer ends unexpectedly and :partial_input is true" do
      ec = Encoding::Converter.new("EUC-JP", "ISO-8859-1")
      ec.primitive_convert("\xa4", "", nil, nil, :partial_input => true).should == :source_buffer_empty
    end

    it "returns :undefined_conversion when a character in the source buffer is not representable in the output encoding" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      ec.primitive_convert("\u{9876}","").should == :undefined_conversion
    end

    it "returns :invalid_byte_sequence when an invalid byte sequence was found in the source buffer" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      ec.primitive_convert("\xf1abcd","").should == :invalid_byte_sequence
    end

    it "returns :finished when the conversion succeeded" do
      ec = Encoding::Converter.new("utf-8", "iso-8859-1")
      ec.primitive_convert("glark".force_encoding('utf-8'),"").should == :finished
    end

    it "returns :destination_buffer_full when the destination buffer is too small" do
      ec = Encoding::Converter.new("utf-8", "iso-2022-jp")
      source = "\u{9999}"
      destination_bytesize = source.bytesize - 1
      ec.primitive_convert(source, "", 0, destination_bytesize) \
        .should == :destination_buffer_full
    end
  end
end