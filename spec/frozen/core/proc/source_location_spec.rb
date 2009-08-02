require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/procs'

ruby_version_is "1.9" do
  describe "Proc#source_location" do
    before(:each) do
      @proc = ProcSpecs::SourceLocation.my_proc
      @lambda = ProcSpecs::SourceLocation.my_lambda
      @proc_new = ProcSpecs::SourceLocation.my_proc_new
    end

    it "returns an Array" do
      @proc.source_location.should be_an_instance_of(Array)
      @proc_new.source_location.should be_an_instance_of(Array)
      @lambda.source_location.should be_an_instance_of(Array)
    end

    it "sets the first value to the path of the file in which the proc was defined" do
      file = @proc.source_location.first
      file.should be_an_instance_of(String)
      file.should == File.dirname(__FILE__) + '/fixtures/procs.rb'

      file = @proc_new.source_location.first
      file.should be_an_instance_of(String)
      file.should == File.dirname(__FILE__) + '/fixtures/procs.rb'

      file = @lambda.source_location.first
      file.should be_an_instance_of(String)
      file.should == File.dirname(__FILE__) + '/fixtures/procs.rb'
    end

    it "sets the last value to a Fixnum representing the line on which the proc was defined" do
      line = @proc.source_location.last 
      line.should be_an_instance_of(Fixnum)
      line.should == 7 

      line = @proc_new.source_location.last 
      line.should be_an_instance_of(Fixnum)
      line.should == 15 

      line = @lambda.source_location.last 
      line.should be_an_instance_of(Fixnum)
      line.should == 11 
    end

    it "works even if the proc was created on the same line" do
      proc { true }.source_location.should == [__FILE__, __LINE__]
      Proc.new { true }.source_location.should == [__FILE__, __LINE__]
      lambda { true }.source_location.should == [__FILE__, __LINE__]
    end

    it "returns the first line of a multi-line proc (i.e. the line containing 'proc do')" do
      ProcSpecs::SourceLocation.my_multiline_proc.source_location.last.should == 19
      ProcSpecs::SourceLocation.my_multiline_proc_new.source_location.last.should == 33
      ProcSpecs::SourceLocation.my_multiline_lambda.source_location.last.should == 26 
    end

    it "returns the location of the proc's body; not necessarily the proc itself" do
      ProcSpecs::SourceLocation.my_detached_proc.source_location.last.should == 40
      ProcSpecs::SourceLocation.my_detached_proc_new.source_location.last.should == 50 
      ProcSpecs::SourceLocation.my_detached_lambda.source_location.last.should ==45 
    end
  end
end
