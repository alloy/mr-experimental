require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/shared/getc'

describe "ARGF.getc" do
  it_behaves_like :argf_getc, :readchar
end

describe "ARGF.readchar" do
  before :each do
    @file1 = fixture __FILE__, "file1.txt"
    @file2 = fixture __FILE__, "file2.txt"
  end

  after :each do
    ARGF.close unless ARGF.closed?
  end

  it "raises EOFError when end of stream reached" do
    argv [@file1, @file2] do
      lambda { while c = ARGF.readchar; end }.should raise_error(EOFError)
    end
  end
end
