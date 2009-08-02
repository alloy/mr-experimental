require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/fixtures/classes'

describe "Thread#status" do
  it "can check it's own status" do
    ThreadSpecs.status_of_current_thread.status.should == 'run'
  end

  it "describes a running thread" do
    ThreadSpecs.status_of_running_thread.status.should == 'run'
  end

  it "describes a sleeping thread" do
    ThreadSpecs.status_of_sleeping_thread.status.should == 'sleep'
  end

  it "describes a blocked thread" do
    ThreadSpecs.status_of_blocked_thread.status.should == 'sleep'
  end

  it "describes a completed thread" do
    ThreadSpecs.status_of_completed_thread.status.should == false
  end

  it "describes a killed thread" do
    ThreadSpecs.status_of_killed_thread.status.should == false
  end

  it "describes a thread with an uncaught exception" do
    ThreadSpecs.status_of_thread_with_uncaught_exception.status.should == nil
  end

  ruby_version_is ""..."1.9" do
    it "describes a dying running thread" do
      ThreadSpecs.status_of_dying_running_thread.status.should == 'aborting'
    end
  end

  it "describes a dying sleeping thread" do
    ThreadSpecs.status_of_dying_sleeping_thread.status.should == 'sleep'
  end

  it "reports aborting on a killed thread" do
    ThreadSpecs.status_of_aborting_thread.status.should == 'aborting'
  end
end
