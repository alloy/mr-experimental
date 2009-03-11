require File.dirname(__FILE__) + '/../../../spec_helper'

process_is_foreground do

  not_supported_on :ironruby do
    require 'readline'
    describe "Readline::HISTORY.push" do
      it "pushes all passed Objects into the history" do
        Readline::HISTORY.push("1", "2", "3")
        Readline::HISTORY.size.should == 3

        Readline::HISTORY.pop.should == "3"
        Readline::HISTORY.pop.should == "2"
        Readline::HISTORY.pop.should == "1"
      end

      it "tries to convert the passed Object to a String using #to_str" do
        obj = mock("Converted to String")
        obj.should_receive(:to_str).and_return("converted")

        Readline::HISTORY.push(obj)
        Readline::HISTORY.pop.should == "converted"
      end

      it "raises a TypeError when the passed Object can't be converted to a String" do
        lambda { Readline::HISTORY.push(mock("Object")) }.should raise_error(TypeError)
      end
    end
  end
end
