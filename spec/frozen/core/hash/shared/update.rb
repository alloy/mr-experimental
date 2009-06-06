describe :hash_update, :shared => true do
  it "adds the entries from other, overwriting duplicate keys. Returns self" do
    h = new_hash(:_1 => 'a', :_2 => '3')
    h.send(@method, :_1 => '9', :_9 => 2).should equal(h)
    h.should == new_hash(:_1 => "9", :_2 => "3", :_9 => 2)
  end

  it "sets any duplicate key to the value of block if passed a block" do
    h1 = new_hash(:a => 2, :b => -1)
    h2 = new_hash(:a => -2, :c => 1)
    h1.send(@method, h2) { |k,x,y| 3.14 }.should equal(h1)
    h1.should == new_hash(:c => 1, :b => -1, :a => 3.14)

    h1.send(@method, h1) { nil }
    h1.should == new_hash(:a => nil, :b => nil, :c => nil)
  end

  it "tries to convert the passed argument to a hash using #to_hash" do
    obj = mock('{1=>2}')
    obj.should_receive(:to_hash).and_return(new_hash(1 => 2))
    new_hash(3 => 4).send(@method, obj).should == new_hash(1 => 2, 3 => 4)
  end

  it "does not call to_hash on hash subclasses" do
    new_hash(3 => 4).send(@method, ToHashHash[1 => 2]).should == new_hash(1 => 2, 3 => 4)
  end

  it "processes entries with same order as merge()" do
    h = new_hash(1 => 2, 3 => 4, 5 => 6, "x" => nil, nil => 5, [] => [])
    merge_bang_pairs = []
    merge_pairs = []
    h.merge(h) { |*arg| merge_pairs << arg }
    h.send(@method, h) { |*arg| merge_bang_pairs << arg }
    merge_bang_pairs.should == merge_pairs
  end

  ruby_version_is ""..."1.9" do
    it "raises a TypeError if called on a non-empty, frozen instance" do
      HashSpecs.frozen_hash.send(@method, HashSpecs.empty_frozen_hash) # ok, empty
      lambda { HashSpecs.frozen_hash.send(@method, 1 => 2) }.should raise_error(TypeError)
    end
  end
  ruby_version_is "1.9" do
    ruby_bug "#1571", "1.9.2" do
      it "raises a RuntimeError if called on a frozen instance" do
        lambda { HashSpecs.frozen_hash.send(@method, HashSpecs.empty_frozen_hash) }.
          should raise_error(RuntimeError)
        lambda { HashSpecs.frozen_hash.send(@method, 1 => 2) }.
          should raise_error(RuntimeError)
      end
    end
  end
end
