require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Thread.stop" do
  it "causes the current thread to sleep indefinitely" do
    t = Thread.new { Thread.stop; 5 }
    Thread.pass while t.status and t.status != 'sleep'
    t.status.should == 'sleep'
    t.run
    t.value.should == 5
  end

  ruby_version_is ""..."1.9" do
    it "resets Thread.critical to false" do
      t = Thread.new { Thread.critical = true; Thread.stop }
      Thread.pass while t.status and t.status != 'sleep'
      Thread.critical.should == false
      t.run
      t.join
    end
  end
end

describe "Thread#stop?" do
  it "can check it's own status" do
    ThreadSpecs.status_of_current_thread.stop?.should == false
  end

  it "describes a running thread" do
    ThreadSpecs.status_of_running_thread.stop?.should == false
  end

  it "describes a sleeping thread" do
    ThreadSpecs.status_of_sleeping_thread.stop?.should == true
  end

  it "describes a blocked thread" do
    ThreadSpecs.status_of_blocked_thread.stop?.should == true
  end

  it "describes a completed thread" do
    ThreadSpecs.status_of_completed_thread.stop?.should == true
  end

  it "describes a killed thread" do
    ThreadSpecs.status_of_killed_thread.stop?.should == true
  end

  it "describes a thread with an uncaught exception" do
    ThreadSpecs.status_of_thread_with_uncaught_exception.stop?.should == true
  end

  it "describes a dying running thread" do
    ThreadSpecs.status_of_dying_running_thread.stop?.should == false
  end

  it "describes a dying sleeping thread" do
    ThreadSpecs.status_of_dying_sleeping_thread.stop?.should == true
  end

  it "reports aborting on a killed thread" do
    ThreadSpecs.status_of_aborting_thread.stop?.should == false
  end
end
