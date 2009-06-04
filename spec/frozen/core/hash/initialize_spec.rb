require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Hash#initialize" do
  it "is private" do
    hash_class.should have_private_instance_method("initialize")
  end

  it "can be used to reset default_proc" do
    h = new_hash("foo" => 1, "bar" => 2)
    h.default_proc.should == nil
    h.instance_eval { initialize { |h, k| k * 2 } }
    h.default_proc.should_not == nil
    h["a"].should == "aa"
  end

  it "should get passed whatever args were passed to Hash#new" do
    NewHash.new(:one, :two)[0].should == :one
    NewHash.new(:one, :two)[1].should == :two
  end

  ruby_version_is ""..."1.9" do
    it "raises a TypeError if called on a frozen instance" do
      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize() }}
      block.should raise_error(TypeError)

      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize(nil) }  }
      block.should raise_error(TypeError)

      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize(5) }    }
      block.should raise_error(TypeError)

      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize { 5 } } }
      block.should raise_error(TypeError)
    end
  end

  ruby_version_is "1.9" do
    it "raises a RuntimeError if called on a frozen instance" do
      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize() }}
      block.should raise_error(RuntimeError)

      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize(nil) }  }
      block.should raise_error(RuntimeError)

      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize(5) }    }
      block.should raise_error(RuntimeError)

      block = lambda { HashSpecs.frozen_hash.instance_eval { initialize { 5 } } }
      block.should raise_error(RuntimeError)
    end
  end
end
