require File.dirname(__FILE__) + '/../../spec_helper'
require File.dirname(__FILE__) + '/shared/next'
require 'prime'

describe "Prime#succ" do
  it_behaves_like :prime_next, :succ
end


