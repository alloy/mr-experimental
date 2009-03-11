require 'test/unit'

class RationalSub < Rational; end

class Rational_Test < Test::Unit::TestCase

  def test_ratsub
    c = RationalSub.__send__(:new, 1)
    cc = RationalSub.__send__(:convert, 1)
    if defined?(RationalSub::Unify)
      assert_instance_of(Fixnum, c)
      assert_instance_of(Fixnum, cc)
    else
      assert_instance_of(RationalSub, c)
      assert_instance_of(RationalSub, cc)

      c2 = c + 1
      assert_instance_of(RationalSub, c2)
      c2 = c - 1
      assert_instance_of(RationalSub, c2)

      c3 = c - c2
      assert_instance_of(RationalSub, c3)

      s = Marshal.dump(c)
      c5 = Marshal.load(s)
      assert_equal(c, c5)
      assert_instance_of(RationalSub, c5)
    end
  end

  def test_hash
    assert_instance_of(Fixnum, Rational(1,2).hash)

    h = {}
    h[Rational(0)] = 0
    h[Rational(1,1)] = 1
    h[Rational(2,1)] = 2
    h[Rational(3,1)] = 3

    assert_equal(4, h.size)
    assert_equal(2, h[Rational(2,1)])

    h[Rational(0,1)] = 9
    assert_equal(4, h.size)
  end

  def test_freeze
    c = Rational(1)
    c.freeze
    unless defined?(Rational::Unify)
      assert_equal(true, c.frozen?)
    end
    assert_instance_of(String, c.to_s)
  end

  def test_new_bang # no unify & no reduce
    assert_instance_of(Rational, Rational.__send__(:new!, 2,1))
    assert_equal([2,1], Rational.__send__(:new!, 2,1).
		 instance_eval{[numerator, denominator]})
    assert_equal([2,4],  Rational.__send__(:new!, 2,4).
		 instance_eval{[numerator, denominator]})
    assert_equal([-2,4], Rational.__send__(:new!, -2,4).
		 instance_eval{[numerator, denominator]})
    assert_equal([-2,4], Rational.__send__(:new!, 2,-4).
		 instance_eval{[numerator, denominator]})
    assert_equal([2,4], Rational.__send__(:new!, -2,-4).
		 instance_eval{[numerator, denominator]})

    # to_i
    assert_equal([2,1], Rational.__send__(:new!, Rational(2)).
		 instance_eval{[numerator, denominator]})
    assert_equal([2,3], Rational.__send__(:new!, Rational(2), Rational(3)).
		 instance_eval{[numerator, denominator]})
    assert_equal([2,3], Rational.__send__(:new!, 2, Rational(3)).
		 instance_eval{[numerator, denominator]})

    assert_equal([1,1], Rational.__send__(:new!, 1.1).
		 instance_eval{[numerator, denominator]})
    assert_equal([-1,1], Rational.__send__(:new!, -1.1).
		 instance_eval{[numerator, denominator]})
    assert_equal([1,1], Rational.__send__(:new!, '1').
		 instance_eval{[numerator, denominator]})
    assert_equal([0,1], Rational.__send__(:new!, nil).
		 instance_eval{[numerator, denominator]})
  end

=begin
  def test_reduce
    if defined?(Rational::Unify)
      assert_instance_of(Fixnum, Rational.__send__(:reduce, 2,1))
    else
      assert_instance_of(Rational, Rational.__send__(:reduce, 2,1))
      assert_instance_of(Rational, Rational.__send__(:reduce, 2,1))
    end
    assert_equal([2,1], Rational.__send__(:reduce, 2,1).
		 instance_eval{[numerator, denominator]})
    assert_equal([1,2], Rational.__send__(:reduce, 2,4).
		 instance_eval{[numerator, denominator]})
    assert_equal([-1,2], Rational.__send__(:reduce, -2,4).
		 instance_eval{[numerator, denominator]})
    assert_equal([-1,2], Rational.__send__(:reduce, 2,-4).
		 instance_eval{[numerator, denominator]})
    assert_equal([1,2], Rational.__send__(:reduce, -2,-4).
		 instance_eval{[numerator, denominator]})

    assert_raise(ArgumentError){Rational.__send__(:reduce, Rational(1,2),2)}
    assert_raise(ArgumentError){Rational.__send__(:reduce, 2,Rational(1,2))}
    assert_raise(ArgumentError){Rational.
      __send__(:reduce, Rational(1,2),Rational(1,2))}

    assert_raise(ArgumentError){Rational.__send__(:reduce, 1.1)}
    assert_raise(ArgumentError){Rational.__send__(:reduce, -1.1)}
    assert_raise(ArgumentError){Rational.__send__(:reduce, '1')}
    assert_raise(ArgumentError){Rational.__send__(:reduce, nil)}
  end
=end

  def test_new
    if defined?(Rational::Unify)
      assert_instance_of(Fixnum, Rational.__send__(:new, 2,1))
    else
      assert_instance_of(Rational, Rational.__send__(:new, 2,1))
      assert_equal([2,1], Rational.__send__(:new, 2,1).
		   instance_eval{[numerator, denominator]})
    end
    assert_equal([1,2], Rational.__send__(:new, 2,4).
		 instance_eval{[numerator, denominator]})
    assert_equal([-1,2], Rational.__send__(:new, -2,4).
		 instance_eval{[numerator, denominator]})
    assert_equal([-1,2], Rational.__send__(:new, 2,-4).
		 instance_eval{[numerator, denominator]})
    assert_equal([1,2], Rational.__send__(:new, -2,-4).
		 instance_eval{[numerator, denominator]})

    assert_raise(ArgumentError){Rational.__send__(:new, Rational(1,2),2)}
    assert_raise(ArgumentError){Rational.__send__(:new, 2,Rational(1,2))}
    assert_raise(ArgumentError){Rational.__send__(:new, Rational(1,2),Rational(1,2))}

    assert_raise(ArgumentError){Rational.__send__(:new, 1.1)}
    assert_raise(ArgumentError){Rational.__send__(:new, -1.1)}
    assert_raise(ArgumentError){Rational.__send__(:new, '1')}
    assert_raise(ArgumentError){Rational.__send__(:new, nil)}
=begin
    assert_raise(ArgumentError){Rational.__send__(:new, Rational(1))}
    if defined?(Complex)
      assert_raise(ArgumentError){Rational.__send__(:new, Complex(1))}
    end
=end
  end

  def test_conv
    c = Rational(0,1)
    assert_equal(Rational.__send__(:new, 0,1), c)

    c = Rational(2**32, 2**32)
    assert_equal(Rational.__send__(:new, 2**32,2**32), c)
    assert_equal([1,1], [c.numerator,c.denominator])

    c = Rational(-2**32, 2**32)
    assert_equal(Rational.__send__(:new, -2**32,2**32), c)
    assert_equal([-1,1], [c.numerator,c.denominator])

    c = Rational(2**32, -2**32)
    assert_equal(Rational.__send__(:new, 2**32,-2**32), c)
    assert_equal([-1,1], [c.numerator,c.denominator])

    c = Rational(-2**32, -2**32)
    assert_equal(Rational.__send__(:new, -2**32,-2**32), c)
    assert_equal([1,1], [c.numerator,c.denominator])

    c = Rational(Rational(1,2),2)
    assert_equal(Rational.__send__(:new, 1,4), c)

    c = Rational(2,Rational(1,2))
    assert_equal(Rational.__send__(:new, 4), c)

    c = Rational(Rational(1,2),Rational(1,2))
    assert_equal(Rational.__send__(:new, 1), c)

    assert_equal(Rational.__send__(:new, 1),Rational(1))
    assert_equal(1.1.to_r,Rational(1.1))
    assert_equal(Rational.__send__(:new, 1),Rational('1'))
    assert_raise(ArgumentError){Rational(nil)}
  end

  def test_attr
    c = Rational(4)

    assert_equal(4, c.numerator)
    assert_equal(1, c.denominator)

    c = Rational(4,5)

    assert_equal(4, c.numerator)
    assert_equal(5, c.denominator)

    c = Rational.__send__(:new, 4)

    assert_equal(4, c.numerator)
    assert_equal(1, c.denominator)

    c = Rational.__send__(:new, 4,5)

    assert_equal(4, c.numerator)
    assert_equal(5, c.denominator)

    c = Rational.__send__(:new!, 4)

    assert_equal(4, c.numerator)
    assert_equal(1, c.denominator)

    c = Rational.__send__(:new!, 4,5)

    assert_equal(4, c.numerator)
    assert_equal(5, c.denominator)
  end

  def test_attr2
    c = Rational(1)

    if defined?(Rational::Unify)
      assert_equal(true, c.scalar?)
=begin
      assert_equal(true, c.finite?)
      assert_equal(false, c.infinite?)
      assert_equal(false, c.nan?)
      assert_equal(true, c.integer?)
      assert_equal(false, c.float?)
      assert_equal(true, c.rational?)
      assert_equal(true, c.real?)
      assert_equal(false, c.complex?)
      assert_equal(true, c.exact?)
      assert_equal(false, c.inexact?)
=end
    else
      assert_equal(true, c.scalar?)
=begin
      assert_equal(true, c.finite?)
      assert_equal(false, c.infinite?)
      assert_equal(false, c.nan?)
      assert_equal(false, c.integer?)
      assert_equal(false, c.float?)
      assert_equal(true, c.rational?)
      assert_equal(true, c.real?)
      assert_equal(false, c.complex?)
      assert_equal(true, c.exact?)
      assert_equal(false, c.inexact?)
=end
    end

=begin
    assert_equal(true, Rational(0).positive?)
    assert_equal(true, Rational(1).positive?)
    assert_equal(false, Rational(-1).positive?)
    assert_equal(false, Rational(0).negative?)
    assert_equal(false, Rational(1).negative?)
    assert_equal(true, Rational(-1).negative?)

    assert_equal(0, Rational(0).sign)
    assert_equal(1, Rational(2).sign)
    assert_equal(-1, Rational(-2).sign)
=end

    assert_equal(true, Rational(0).zero?)
    assert_equal(true, Rational(0,1).zero?)
    assert_equal(false, Rational(1,1).zero?)

    assert_equal(nil, Rational(0).nonzero?)
    assert_equal(nil, Rational(0,1).nonzero?)
    assert_equal(Rational(1,1), Rational(1,1).nonzero?)
  end

  def test_uplus
    assert_equal(Rational(1), +Rational(1))
    assert_equal(Rational(-1), +Rational(-1))
    assert_equal(Rational(1,1), +Rational(1,1))
    assert_equal(Rational(-1,1), +Rational(-1,1))
    assert_equal(Rational(-1,1), +Rational(1,-1))
    assert_equal(Rational(1,1), +Rational(-1,-1))
  end

  def test_negate
    assert_equal(Rational(-1), -Rational(1))
    assert_equal(Rational(1), -Rational(-1))
    assert_equal(Rational(-1,1), -Rational(1,1))
    assert_equal(Rational(1,1), -Rational(-1,1))
    assert_equal(Rational(1,1), -Rational(1,-1))
    assert_equal(Rational(-1,1), -Rational(-1,-1))

=begin
    assert_equal(0, Rational(0).negate)
    assert_equal(-2, Rational(2).negate)
    assert_equal(2, Rational(-2).negate)
=end
  end

  def test_add
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_equal(Rational(7,6), c + c2)

    assert_equal(Rational(5,2), c + 2)
    assert_equal(2.5, c + 2.0)
  end

  def test_sub
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_equal(Rational(-1,6), c - c2)

    assert_equal(Rational(-3,2), c - 2)
    assert_equal(-1.5, c - 2.0)
  end

  def test_mul
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_equal(Rational(1,3), c * c2)

    assert_equal(Rational(1,1), c * 2)
    assert_equal(1.0, c * 2.0)
  end

  def test_div
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_equal(Rational(3,4), c / c2)

    assert_equal(Rational(1,4), c / 2)
    assert_equal(0.25, c / 2.0)
  end

  def assert_eql(exp, act, *args)
    unless Array === exp
      exp = [exp]
    end
    unless Array === act
      act = [act]
    end
    exp.zip(act).each do |e, a|
      na = [e, a] + args
      assert_equal(*na)
      na = [e.class, a] + args
      assert_instance_of(*na)
    end
  end

  def test_idiv
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_eql(0, c.div(c2))
    assert_eql(0, c.div(2))
    assert_eql(0, c.div(2.0))

    c = Rational(301,100)
    c2 = Rational(7,5)

    assert_equal(2, c.div(c2))
    assert_equal(-3, c.div(-c2))
    assert_equal(-3, (-c).div(c2))
    assert_equal(2, (-c).div(-c2))

    c = Rational(301,100)
    c2 = Rational(2)

    assert_equal(1, c.div(c2))
    assert_equal(-2, c.div(-c2))
    assert_equal(-2, (-c).div(c2))
    assert_equal(1, (-c).div(-c2))

    unless defined?(Rational::Unify)
      c = Rational(11)
      c2 = Rational(3)

      assert_equal(3, c.div(c2))
      assert_equal(-4, c.div(-c2))
      assert_equal(-4, (-c).div(c2))
      assert_equal(3, (-c).div(-c2))
    end
  end

  def test_divmod
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_eql([0, Rational(1,2)], c.divmod(c2))
    assert_eql([0, Rational(1,2)], c.divmod(2))
    assert_eql([0, 0.5], c.divmod(2.0))

    c = Rational(301,100)
    c2 = Rational(7,5)

    assert_equal([2, Rational(21,100)], c.divmod(c2))
    assert_equal([-3, Rational(-119,100)], c.divmod(-c2))
    assert_equal([-3, Rational(119,100)], (-c).divmod(c2))
    assert_equal([2, Rational(-21,100)], (-c).divmod(-c2))

    c = Rational(301,100)
    c2 = Rational(2)

    assert_equal([1, Rational(101,100)], c.divmod(c2))
    assert_equal([-2, Rational(-99,100)], c.divmod(-c2))
    assert_equal([-2, Rational(99,100)], (-c).divmod(c2))
    assert_equal([1, Rational(-101,100)], (-c).divmod(-c2))

    unless defined?(Rational::Unify)
      c = Rational(11)
      c2 = Rational(3)

      assert_equal([3,2], c.divmod(c2))
      assert_equal([-4,-1], c.divmod(-c2))
      assert_equal([-4,1], (-c).divmod(c2))
      assert_equal([3,-2], (-c).divmod(-c2))
    end
  end

=begin
  def test_quot
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_eql(0, c.quot(c2))
    assert_eql(0, c.quot(2))
    assert_eql(0, c.quot(2.0))

    c = Rational(301,100)
    c2 = Rational(7,5)

    assert_equal(2, c.quot(c2))
    assert_equal(-2, c.quot(-c2))
    assert_equal(-2, (-c).quot(c2))
    assert_equal(2, (-c).quot(-c2))

    c = Rational(301,100)
    c2 = Rational(2)

    assert_equal(1, c.quot(c2))
    assert_equal(-1, c.quot(-c2))
    assert_equal(-1, (-c).quot(c2))
    assert_equal(1, (-c).quot(-c2))

    unless defined?(Rational::Unify)
      c = Rational(11)
      c2 = Rational(3)

      assert_equal(3, c.quot(c2))
      assert_equal(-3, c.quot(-c2))
      assert_equal(-3, (-c).quot(c2))
      assert_equal(3, (-c).quot(-c2))
    end
  end

  def test_quotrem
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_eql([0, Rational(1,2)], c.quotrem(c2))
    assert_eql([0, Rational(1,2)], c.quotrem(2))
    assert_eql([0, 0.5], c.quotrem(2.0))

    c = Rational(301,100)
    c2 = Rational(7,5)

    assert_equal([2, Rational(21,100)], c.quotrem(c2))
    assert_equal([-2, Rational(21,100)], c.quotrem(-c2))
    assert_equal([-2, Rational(-21,100)], (-c).quotrem(c2))
    assert_equal([2, Rational(-21,100)], (-c).quotrem(-c2))

    c = Rational(301,100)
    c2 = Rational(2)

    assert_equal([1, Rational(101,100)], c.quotrem(c2))
    assert_equal([-1, Rational(101,100)], c.quotrem(-c2))
    assert_equal([-1, Rational(-101,100)], (-c).quotrem(c2))
    assert_equal([1, Rational(-101,100)], (-c).quotrem(-c2))

    unless defined?(Rational::Unify)
      c = Rational(11)
      c2 = Rational(3)

      assert_equal([3,2], c.quotrem(c2))
      assert_equal([-3,2], c.quotrem(-c2))
      assert_equal([-3,-2], (-c).quotrem(c2))
      assert_equal([3,-2], (-c).quotrem(-c2))
    end
  end
=end

  def test_quo
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_equal(Rational(3,4), c.quo(c2))

    assert_equal(Rational(1,4), c.quo(2))
    assert_equal(Rational(0.25), c.quo(2.0))
  end

  def test_fdiv
    c = Rational(1,2)
    c2 = Rational(2,3)

    assert_equal(0.75, c.fdiv(c2))

    assert_equal(0.25, c.fdiv(2))
    assert_equal(0.25, c.fdiv(2.0))
  end

  def test_expt
    c = Rational(1,2)
    c2 = Rational(2,3)

    r = c ** c2
    assert_in_delta(0.6299, r, 0.001)

    assert_equal(Rational(1,4), c ** 2)
    assert_equal(Rational(4), c ** -2)
    assert_equal(Rational(1,4), (-c) ** 2)
    assert_equal(Rational(4), (-c) ** -2)

    assert_equal(0.25, c ** 2.0)
    assert_equal(4.0, c ** -2.0)

    assert_equal(Rational(1,4), c ** Rational(2))
    assert_equal(Rational(4), c ** Rational(-2))

    assert_equal(Rational(1), 0 ** Rational(0))
    assert_equal(Rational(1), Rational(0) ** 0)
    assert_equal(Rational(1), Rational(0) ** Rational(0))

    # p ** p
    x = 2 ** Rational(2)
    assert_equal(Rational(4), x)
    unless defined?(Rational::Unify)
      assert_instance_of(Rational, x)
    end
    assert_equal(4, x.numerator)
    assert_equal(1, x.denominator)

    x = Rational(2) ** 2
    assert_equal(Rational(4), x)
    unless defined?(Rational::Unify)
      assert_instance_of(Rational, x)
    end
    assert_equal(4, x.numerator)
    assert_equal(1, x.denominator)

    x = Rational(2) ** Rational(2)
    assert_equal(Rational(4), x)
    unless defined?(Rational::Unify)
      assert_instance_of(Rational, x)
    end
    assert_equal(4, x.numerator)
    assert_equal(1, x.denominator)

    # -p ** p
    x = (-2) ** Rational(2)
    assert_equal(Rational(4), x)
    unless defined?(Rational::Unify)
      assert_instance_of(Rational, x)
    end
    assert_equal(4, x.numerator)
    assert_equal(1, x.denominator)

    x = Rational(-2) ** 2
    assert_equal(Rational(4), x)
    unless defined?(Rational::Unify)
      assert_instance_of(Rational, x)
    end
    assert_equal(4, x.numerator)
    assert_equal(1, x.denominator)

    x = Rational(-2) ** Rational(2)
    assert_equal(Rational(4), x)
    unless defined?(Rational::Unify)
      assert_instance_of(Rational, x)
    end
    assert_equal(4, x.numerator)
    assert_equal(1, x.denominator)

    # p ** -p
    x = 2 ** Rational(-2)
    assert_equal(Rational(1,4), x)
    assert_instance_of(Rational, x)
    assert_equal(1, x.numerator)
    assert_equal(4, x.denominator)

    x = Rational(2) ** -2
    assert_equal(Rational(1,4), x)
    assert_instance_of(Rational, x)
    assert_equal(1, x.numerator)
    assert_equal(4, x.denominator)

    x = Rational(2) ** Rational(-2)
    assert_equal(Rational(1,4), x)
    assert_instance_of(Rational, x)
    assert_equal(1, x.numerator)
    assert_equal(4, x.denominator)

    # -p ** -p
    x = (-2) ** Rational(-2)
    assert_equal(Rational(1,4), x)
    assert_instance_of(Rational, x)
    assert_equal(1, x.numerator)
    assert_equal(4, x.denominator)

    x = Rational(-2) ** -2
    assert_equal(Rational(1,4), x)
    assert_instance_of(Rational, x)
    assert_equal(1, x.numerator)
    assert_equal(4, x.denominator)

    x = Rational(-2) ** Rational(-2)
    assert_equal(Rational(1,4), x)
    assert_instance_of(Rational, x)
    assert_equal(1, x.numerator)
    assert_equal(4, x.denominator)
  end

  def test_cmp
    assert_equal(-1, Rational(-1) <=> Rational(0))
    assert_equal(0, Rational(0) <=> Rational(0))
    assert_equal(+1, Rational(+1) <=> Rational(0))

    assert_equal(-1, Rational(-1) <=> 0)
    assert_equal(0, Rational(0) <=> 0)
    assert_equal(+1, Rational(+1) <=> 0)

    assert_equal(-1, Rational(-1) <=> 0.0)
    assert_equal(0, Rational(0) <=> 0.0)
    assert_equal(+1, Rational(+1) <=> 0.0)

    assert_equal(-1, Rational(1,2) <=> Rational(2,3))
    assert_equal(0, Rational(2,3) <=> Rational(2,3))
    assert_equal(+1, Rational(2,3) <=> Rational(1,2))

    f = 2**30-1
    b = 2**30

    assert_equal(0, Rational(f) <=> Rational(f))
    assert_equal(-1, Rational(f) <=> Rational(b))
    assert_equal(+1, Rational(b) <=> Rational(f))
    assert_equal(0, Rational(b) <=> Rational(b))

    assert_equal(-1, Rational(f-1) <=> Rational(f))
    assert_equal(+1, Rational(f) <=> Rational(f-1))
    assert_equal(-1, Rational(b-1) <=> Rational(b))
    assert_equal(+1, Rational(b) <=> Rational(b-1))

    assert_equal(false, Rational(0) < Rational(0))
    assert_equal(true, Rational(0) <= Rational(0))
    assert_equal(true, Rational(0) >= Rational(0))
    assert_equal(false, Rational(0) > Rational(0))
  end

  def test_equal
    assert(Rational(1,1) == Rational(1))
    assert(Rational(1,1) == Rational.__send__(:new, 1))
    assert(Rational(1,1) == Rational.__send__(:new, 1,1))
    assert(Rational(1,1) == Rational.__send__(:new!, 1))
    assert(Rational(1,1) == Rational.__send__(:new!, 1,1))

    assert(Rational(-1,1) == Rational(-1))
    assert(Rational(-1,1) == Rational.__send__(:new, -1))
    assert(Rational(-1,1) == Rational.__send__(:new, -1,1))
    assert(Rational(-1,1) == Rational.__send__(:new!, -1))
    assert(Rational(-1,1) == Rational.__send__(:new!, -1,1))

    assert_equal(false, Rational(2,1) == Rational(1))
    assert_equal(true, Rational(2,1) != Rational(1))
    assert_equal(false, Rational(1) == nil)
    assert_equal(false, Rational(1) == '')

    assert_equal(false, Rational(1,2**100) == 1)
  end

  def test_unify
    if defined?(Rational::Unify)
      assert_instance_of(Fixnum, Rational(1,2) + Rational(1,2))
      assert_instance_of(Fixnum, Rational(1,2) - Rational(1,2))
      assert_instance_of(Fixnum, Rational(1,2) * 2)
      assert_instance_of(Fixnum, Rational(1,2) / Rational(1,2))
      assert_instance_of(Fixnum, Rational(1,2).div(Rational(1,2)))
      assert_instance_of(Fixnum, Rational(1,2).quo(Rational(1,2)))
      assert_instance_of(Fixnum, Rational(1,2) ** -2)
    end
  end

  def test_to_s
    c = Rational(1,2)

    assert_instance_of(String, c.to_s)
    assert_equal('1/2', c.to_s)

    assert_equal('0', Rational(0,2).to_s)
    assert_equal('0', Rational(0,-2).to_s)
    assert_equal('1/2', Rational(1,2).to_s)
    assert_equal('-1/2', Rational(-1,2).to_s)
    assert_equal('1/2', Rational(-1,-2).to_s)
    assert_equal('-1/2', Rational(1,-2).to_s)
    assert_equal('1/2', Rational(-1,-2).to_s)
  end

  def test_inspect
    c = Rational(1,2)

    assert_instance_of(String, c.inspect)
    assert_equal('Rational(1, 2)', c.inspect)
  end

  def test_marshal
    c = Rational(1,2)

    s = Marshal.dump(c)
    c2 = Marshal.load(s)
    assert_equal(c, c2)
    assert_instance_of(Rational, c2)
  end

  def test_parse
    assert_equal(Rational(0), ''.to_r)
    assert_equal(Rational(0), ' '.to_r)
    assert_equal(Rational(5), '5'.to_r)
    assert_equal(Rational(-5), '-5'.to_r)
    assert_equal(Rational(5,3), '5/3'.to_r)
    assert_equal(Rational(-5,3), '-5/3'.to_r)
    assert_equal(Rational(5,-3), '5/-3'.to_r)
    assert_equal(Rational(-5,-3), '-5/-3'.to_r)

    assert_equal(Rational(5), '5.0'.to_r)
    assert_equal(Rational(-5), '-5.0'.to_r)
    assert_equal(Rational(5,3), '5.0/3'.to_r)
    assert_equal(Rational(-5,3), '-5.0/3'.to_r)
    assert_equal(Rational(5,-3), '5.0/-3'.to_r)
    assert_equal(Rational(-5,-3), '-5.0/-3'.to_r)

    assert_equal(Rational(5), '5e0'.to_r)
    assert_equal(Rational(-5), '-5e0'.to_r)
    assert_equal(Rational(5,3), '5e0/3'.to_r)
    assert_equal(Rational(-5,3), '-5e0/3'.to_r)
    assert_equal(Rational(5,-3), '5e0/-3'.to_r)
    assert_equal(Rational(-5,-3), '-5e0/-3'.to_r)

    assert_equal(Rational(33,100), '0.33'.to_r)
    assert_equal(Rational(-33,100), '-0.33'.to_r)
    assert_equal(Rational(-33,100), '-0.3_3'.to_r)

    assert_equal(Rational(1,2), '5e-1'.to_r)
    assert_equal(Rational(50), '5e+1'.to_r)
    assert_equal(Rational(1,2), '5.0e-1'.to_r)
    assert_equal(Rational(50), '5.0e+1'.to_r)
    assert_equal(Rational(50), '5e1'.to_r)
    assert_equal(Rational(50), '5E1'.to_r)
    assert_equal(Rational(500), '5e2'.to_r)
    assert_equal(Rational(5000), '5e3'.to_r)
    assert_equal(Rational(500000000000), '5e1_1'.to_r)

    assert_equal(Rational(5), Rational('5'))
    assert_equal(Rational(-5), Rational('-5'))
    assert_equal(Rational(5,3), Rational('5/3'))
    assert_equal(Rational(-5,3), Rational('-5/3'))
    assert_equal(Rational(5,-3), Rational('5/-3'))
    assert_equal(Rational(-5,-3), Rational('-5/-3'))

    assert_equal(Rational(33,100), Rational('0.33'))
    assert_equal(Rational(-33,100), Rational('-0.33'))
    assert_equal(Rational(-33,100), Rational('-0.3_3'))

    assert_equal(Rational(1,2), Rational('5e-1'))
    assert_equal(Rational(50), Rational('5e1'))
    assert_equal(Rational(50), Rational('5E1'))
    assert_equal(Rational(500), Rational('5e2'))
    assert_equal(Rational(5000), Rational('5e3'))
    assert_equal(Rational(500000000000), Rational('5e1_1'))

    assert_equal(Rational(5.0), Rational('5.0'))
    assert_equal(Rational(-5.0), Rational('-5.0'))
    assert_equal(Rational(5.0,3), Rational('5.0/3'))
    assert_equal(Rational(-5.0,3), Rational('-5.0/3'))
    assert_equal(Rational(5.0,-3), Rational('5.0/-3'))
    assert_equal(Rational(-5.0,-3), Rational('-5.0/-3'))

    assert_equal(Rational(0), '_'.to_r)
    assert_equal(Rational(0), '_5'.to_r)
    assert_equal(Rational(5), '5_'.to_r)
    assert_equal(Rational(5), '5x'.to_r)
    assert_equal(Rational(5), '5/_3'.to_r)
    assert_equal(Rational(5,3), '5/3_'.to_r)
    assert_equal(Rational(5,3), '5/3.3'.to_r)
    assert_equal(Rational(5,3), '5/3x'.to_r)
    assert_raise(ArgumentError){ Rational('')}
    assert_raise(ArgumentError){ Rational('_')}
    assert_raise(ArgumentError){ Rational('_5')}
    assert_raise(ArgumentError){ Rational('5_')}
    assert_raise(ArgumentError){ Rational('5x')}
    assert_raise(ArgumentError){ Rational('5/_3')}
    assert_raise(ArgumentError){ Rational('5/3_')}
    assert_raise(ArgumentError){ Rational('5/3.3')}
    assert_raise(ArgumentError){ Rational('5/3x')}
  end

=begin
  def test_reciprocal
    assert_equal(Rational(1,9), Rational(9,1).reciprocal)
    assert_equal(Rational(9,1), Rational(1,9).reciprocal)
    assert_equal(Rational(-1,9), Rational(-9,1).reciprocal)
    assert_equal(Rational(-9,1), Rational(-1,9).reciprocal)
  end
=end

  def test_to_i
    assert_equal(1, Rational(3,2).to_i)
    assert_equal(1, Integer(Rational(3,2)))
  end

  def test_to_f
    assert_equal(1.5, Rational(3,2).to_f)
    assert_equal(1.5, Float(Rational(3,2)))
  end

  def test_to_c
    if defined?(Complex) && !Complex.instance_variable_get('@RCS_ID')
      if defined?(Rational::Unify)
	assert_equal(Rational(3,2), Rational(3,2).to_c)
	assert_equal(Rational(3,2), Complex(Rational(3,2)))
      else
	assert_equal(Complex(Rational(3,2)), Rational(3,2).to_c)
	assert_equal(Complex(Rational(3,2)), Complex(Rational(3,2)))
      end
    end
  end

  def test_to_r
    c = nil.to_r
    assert_equal([0,1] , [c.numerator, c.denominator])

    c = 0.to_r
    assert_equal([0,1] , [c.numerator, c.denominator])

    c = 1.to_r
    assert_equal([1,1] , [c.numerator, c.denominator])

    c = 1.1.to_r
    assert_equal([2476979795053773, 2251799813685248],
		 [c.numerator, c.denominator])

    c = Rational(1,2).to_r
    assert_equal([1,2] , [c.numerator, c.denominator])

    if defined?(Complex)
      if Complex.instance_variable_get('@RCS_ID')
	assert_raise(NoMethodError){Complex(1,2).to_r}
      else
	assert_raise(RangeError){Complex(1,2).to_r}
      end
    end
  end

  def test_prec
    assert_equal(true, Rational < Precision)

    c = Rational(3,2)

    assert_eql(1, c.prec(Integer))
    assert_eql(1.5, c.prec(Float))
    assert_eql(c, c.prec(Rational))
  end

  def test_supp
    assert_equal(true, 1.scalar?)
    assert_equal(true, 1.1.scalar?)

    if defined?(Complex)
      assert_equal(1, 1.real)
      assert_equal(0, 1.image)
      assert_equal(0, 1.imag)

      assert_equal(1.1, 1.1.real)
      assert_equal(0, 1.1.image)
      assert_equal(0, 1.1.imag)

      assert_equal(0, 1.arg)
      assert_equal(0, 1.angle)

      assert_equal(0, 1.0.arg)
      assert_equal(0, 1.0.angle)

      assert_equal(Math::PI, -1.arg)
      assert_equal(Math::PI, -1.angle)

      assert_equal(Math::PI, -1.0.arg)
      assert_equal(Math::PI, -1.0.angle)

      assert_equal([1,0], 1.polar)
      assert_equal([1, Math::PI], -1.polar)

      assert_equal([1.0,0], 1.0.polar)
      assert_equal([1.0, Math::PI], -1.0.polar)

      assert_equal(1, 1.conjugate)
      assert_equal(-1, -1.conjugate)
      assert_equal(1, 1.conj)
      assert_equal(-1, -1.conj)

      assert_equal(1.1, 1.1.conjugate)
      assert_equal(-1.1, -1.1.conjugate)
      assert_equal(1.1, 1.1.conj)
      assert_equal(-1.1, -1.1.conj)
    end

    assert_equal(1, 1.numerator)
    assert_equal(9, 9.numerator)
    assert_equal(1, 1.denominator)
    assert_equal(1, 9.denominator)

    assert_equal(1.0, 1.0.numerator)
    assert_equal(9.0, 9.0.numerator)
    assert_equal(1.0, 1.0.denominator)
    assert_equal(1.0, 9.0.denominator)

=begin
    assert_equal(Rational(1,9), 9.reciprocal)
    assert_equal(Rational(1,9), 9.0.reciprocal)
    assert_equal(Rational(1,9), 9.inverse)
    assert_equal(Rational(1,9), 9.0.inverse)
=end

    assert_equal(Rational(1,2), 1.quo(2))
    assert_equal(Rational(5000000000), 10000000000.quo(2))
    assert_equal(Rational(1,2), 1.0.quo(2))
    assert_equal(Rational(1,4), Rational(1,2).quo(2))

    assert_equal(0.5, 1.fdiv(2))
    assert_equal(5000000000.0, 10000000000.fdiv(2))
    assert_equal(0.5, 1.0.fdiv(2))
    assert_equal(0.25, Rational(1,2).fdiv(2))
  end

  def test_zero_div
    assert_raise(ZeroDivisionError) { Rational(1, 0) }
    assert_raise(ZeroDivisionError) { Rational(1, 1) / 0 }
  end

  def test_gcd
    assert_equal(0, Rational(0, 2**100))
  end

  def test_unify2
    f = defined?(Rational::Unify)
    Rational.const_set(:Unify, true) unless f

    assert_same(42, Rational(84, 2))
    assert_same(1, Rational(1, 2) + Rational(1, 2))

    Rational.instance_eval { remove_const(:Unify) } unless f
  end

  def test_coerce
    r = Rational(7, 3)
    assert_equal(Rational(42, 1), r.coerce(42).first)
    assert_raise(TypeError) { r.coerce(Object.new) }

    o = Object.new
    def o.coerce(x); [x.numerator, x.denominator]; end
    assert_equal(10, r + o)
    assert_equal(4, r - o)
    assert_equal(21, r * o)
    assert_equal(2, r / o)
    assert_equal(343, r ** o)
    assert_equal(1, r <=> o)

    b = 2**100
    def b.<=>(x); 0; end rescue nil
    assert_equal(1, r ** b)
    b = 2**100
    def b.**(x); -1; end rescue nil
    assert_equal(-1, Rational(1, b)**3)
  end

  def test_modulo_remainder
    assert_equal(Rational(1, 2), Rational(5, 2).modulo(1))
    assert_equal(Rational(1, 2), Rational(5, 2).modulo(2))
    assert_equal(Rational(5, 2), Rational(5, 2).modulo(3))
    assert_equal(Rational(5, 6), Rational(5, 2).modulo(Rational(5, 3)))
    assert_equal(Rational(1, 2), Rational(-5, 2).modulo(1))
    assert_equal(Rational(-1, 2), Rational(5, 2).modulo(-1))
    assert_equal(Rational(-1, 2), Rational(-5, 2).modulo(-1))

    assert_equal(Rational(1, 2), Rational(5, 2).remainder(1))
    assert_equal(Rational(1, 2), Rational(5, 2).remainder(2))
    assert_equal(Rational(5, 2), Rational(5, 2).remainder(3))
    assert_equal(Rational(5, 6), Rational(5, 2).remainder(Rational(5, 3)))
    assert_equal(Rational(-1, 2), Rational(-5, 2).remainder(1))
    assert_equal(Rational(1, 2), Rational(5, 2).remainder(-1))
    assert_equal(Rational(-1, 2), Rational(-5, 2).remainder(-1))
  end

  def test_abs
    assert_equal(Rational(1, 2), Rational(1, 2).abs)
    assert_equal(Rational(1, 2), Rational(-1, 2).abs)
  end

  def test_floor_ceil_truncate_round
    assert_equal( 2, Rational( 5, 2).floor)
    assert_equal(-3, Rational(-5, 2).floor)
    assert_equal( 3, Rational( 5, 2).ceil)
    assert_equal(-2, Rational(-5, 2).ceil)
    assert_equal( 2, Rational( 5, 2).truncate)
    assert_equal(-2, Rational(-5, 2).truncate)
    assert_equal( 3, Rational( 5, 2).round)
    assert_equal(-3, Rational(-5, 2).round)
    assert_equal( 1, Rational( 4, 3).round)
    assert_equal(-1, Rational(-4, 3).round)
    assert_equal( 2, Rational( 5, 3).round)
    assert_equal(-2, Rational(-5, 3).round)
  end

  def test_convert
    assert_equal(Rational(1, 2), Rational(Complex(1, 0), 2))
    assert_raise(RangeError) { Rational(Complex(1, 1), 1) }
    assert_equal(Rational(1, 2), Rational(1, Complex(2, 0)))
    assert_raise(RangeError) { Rational(1, Complex(2, 1)) }
    assert_equal(Rational(1, 2), Rational(0.25, 0.5))
    assert_equal(Rational(1, 2), Rational('1', '2'))
  end

  def test_add2
    assert_equal(Rational(2**100, 3), Rational(0, 1) + Rational(2**100, 3))
    assert_equal(Rational(2, 3**100), Rational(0, 1) + Rational(2, 3**100))
  end

  def test_div2
    assert_raise(ZeroDivisionError) { Rational(1, 1) / Rational(0, 1) }
  end

  def test_to_f2
    assert_equal(1, Rational(2**5000,3).to_f.infinite?)
    assert_equal(0, Rational(1, 2**5000).to_f)
  end

  def test_fixed_bug
    if defined?(Rational::Unify)
      assert_instance_of(Fixnum, Rational(1,2) ** 0) # mathn's bug
    end

    n = Float::MAX.to_i * 2
    assert_equal(1.0, Rational(n + 2, n + 1).to_f, '[ruby-dev:33852]')
  end

  def test_known_bug
  end

end
