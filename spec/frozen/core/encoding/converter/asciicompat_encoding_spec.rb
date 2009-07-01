require File.dirname(__FILE__) + '/../../../spec_helper'

ruby_version_is "1.9" do
  describe "Encoding::Converter.asciicompat_encoding" do
    it "accepts an encoding name as a String argument" do
      lambda { Encoding::Converter.asciicompat_encoding('UTF-8') }.
        should_not raise_error
    end

    it "coerces non-String/Encoding objects with #to_str" do
      str = mock('string')
      str.should_receive(:to_str).twice.and_return('string')
      Encoding::Converter.asciicompat_encoding(str)
    end

    it "accepts an Encoding object as an argument" do
      Encoding::Converter.
        asciicompat_encoding(Encoding.find("ISO-2022-JP")).
        should == Encoding::Converter.asciicompat_encoding("ISO-2022-JP")
    end

    it "returns a corresponding ASCII compatible encoding for ASCII-incompatible encodings" do
      Encoding::Converter.asciicompat_encoding('UTF-16BE').should == Encoding::UTF_8
      Encoding::Converter.asciicompat_encoding("ISO-2022-JP").should == Encoding.find("stateless-ISO-2022-JP")
    end

    it "returns nil when the given encoding is ASCII compatible" do
      Encoding::Converter.asciicompat_encoding('ASCII').should be_nil
      Encoding::Converter.asciicompat_encoding('UTF-8').should be_nil
    end

    quarantine! do
      # Reported as bug #1659
      it "handles encoding names who resolve to nil encodings" do
        internal = Encoding.default_internal
        Encoding.default_internal = nil
        Encoding::Converter.asciicompat_encoding('internal')
        Encoding.default_internal = internal
      end
    end

    it "returns nil if called with an encoding it returned previously" do
      internal = Encoding.default_internal
      # We set the default_internal encoding explicitly because otherwise we
      # trigger bug #1659
      Encoding.default_internal = 'UTF-8'
      Encoding.name_list.each do |name|
        asciicompat = Encoding::Converter.asciicompat_encoding(name)
        next if asciicompat.nil?
        Encoding::Converter.asciicompat_encoding(asciicompat).should be_nil
      end
      Encoding.default_internal = internal
    end
  end
end
