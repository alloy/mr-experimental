module NoMethodErrorSpecs
  class NoMethodErrorA; end

  class NoMethodErrorB; end

  class NoMethodErrorC;
    protected
    def a_protected_method;end
    private
    def a_private_method; end
  end

  class NoMethodErrorD; end
end

module ExceptionSpecs
  class Exceptional < Exception; end
  
  class Backtrace
    def self.backtrace
      begin
        raise
      rescue RuntimeError => e
        e.backtrace
      end
    end
  end

  class UnExceptional < Exception
    def backtrace
      nil
    end
    def message
      nil
    end
  end
end  
