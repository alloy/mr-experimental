require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/methods'

describe "Time#_dump" do
  before :each do
    @t = Time.at(946812800)
    @t = @t.gmtime
    @s = @t._dump
  end

  ruby_bug("http://redmine.ruby-lang.org/issues/show/627", "1.8.7") do
    it "preserves the GMT flag" do
      @t.gmt?.should == true
      dump = @t._dump.unpack("VV").first
      ((dump >> 30) & 0x1).should == 1
    end

    it "dumps a Time object to a bytestring" do
      @s.should be_kind_of(String)
      @s.should == [3222863947, 2235564032].pack("VV")
    end

    it "dumps an array with a date as first element" do
      high =                1 << 31 |
            (@t.gmt? ? 1 : 0) << 30 |
             (@t.year - 1900) << 14 |
                (@t.mon  - 1) << 10 |
                       @t.mday << 5 |
                            @t.hour

      high.should == @s.unpack("VV").first
    end
  end

  it "dumps an array with a time as second element" do
    low =  @t.min  << 26 |
           @t.sec  << 20 |
           @t.usec
    low.should == @s.unpack("VV").last
  end
end

