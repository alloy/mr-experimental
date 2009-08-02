require File.dirname(__FILE__) + '/caller_fixture1'

module KernelSpecs
  class Methods
    def self.ichi; end
    def ni; end
    class << self
      def san; end
    end

    private

    def self.shi; end
    def juu_shi; end

    class << self
      def roku; end

      private

      def shichi; end
    end

    protected

    def self.hachi; end
    def ku; end

    class << self
      def juu; end

      protected

      def juu_ichi; end
    end

    public

    def self.juu_ni; end
    def juu_san; end
  end

  class A
    def public_method; :public_method; end

    def undefed_method; :undefed_method; end
    undef_method :undefed_method

    protected
    def protected_method; :protected_method; end

    private
    def private_method; :private_method; end
  end

  class Binding
    @@super_secret = "password"

    def initialize(n)
      @secret = n
    end

    def square(n)
      n * n
    end

    def get_binding
      a = true
      @bind = binding

      # Add/Change stuff
      b = true
      @secret += 1

      @bind
    end
  end


  module BlockGiven
    def self.accept_block
      block_given?
    end

    def self.accept_block_as_argument(&block)
      block_given?
    end

    class << self
      define_method(:defined_block) do
        block_given?
      end
    end
  end

  module KernelBlockGiven
    def self.accept_block
      Kernel.block_given?
    end

    def self.accept_block_as_argument(&block)
      Kernel.block_given?
    end

    class << self
      define_method(:defined_block) do
        Kernel.block_given?
      end
    end
  end

  module SelfBlockGiven
    def self.accept_block
      self.send(:block_given?)
    end

    def self.accept_block_as_argument(&block)
      self.send(:block_given?)
    end

    class << self
      define_method(:defined_block) do
        self.send(:block_given?)
      end
    end
  end

  module KernelBlockGiven
    def self.accept_block
      Kernel.block_given?
    end

    def self.accept_block_as_argument(&block)
      Kernel.block_given?
    end

    class << self
      define_method(:defined_block) do
        Kernel.block_given?
      end
    end
  end

  def self.before_and_after
    i = "before"
    cont = callcc { |c| c }
    if cont # nil the second time
      i = "after"
      cont.call
    end
    i
  end

  class IVars
    def initialize
      @secret = 99
    end
  end

  module InstEvalCVar
    instance_eval { @@count = 2 }
  end

  module InstEval
    def self.included(base)
      base.instance_eval { @@count = 2 }
    end
  end

  class IncludesInstEval
    include InstEval
  end

  class EvalTest
    def self.eval_yield_with_binding
      eval("yield", binding)
    end
    def self.call_yield
      yield
    end
  end

  def self.helper_script
    File.dirname(__FILE__) + '/check_expansion.rb'
  end

  module DuplicateM
    def repr
      self.class.name.to_s
    end
  end

  class Duplicate
    attr_accessor :one, :two

    def initialize(one, two)
      @one = one
      @two = two
    end

    def initialize_copy(other)
      ScratchPad.record object_id
    end
  end

  module ParentMixin
    def parent_mixin_method; end
  end

  class Parent
    include ParentMixin
    def parent_method; end
    def another_parent_method; end
  end

  class Child < Parent
    undef_method :parent_method
  end

  class Grandchild < Child
    undef_method :parent_mixin_method
  end
end

# for Kernel#sleep to have Channel in it's specs
# TODO: switch directly to queue for both Kernel#sleep and Thread specs?
unless defined? Channel
  require 'thread'
  class Channel < Queue
    alias receive shift
  end
end
