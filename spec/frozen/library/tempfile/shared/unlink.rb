describe :tempfile_unlink, :shared => true do
  before(:each) do
    @tempfile = Tempfile.new("specs")
  end

  after(:each) do
    @tempfile.close
  end

  ruby_bug "", "1.8.6" do
    it "unlinks self" do
      path = @tempfile.path
      @tempfile.send(@method)
      File.exists?(path).should be_false
    end
  end
end
