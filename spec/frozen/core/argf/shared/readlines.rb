describe :argf_readlines, :shared => true do
  before :each do
    @file1 = fixture __FILE__, "file1.txt"
    @file2 = fixture __FILE__, "file2.txt"

    @lines  = File.readlines(@file1)
    @lines += File.readlines(@file2)
  end

  after :each do
    ARGF.close
  end

  it "reads all lines of all files" do
    argv [@file1, @file2] do
      ARGF.send(@method).should == @lines
    end
  end

  it "returns nil when end of stream reached" do
    argv [@file1, @file2] do
      ARGF.read
      ARGF.send(@method).should == nil
    end
  end
end
