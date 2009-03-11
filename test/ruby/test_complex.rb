require 'test/unit'

class ComplexSub < Complex; end

class Complex_Test < Test::Unit::TestCase

  def test_compsub
    c = ComplexSub.__send__(:new, 1)
    cc = ComplexSub.__send__(:convert, 1)
    if defined?(ComplexSub::Unify)
      assert_instance_of(Fixnum, c)
      assert_instance_of(Fixnum, cc)
    else
      assert_instance_of(ComplexSub, c)
      assert_instance_of(ComplexSub, cc)

      c2 = c + 1
      assert_instance_of(ComplexSub, c2)
      c2 = c - 1
      assert_instance_of(ComplexSub, c2)

      c3 = c - c2
      assert_instance_of(ComplexSub, c3)

      s = Marshal.dump(c)
      c5 = Marshal.load(s)
      assert_equal(c, c5)
      assert_instance_of(ComplexSub, c5)
    end

  end

  def test_eql_p
    c = Complex(0)
    c2 = Complex(0)
    c3 = Complex(1)

    assert_equal(true, c.eql?(c2))
    assert_equal(false, c.eql?(c3))

    if defined?(Complex::Unify)
      assert_equal(true, c.eql?(0))
    else
      assert_equal(false, c.eql?(0))
    end
  end

  def test_hash
    assert_instance_of(Fixnum, Complex(1,2).hash)

    h = {}
    h[Complex(0)] = 0
    h[Complex(0,1)] = 1
    h[Complex(1,0)] = 2
    h[Complex(1,1)] = 3

    assert_equal(4, h.size)
    assert_equal(2, h[Complex(1,0)])

    h[Complex(0,0)] = 9
    assert_equal(4, h.size)
  end

  def test_freeze
    c = Complex(1)
    c.freeze
    unless defined?(Complex::Unify)
      assert_equal(true, c.frozen?)
    end
    assert_instance_of(String, c.to_s)
  end

  def test_new_bang # no unify
    assert_instance_of(Complex, Complex.__send__(:new!, 2,0))
    assert_equal([2,0], Complex.__send__(:new!, 2,0).
		 instance_eval{[real, image]})
    assert_equal([2,4], Complex.__send__(:new!, 2,4).
		 instance_eval{[real, image]})
    assert_equal([-2,4], Complex.__send__(:new!, -2,4).
		 instance_eval{[real, image]})
    assert_equal([2,-4], Complex.__send__(:new!, 2,-4).
		 instance_eval{[real, image]})
    assert_equal([-2,-4], Complex.__send__(:new!, -2,-4).
		 instance_eval{[real, image]})

    assert_equal([2,0], Complex.__send__(:new!, Complex(2)).
		 instance_eval{[real, image]})
    assert_equal([2,3], Complex.__send__(:new!, Complex(2), Complex(3)).
		 instance_eval{[real, image]})
    assert_equal([2,3], Complex.__send__(:new!, 2, Complex(3)).
		 instance_eval{[real, image]})

    assert_equal([1.1,0], Complex.__send__(:new!, 1.1).
		 instance_eval{[real, image]})
    assert_equal([-1.1,0], Complex.__send__(:new!, -1.1).
		 instance_eval{[real, image]})
    assert_equal([1,0], Complex.__send__(:new!, '1').
		 instance_eval{[real, image]})
    assert_equal([0,0], Complex.__send__(:new!, nil).
		 instance_eval{[real, image]})
  end

  def test_new
    if defined?(Complex::Unify)
      assert_instance_of(Fixnum, Complex.__send__(:new, 2,0))
    else
      assert_instance_of(Complex, Complex.__send__(:new, 2,0))
      assert_equal([2,0], Complex.__send__(:new, 2,0). instance_eval{[real, image]})
    end
    assert_equal([2,4], Complex.__send__(:new, 2,4).instance_eval{[real, image]})
    assert_equal([-2,4], Complex.__send__(:new, -2,4).instance_eval{[real, image]})
    assert_equal([2,-4], Complex.__send__(:new, 2,-4).instance_eval{[real, image]})
    assert_equal([-2,-4], Complex.__send__(:new, -2,-4).instance_eval{[real, image]})

    assert_raise(ArgumentError){Complex.__send__(:new, Complex(1,2),2)}
    assert_raise(ArgumentError){Complex.__send__(:new, 2,Complex(1,2))}
    assert_raise(ArgumentError){Complex.__send__(:new, Complex(1,2),Complex(1,2))}

    assert_raise(ArgumentError){Complex.__send__(:new, '1')}
    assert_raise(ArgumentError){Complex.__send__(:new, nil)}
=begin
    assert_raise(ArgumentError){Complex.__send__(:new, Complex(1))}
=end
  end

  def test_conv
    c = Complex(0,0)
    assert_equal(Complex.__send__(:new, 0,0), c)

    c = Complex(2**32, 2**32)
    assert_equal(Complex.__send__(:new, 2**32,2**32), c)
    assert_equal([2**32,2**32], [c.real,c.image])

    c = Complex(-2**32, 2**32)
    assert_equal(Complex.__send__(:new, -2**32,2**32), c)
    assert_equal([-2**32,2**32], [c.real,c.image])

    c = Complex(2**32, -2**32)
    assert_equal(Complex.__send__(:new, 2**32,-2**32), c)
    assert_equal([2**32,-2**32], [c.real,c.image])

    c = Complex(-2**32, -2**32)
    assert_equal(Complex.__send__(:new, -2**32,-2**32), c)
    assert_equal([-2**32,-2**32], [c.real,c.image])

    c = Complex(Complex(1),0)
    assert_equal(Complex.__send__(:new, 1,0), c)

    c = Complex(0,Complex(1))
    assert_equal(Complex.__send__(:new, 0,1), c)

    c = 5.re
    assert_equal(Complex.__send__(:new, 5,0), c)

    c = Complex(1,2).re
    assert_equal(Complex.__send__(:new, 1,2), c)

    c = 5.im
    assert_equal(Complex.__send__(:new, 0,5), c)

    c = Complex(2,0).im
    assert_equal(Complex.__send__(:new, 0,2), c)
    assert_raise(ArgumentError){Complex(1,2).im}

    c = Complex::I
    assert_equal(Complex.__send__(:new, 0,1), c)

    assert_equal(Complex.__send__(:new, 1),Complex(1))
    assert_equal(Complex.__send__(:new, 1),Complex('1'))
    assert_raise(ArgumentError){Complex(nil)}
  end

  def test_attr
    c = Complex(4)

    assert_equal(4, c.real)
    assert_equal(0, c.image)

    c = Complex(4,5)

    assert_equal(4, c.real)
    assert_equal(5, c.image)

    c = Complex(-0.0,-0.0)

    assert_equal('-0.0', c.real.to_s)
    assert_equal('-0.0', c.image.to_s)

    c = Complex.__send__(:new, 4)

    assert_equal(4, c.real)
    assert_equal(0, c.image)
    assert_equal(c.imag, c.image)

    c = Complex.__send__(:new, 4,5)

    assert_equal(4, c.real)
    assert_equal(5, c.image)
    assert_equal(c.imag, c.image)

    c = Complex.__send__(:new, -0.0,-0.0)

    assert_equal('-0.0', c.real.to_s)
    assert_equal('-0.0', c.image.to_s)
    assert_equal(c.imag.to_s, c.image.to_s)

    c = Complex.__send__(:new!, 4)

    assert_equal(4, c.real)
    assert_equal(c.imag, c.image)
    assert_equal(0, c.image)

    c = Complex.__send__(:new!, 4,5)

    assert_equal(4, c.real)
    assert_equal(5, c.image)
    assert_equal(c.imag, c.image)

    c = Complex.__send__(:new!, -0.0,-0.0)

    assert_equal('-0.0', c.real.to_s)
    assert_equal('-0.0', c.image.to_s)
    assert_equal(c.imag.to_s, c.image.to_s)
  end

  def test_attr2
    c = Complex(1)

    if defined?(Complex::Unify)
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
      assert_equal(false, c.scalar?)
=begin
      assert_equal(true, c.finite?)
      assert_equal(false, c.infinite?)
      assert_equal(false, c.nan?)
      assert_equal(false, c.integer?)
      assert_equal(false, c.float?)
      assert_equal(false, c.rational?)
      assert_equal(false, c.real?)
      assert_equal(true, c.complex?)
      assert_equal(true, c.exact?)
      assert_equal(false, c.inexact?)
=end
    end

=begin
    assert_equal(0, Complex(0).sign)
    assert_equal(1, Complex(2).sign)
    assert_equal(-1, Complex(-2).sign)
=end

    assert_equal(true, Complex(0).zero?)
    assert_equal(true, Complex(0,0).zero?)
    assert_equal(false, Complex(1,0).zero?)
    assert_equal(false, Complex(0,1).zero?)
    assert_equal(false, Complex(1,1).zero?)

    assert_equal(nil, Complex(0).nonzero?)
    assert_equal(nil, Complex(0,0).nonzero?)
    assert_equal(Complex(1,0), Complex(1,0).nonzero?)
    assert_equal(Complex(0,1), Complex(0,1).nonzero?)
    assert_equal(Complex(1,1), Complex(1,1).nonzero?)
  end

  def test_uplus
    assert_equal(Complex(1), +Complex(1))
    assert_equal(Complex(-1), +Complex(-1))
    assert_equal(Complex(1,1), +Complex(1,1))
    assert_equal(Complex(-1,1), +Complex(-1,1))
    assert_equal(Complex(1,-1), +Complex(1,-1))
    assert_equal(Complex(-1,-1), +Complex(-1,-1))
  end

  def test_negate
    assert_equal(Complex(-1), -Complex(1))
    assert_equal(Complex(1), -Complex(-1))
    assert_equal(Complex(-1,-1), -Complex(1,1))
    assert_equal(Complex(1,-1), -Complex(-1,1))
    assert_equal(Complex(-1,1), -Complex(1,-1))
    assert_equal(Complex(1,1), -Complex(-1,-1))

=begin
    assert_equal(0, Complex(0).negate)
    assert_equal(-2, Complex(2).negate)
    assert_equal(2, Complex(-2).negate)
=end
  end

  def test_add
    c = Complex(1,2)
    c2 = Complex(2,3)

    assert_equal(Complex(3,5), c + c2)

    assert_equal(Complex(3,2), c + 2)
    assert_equal(Complex(3.0,2), c + 2.0)

    if defined?(Rational)
      assert_equal(Complex(Rational(3,1),Rational(2)), c + Rational(2))
      assert_equal(Complex(Rational(5,3),Rational(2)), c + Rational(2,3))
    end
  end

  def test_sub
    c = Complex(1,2)
    c2 = Complex(2,3)

    assert_equal(Complex(-1,-1), c - c2)

    assert_equal(Complex(-1,2), c - 2)
    assert_equal(Complex(-1.0,2), c - 2.0)

    if defined?(Rational)
      assert_equal(Complex(Rational(-1,1),Rational(2)), c - Rational(2))
      assert_equal(Complex(Rational(1,3),Rational(2)), c - Rational(2,3))
    end
  end

  def test_mul
    c = Complex(1,2)
    c2 = Complex(2,3)

    assert_equal(Complex(-4,7), c * c2)

    assert_equal(Complex(2,4), c * 2)
    assert_equal(Complex(2.0,4.0), c * 2.0)

    if defined?(Rational)
      assert_equal(Complex(Rational(2,1),Rational(4)), c * Rational(2))
      assert_equal(Complex(Rational(2,3),Rational(4,3)), c * Rational(2,3))
    end

  end

  def test_div
    c = Complex(1,2)
    c2 = Complex(2,3)

    if defined?(Complex::Unify)
      assert_equal(Complex(Rational(8,13),Rational(1,13)), c / c2)
    else
      assert_equal(Complex(0,0), c / c2)
    end

    c = Complex(1.0,2.0)
    c2 = Complex(2.0,3.0)

    r = c / c2
    assert_in_delta(0.615, r.real, 0.001)
    assert_in_delta(0.076, r.image, 0.001)

    c = Complex(1,2)
    c2 = Complex(2,3)

    if defined?(Complex::Unify)
      assert_equal(Complex(Rational(1,2),1), c / 2)
    else
      assert_equal(Complex(0,1), c / 2)
    end
    assert_equal(Complex(0.5,1.0), c / 2.0)

    if defined?(Rational)
      assert_equal(Complex(Rational(1,2),Rational(1)), c / Rational(2))
      assert_equal(Complex(Rational(3,2),Rational(3)), c / Rational(2,3))
    end
  end

  def test_quo
    c = Complex(1,2)
    c2 = Complex(2,3)

    if defined?(Rational)
      assert_equal(Complex(Rational(8,13),Rational(1,13)), c.quo(c2))
    else
      r = c.quo(c2)
      assert_in_delta(0.615, r.real, 0.001)
      assert_in_delta(0.076, r.image, 0.001)
    end

    c = Complex(1.0,2.0)
    c2 = Complex(2.0,3.0)

    r = c.quo(c2)
    assert_in_delta(0.615, r.real, 0.001)
    assert_in_delta(0.076, r.image, 0.001)

    c = Complex(1,2)
    c2 = Complex(2,3)

    if defined?(Rational)
      assert_equal(Complex(Rational(1,2),1), c.quo(2))
    else
      assert_equal(Complex(0.5,1.0), c.quo(2))
    end
    assert_equal(Complex(0.5,1.0), c.quo(2.0))

    if defined?(Rational)
      assert_equal(Complex(Rational(1,2),Rational(1)), c / Rational(2))
      assert_equal(Complex(Rational(3,2),Rational(3)), c / Rational(2,3))
    end
  end

  def test_fdiv
    c = Complex(1,2)
    c2 = Complex(2,3)

    r = c.fdiv(c2)
    assert_in_delta(0.615, r.real, 0.001)
    assert_in_delta(0.076, r.image, 0.001)

    c = Complex(1.0,2.0)
    c2 = Complex(2.0,3.0)

    r = c.fdiv(c2)
    assert_in_delta(0.615, r.real, 0.001)
    assert_in_delta(0.076, r.image, 0.001)

    c = Complex(1,2)
    c2 = Complex(2,3)

    assert_equal(Complex(0.5,1.0), c.fdiv(2))
    assert_equal(Complex(0.5,1.0), c.fdiv(2.0))
  end

  def test_expt
    c = Complex(1,2)
    c2 = Complex(2,3)

    r = c ** c2
    assert_in_delta(-0.015, r.real, 0.001)
    assert_in_delta(-0.179, r.image, 0.001)

    assert_equal(Complex(-3,4), c ** 2)
    if defined?(Rational) && !Rational.instance_variable_get('@RCS_ID')
      assert_equal(Complex(Rational(-3,25),Rational(-4,25)), c ** -2)
    else
      r = c ** -2
      assert_in_delta(-0.12, r.real, 0.001)
      assert_in_delta(-0.16, r.image, 0.001)
    end
    r = c ** 2.0
    assert_in_delta(-3.0, r.real, 0.001)
    assert_in_delta(4.0, r.image, 0.001)

    r = c ** -2.0
    assert_in_delta(-0.12, r.real, 0.001)
    assert_in_delta(-0.16, r.image, 0.001)

    if defined?(Rational) && !Rational.instance_variable_get('@RCS_ID')
      assert_equal(Complex(-3,4), c ** Rational(2))
#=begin
      assert_equal(Complex(Rational(-3,25),Rational(-4,25)),
		   c ** Rational(-2)) # why failed?
#=end

      r = c ** Rational(2,3)
      assert_in_delta(1.264, r.real, 0.001)
      assert_in_delta(1.150, r.image, 0.001)

      r = c ** Rational(-2,3)
      assert_in_delta(0.432, r.real, 0.001)
      assert_in_delta(-0.393, r.image, 0.001)
    end
  end

  def test_cmp
    assert_raise(NoMethodError){1 <=> Complex(1,1)}
    assert_raise(NoMethodError){Complex(1,1) <=> 1}
    assert_raise(NoMethodError){Complex(1,1) <=> Complex(1,1)}
  end

  def test_equal
    assert(Complex(1,0) == Complex(1))
    assert(Complex(1,0) == Complex.__send__(:new, 1))
    assert(Complex(1,0) == Complex.__send__(:new, 1,0))
    assert(Complex(1,0) == Complex.__send__(:new!, 1))
    assert(Complex(1,0) == Complex.__send__(:new!, 1,0))

    assert(Complex(-1,0) == Complex(-1))
    assert(Complex(-1,0) == Complex.__send__(:new, -1))
    assert(Complex(-1,0) == Complex.__send__(:new, -1,0))
    assert(Complex(-1,0) == Complex.__send__(:new!, -1))
    assert(Complex(-1,0) == Complex.__send__(:new!, -1,0))

    assert_equal(false, Complex(2,1) == Complex(1))
    assert_equal(true, Complex(2,1) != Complex(1))
    assert_equal(false, Complex(1) == nil)
    assert_equal(false, Complex(1) == '')
  end

  def test_math
    c = Complex(1,2)

    assert_in_delta(2.236, c.abs, 0.001)
    assert_equal(5, c.abs2)

    assert_equal(c.abs, Math.sqrt(c * c.conj))
    assert_equal(c.abs, Math.sqrt(c.real**2 + c.image**2))
    assert_equal(c.abs2, c * c.conj)
    assert_equal(c.abs2, c.real**2 + c.image**2)

    assert_in_delta(1.107, c.arg, 0.001)
    assert_in_delta(1.107, c.angle, 0.001)

    r = c.polar
    assert_in_delta(2.236, r[0], 0.001)
    assert_in_delta(1.107, r[1], 0.001)
    assert_equal(Complex(1,-2), c.conjugate)
    assert_equal(Complex(1,-2), c.conj)
#    assert_equal(Complex(1,-2), ~c)
#    assert_equal(5, c * ~c)

    assert_equal(Complex(1,2), c.numerator)
    assert_equal(1, c.denominator)
  end

  def test_to_s
    c = Complex(1,2)

    assert_instance_of(String, c.to_s)
    assert_equal('1+2i', c.to_s)

    assert_equal('2i', Complex(0,2).to_s)
    assert_equal('-2i', Complex(0,-2).to_s)
    assert_equal('1+2i', Complex(1,2).to_s)
    assert_equal('-1+2i', Complex(-1,2).to_s)
    assert_equal('-1-2i', Complex(-1,-2).to_s)
    assert_equal('1-2i', Complex(1,-2).to_s)
    assert_equal('-1-2i', Complex(-1,-2).to_s)

    assert_equal('2.0i', Complex(0,2.0).to_s)
    assert_equal('-2.0i', Complex(0,-2.0).to_s)
    assert_equal('1.0+2.0i', Complex(1.0,2.0).to_s)
    assert_equal('-1.0+2.0i', Complex(-1.0,2.0).to_s)
    assert_equal('-1.0-2.0i', Complex(-1.0,-2.0).to_s)
    assert_equal('1.0-2.0i', Complex(1.0,-2.0).to_s)
    assert_equal('-1.0-2.0i', Complex(-1.0,-2.0).to_s)

    if defined?(Rational)
      assert_equal('2i', Complex(0,Rational(2)).to_s)
      assert_equal('-2i', Complex(0,Rational(-2)).to_s)
      assert_equal('1+2i', Complex(1,Rational(2)).to_s)
      assert_equal('-1+2i', Complex(-1,Rational(2)).to_s)
      assert_equal('-1-2i', Complex(-1,Rational(-2)).to_s)
      assert_equal('1-2i', Complex(1,Rational(-2)).to_s)
      assert_equal('-1-2i', Complex(-1,Rational(-2)).to_s)

      assert_equal('(2/3)i', Complex(0,Rational(2,3)).to_s)
      assert_equal('(-2/3)i', Complex(0,Rational(-2,3)).to_s)
      assert_equal('1+(2/3)i', Complex(1,Rational(2,3)).to_s)
      assert_equal('-1+(2/3)i', Complex(-1,Rational(2,3)).to_s)
      assert_equal('-1-(2/3)i', Complex(-1,Rational(-2,3)).to_s)
      assert_equal('1-(2/3)i', Complex(1,Rational(-2,3)).to_s)
      assert_equal('-1-(2/3)i', Complex(-1,Rational(-2,3)).to_s)
    end
  end

  def test_inspect
    c = Complex(1,2)

    assert_instance_of(String, c.inspect)
    assert_equal('Complex(1, 2)', c.inspect)
  end

  def test_marshal
    c = Complex(1,2)

    s = Marshal.dump(c)
    c2 = Marshal.load(s)
    assert_equal(c, c2)
    assert_instance_of(Complex, c2)

    if defined?(Rational)
      c = Complex(Rational(1,2),Rational(2,3))

      s = Marshal.dump(c)
      c2 = Marshal.load(s)
      assert_equal(c, c2)
      assert_instance_of(Complex, c2)
    end
  end

  def test_parse
    assert_equal(Complex(0), ''.to_c)
    assert_equal(Complex(0), ' '.to_c)
    assert_equal(Complex(5), '5'.to_c)
    assert_equal(Complex(-5), '-5'.to_c)
    assert_equal(Complex(5,3), '5+3i'.to_c)
    assert_equal(Complex(-5,3), '-5+3i'.to_c)
    assert_equal(Complex(5,-3), '5-3i'.to_c)
    assert_equal(Complex(-5,-3), '-5-3i'.to_c)
    assert_equal(Complex(0,3), '3i'.to_c)
    assert_equal(Complex(0,-3), '-3i'.to_c)

    assert_equal(Complex(5,3), '5+3I'.to_c)
    assert_equal(Complex(5,3), '5+3j'.to_c)
    assert_equal(Complex(5,3), '5+3J'.to_c)
    assert_equal(Complex(0,3), '3I'.to_c)
    assert_equal(Complex(0,3), '3j'.to_c)
    assert_equal(Complex(0,3), '3J'.to_c)

    assert_equal(Complex(5.0), '5.0'.to_c)
    assert_equal(Complex(-5.0), '-5.0'.to_c)
    assert_equal(Complex(5.0,3.0), '5.0+3.0i'.to_c)
    assert_equal(Complex(-5.0,3.0), '-5.0+3.0i'.to_c)
    assert_equal(Complex(5.0,-3.0), '5.0-3.0i'.to_c)
    assert_equal(Complex(-5.0,-3.0), '-5.0-3.0i'.to_c)
    assert_equal(Complex(0.0,3.0), '3.0i'.to_c)
    assert_equal(Complex(0.0,-3.0), '-3.0i'.to_c)

    assert_equal(Complex(5.0), '5e0'.to_c)
    assert_equal(Complex(-5.0), '-5e0'.to_c)
    assert_equal(Complex(5.0,3.0), '5e0+3e0i'.to_c)
    assert_equal(Complex(-5.0,3.0), '-5e0+3e0i'.to_c)
    assert_equal(Complex(5.0,-3.0), '5e0-3e0i'.to_c)
    assert_equal(Complex(-5.0,-3.0), '-5e0-3e0i'.to_c)
    assert_equal(Complex(0.0,3.0), '3e0i'.to_c)
    assert_equal(Complex(0.0,-3.0), '-3e0i'.to_c)

    assert_equal(Complex(5), Complex('5'))
    assert_equal(Complex(-5), Complex('-5'))
    assert_equal(Complex(5,3), Complex('5+3i'))
    assert_equal(Complex(-5,3), Complex('-5+3i'))
    assert_equal(Complex(5,-3), Complex('5-3i'))
    assert_equal(Complex(-5,-3), Complex('-5-3i'))
    assert_equal(Complex(0,3), Complex('3i'))
    assert_equal(Complex(0,-3), Complex('-3i'))

    assert_equal(Complex(5,3), Complex('5+3I'))
    assert_equal(Complex(5,3), Complex('5+3j'))
    assert_equal(Complex(5,3), Complex('5+3J'))
    assert_equal(Complex(0,3), Complex('3I'))
    assert_equal(Complex(0,3), Complex('3j'))
    assert_equal(Complex(0,3), Complex('3J'))

    assert_equal(Complex(5.0), Complex('5.0'))
    assert_equal(Complex(-5.0), Complex('-5.0'))
    assert_equal(Complex(5.0,3.0), Complex('5.0+3.0i'))
    assert_equal(Complex(-5.0,3.0), Complex('-5.0+3.0i'))
    assert_equal(Complex(5.0,-3.0), Complex('5.0-3.0i'))
    assert_equal(Complex(-5.0,-3.0), Complex('-5.0-3.0i'))
    assert_equal(Complex(0.0,3.0), Complex('3.0i'))
    assert_equal(Complex(0.0,-3.0), Complex('-3.0i'))

    assert_equal(Complex(5.0), Complex('5e0'))
    assert_equal(Complex(-5.0), Complex('-5e0'))
    assert_equal(Complex(5.0,3.0), Complex('5e0+3e0i'))
    assert_equal(Complex(-5.0,3.0), Complex('-5e0+3e0i'))
    assert_equal(Complex(5.0,-3.0), Complex('5e0-3e0i'))
    assert_equal(Complex(-5.0,-3.0), Complex('-5e0-3e0i'))
    assert_equal(Complex(0.0,3.0), Complex('3e0i'))
    assert_equal(Complex(0.0,-3.0), Complex('-3e0i'))

    assert_equal(Complex(0), '_'.to_c)
    assert_equal(Complex(0), '_5'.to_c)
    assert_equal(Complex(5), '5_'.to_c)
    assert_equal(Complex(5), '5x'.to_c)
    assert_equal(Complex(5), '5+_3i'.to_c)
    assert_equal(Complex(5), '5+3_i'.to_c)
    assert_equal(Complex(5,3), '5+3i_'.to_c)
    assert_equal(Complex(5,3), '5+3ix'.to_c)
    assert_raise(ArgumentError){ Complex('')}
    assert_raise(ArgumentError){ Complex('_')}
    assert_raise(ArgumentError){ Complex('_5')}
    assert_raise(ArgumentError){ Complex('5_')}
    assert_raise(ArgumentError){ Complex('5x')}
    assert_raise(ArgumentError){ Complex('5+_3i')}
    assert_raise(ArgumentError){ Complex('5+3_i')}
    assert_raise(ArgumentError){ Complex('5+3i_')}
    assert_raise(ArgumentError){ Complex('5+3ix')}

    if defined?(Rational) && defined?(''.to_r)
      assert_equal(Complex(Rational(1,5)), '1/5'.to_c)
      assert_equal(Complex(Rational(-1,5)), '-1/5'.to_c)
      assert_equal(Complex(Rational(1,5),3), '1/5+3i'.to_c)
      assert_equal(Complex(Rational(1,5),-3), '1/5-3i'.to_c)
      assert_equal(Complex(Rational(-1,5),3), '-1/5+3i'.to_c)
      assert_equal(Complex(Rational(-1,5),-3), '-1/5-3i'.to_c)
      assert_equal(Complex(Rational(1,5),Rational(3,2)), '1/5+3/2i'.to_c)
      assert_equal(Complex(Rational(1,5),Rational(-3,2)), '1/5-3/2i'.to_c)
      assert_equal(Complex(Rational(-1,5),Rational(3,2)), '-1/5+3/2i'.to_c)
      assert_equal(Complex(Rational(-1,5),Rational(-3,2)), '-1/5-3/2i'.to_c)
      assert_equal(Complex(Rational(1,5),Rational(3,2)), '1/5+(3/2)i'.to_c)
      assert_equal(Complex(Rational(1,5),Rational(-3,2)), '1/5-(3/2)i'.to_c)
      assert_equal(Complex(Rational(-1,5),Rational(3,2)), '-1/5+(3/2)i'.to_c)
      assert_equal(Complex(Rational(-1,5),Rational(-3,2)), '-1/5-(3/2)i'.to_c)
    end

    assert_equal(Complex(5, 3), Complex('5', '3'))
  end

  def test_respond
    c = Complex(1,1)
    assert_equal(false, c.respond_to?(:<))
    assert_equal(false, c.respond_to?(:<=))
    assert_equal(false, c.respond_to?(:<=>))
    assert_equal(false, c.respond_to?(:>))
    assert_equal(false, c.respond_to?(:>=))
    assert_equal(false, c.respond_to?(:between?))
#    assert_equal(false, c.respond_to?(:div)) # ?
    assert_equal(false, c.respond_to?(:divmod))
    assert_equal(false, c.respond_to?(:floor))
    assert_equal(false, c.respond_to?(:ceil))
    assert_equal(false, c.respond_to?(:modulo))
    assert_equal(false, c.respond_to?(:round))
    assert_equal(false, c.respond_to?(:step))
    assert_equal(false, c.respond_to?(:tunrcate))

    assert_equal(false, c.respond_to?(:positive?))
    assert_equal(false, c.respond_to?(:negative?))
#    assert_equal(false, c.respond_to?(:sign))

    assert_equal(false, c.respond_to?(:quotient))
    assert_equal(false, c.respond_to?(:quot))
    assert_equal(false, c.respond_to?(:quotrem))

    assert_equal(false, c.respond_to?(:gcd))
    assert_equal(false, c.respond_to?(:lcm))
    assert_equal(false, c.respond_to?(:gcdlcm))
  end

  def test_to_i
    assert_equal(3, Complex(3).to_i)
    assert_equal(3, Integer(Complex(3)))
    assert_raise(RangeError){Complex(3,2).to_i}
    assert_raise(RangeError){Integer(Complex(3,2))}
  end

  def test_to_f
    assert_equal(3.0, Complex(3).to_f)
    assert_equal(3.0, Float(Complex(3)))
    assert_raise(RangeError){Complex(3,2).to_f}
    assert_raise(RangeError){Float(Complex(3,2))}
  end

  def test_to_r
    if defined?(Rational) && !Rational.instance_variable_get('@RCS_ID')
      assert_equal(Rational(3), Complex(3).to_r)
      assert_equal(Rational(3), Rational(Complex(3)))
      assert_raise(RangeError){Complex(3,2).to_r}
      assert_raise(RangeError){Rational(Complex(3,2))}
    end
  end

  def test_to_c
    c = nil.to_c
    assert_equal([0,0] , [c.real, c.image])

    c = 0.to_c
    assert_equal([0,0] , [c.real, c.image])

    c = 1.to_c
    assert_equal([1,0] , [c.real, c.image])

    c = 1.1.to_c
    assert_equal([1.1, 0], [c.real, c.image])

    if defined?(Rational)
      c = Rational(1,2).to_c
      assert_equal([Rational(1,2), 0], [c.real, c.image])
    end

    c = Complex(1,2).to_c
    assert_equal([1, 2], [c.real, c.image])
  end

  def test_prec
    assert_equal(nil, Complex < Precision)
  end

  def test_supp
    assert_equal(true, 1.scalar?)
    assert_equal(true, 1.1.scalar?)

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

    assert_equal(1, 1.numerator)
    assert_equal(9, 9.numerator)
    assert_equal(1, 1.denominator)
    assert_equal(1, 9.denominator)

    if defined?(Rational) && !Rational.instance_variable_get('@RCS_ID')
      assert_equal(1.0, 1.0.numerator)
      assert_equal(9.0, 9.0.numerator)
      assert_equal(1.0, 1.0.denominator)
      assert_equal(1.0, 9.0.denominator)
    end

=begin
    if defined?(Rational) && !Rational.instance_variable_get('@RCS_ID')
      assert_equal(Rational(1,9), 9.reciprocal)
      assert_equal(Rational(1,9), 9.0.reciprocal)
      assert_equal(Rational(1,9), 9.inverse)
      assert_equal(Rational(1,9), 9.0.inverse)
    end
=end

    if defined?(Rational)
      assert_equal(Rational(1,2), 1.quo(2))
      assert_equal(Rational(5000000000), 10000000000.quo(2))
      assert_equal(0.5, 1.0.quo(2))
      assert_equal(Rational(1,4), Rational(1,2).quo(2))
      assert_equal(Complex(Rational(1,2),Rational(1)), Complex(1,2).quo(2))
    else
      assert_equal(0.5, 1.quo(2))
      assert_equal(5000000000.0, 10000000000.quo(2))
      assert_equal(0.5, 1.0.quo(2))
      assert_equal(Complex(0.5,1.0), Complex(1,2).quo(2))
    end

    if defined?(Rational) && !Rational.instance_variable_get('@RCS_ID')
      assert_equal(Rational(1,2), 1.quo(2))
      assert_equal(Rational(5000000000), 10000000000.quo(2))
      assert_equal(Rational(1,2), 1.0.quo(2))
      assert_equal(Rational(1,4), Rational(1,2).quo(2))
      assert_equal(Complex(Rational(1,2),Rational(1)), Complex(1,2).quo(2))
    end

    assert_equal(0.5, 1.fdiv(2))
    assert_equal(5000000000.0, 10000000000.fdiv(2))
    assert_equal(0.5, 1.0.fdiv(2))
    if defined?(Rational)
      assert_equal(0.25, Rational(1,2).fdiv(2))
    end
    assert_equal(Complex(0.5,1.0), Complex(1,2).quo(2))

    unless $".grep(/(\A|\/)complex/).empty?
      assert_equal(Complex(0,2), Math.sqrt(-4.0))
#      assert_equal(true, Math.sqrt(-4.0).inexact?)
      assert_equal(Complex(0,2), Math.sqrt(-4))
#      assert_equal(true, Math.sqrt(-4).exact?)
      if defined?(Rational)
	assert_equal(Complex(0,2), Math.sqrt(Rational(-4)))
#	assert_equal(true, Math.sqrt(Rational(-4)).exact?)
      end

      assert_equal(Complex(0,3), Math.sqrt(-9.0))
#      assert_equal(true, Math.sqrt(-9.0).inexact?)
      assert_equal(Complex(0,3), Math.sqrt(-9))
#      assert_equal(true, Math.sqrt(-9).exact?)
      if defined?(Rational)
	assert_equal(Complex(0,3), Math.sqrt(Rational(-9)))
#	assert_equal(true, Math.sqrt(Rational(-9)).exact?)
      end

      c = Math.sqrt(Complex(1, 2))
      assert_in_delta(1.272, c.real, 0.001)
      assert_in_delta(0.786, c.image, 0.001)

      c = Math.sqrt(-9)
      assert_in_delta(0.0, c.real, 0.001)
      assert_in_delta(3.0, c.image, 0.001)

      c = Math.exp(Complex(1, 2))
      assert_in_delta(-1.131, c.real, 0.001)
      assert_in_delta(2.471, c.image, 0.001)

      c = Math.sin(Complex(1, 2))
      assert_in_delta(3.165, c.real, 0.001)
      assert_in_delta(1.959, c.image, 0.001)

      c = Math.cos(Complex(1, 2))
      assert_in_delta(2.032, c.real, 0.001)
      assert_in_delta(-3.051, c.image, 0.001)

      c = Math.tan(Complex(1, 2))
      assert_in_delta(0.033, c.real, 0.001)
      assert_in_delta(1.014, c.image, 0.001)

      c = Math.sinh(Complex(1, 2))
      assert_in_delta(-0.489, c.real, 0.001)
      assert_in_delta(1.403, c.image, 0.001)

      c = Math.cosh(Complex(1, 2))
      assert_in_delta(-0.642, c.real, 0.001)
      assert_in_delta(1.068, c.image, 0.001)

      c = Math.tanh(Complex(1, 2))
      assert_in_delta(1.166, c.real, 0.001)
      assert_in_delta(-0.243, c.image, 0.001)

      c = Math.log(Complex(1, 2))
      assert_in_delta(0.804, c.real, 0.001)
      assert_in_delta(1.107, c.image, 0.001)

      c = Math.log(Complex(1, 2), Math::E)
      assert_in_delta(0.804, c.real, 0.001)
      assert_in_delta(1.107, c.image, 0.001)

      c = Math.log(-1)
      assert_in_delta(0.0, c.real, 0.001)
      assert_in_delta(Math::PI, c.image, 0.001)

      c = Math.log(8, 2)
      assert_in_delta(3.0, c.real, 0.001)
      assert_in_delta(0.0, c.image, 0.001)

      c = Math.log(-8, -2)
      assert_in_delta(1.092, c.real, 0.001)
      assert_in_delta(-0.420, c.image, 0.001)

      c = Math.log10(Complex(1, 2))
      assert_in_delta(0.349, c.real, 0.001)
      assert_in_delta(0.480, c.image, 0.001)

      c = Math.asin(Complex(1, 2))
      assert_in_delta(0.427, c.real, 0.001)
      assert_in_delta(1.528, c.image, 0.001)

      c = Math.acos(Complex(1, 2))
      assert_in_delta(1.143, c.real, 0.001)
      assert_in_delta(-1.528, c.image, 0.001)

      c = Math.atan(Complex(1, 2))
      assert_in_delta(1.338, c.real, 0.001)
      assert_in_delta(0.402, c.image, 0.001)

      c = Math.atan2(Complex(1, 2), 1)
      assert_in_delta(1.338, c.real, 0.001)
      assert_in_delta(0.402, c.image, 0.001)

      c = Math.asinh(Complex(1, 2))
      assert_in_delta(1.469, c.real, 0.001)
      assert_in_delta(1.063, c.image, 0.001)

      c = Math.acosh(Complex(1, 2))
      assert_in_delta(1.528, c.real, 0.001)
      assert_in_delta(1.143, c.image, 0.001)

      c = Math.atanh(Complex(1, 2))
      assert_in_delta(0.173, c.real, 0.001)
      assert_in_delta(1.178, c.image, 0.001)
    end

  end

  def test_canonicalize
    f = defined?(Complex::Unify)
    Complex.const_set(:Unify, true) unless f

    assert_same(1, Complex.instance_eval { new(1, 0) })
    assert_not_same(1.0, Complex.instance_eval { new(1.0, 0) })
    assert_equal(Complex(1.0, 0), Complex.instance_eval { new(1.0, 0) })

    Complex.instance_eval { remove_const(:Unify) } unless f
  end

  def test_polar
    c = Complex.polar(2, 2)
    assert_in_delta(2*Math.cos(2), c.real , 0.001)
    assert_in_delta(2*Math.sin(2), c.image, 0.001)

    c = Complex.polar(1, Complex(0, 1))
    assert_in_delta(1/Math::E, c.real , 0.001)
    assert_in_delta(        0, c.image, 0.001)
  end

  def test_generic?
    assert_equal(true, Complex.generic?(1))
    assert_equal(true, Complex.generic?(2**100))
    assert_equal(true, Complex.generic?(Rational(1, 2)))
    assert_equal(true, Complex.generic?(1.0))
    assert_equal(false, Complex.generic?(Complex(1, 1)))
  end

  def test_new_bang2
    o = Object.new
    def o.to_i; 1; end
    assert_equal(Complex(1, 1), Complex.instance_eval { new!(o, o) })
  end

  def test_denominator
    f = defined?(Complex::Unify)
    unify_val = f && Complex::Unify
    Complex.instance_eval { remove_const(:Unify) } if f

    dummy_rational = Class.new(Rational)
    o1 = dummy_rational.instance_eval { new(1, 1) }
    o2 = dummy_rational.instance_eval { new(1, 1) }
    d1 = d2 = nil
    class << o1; self; end.instance_eval { define_method(:denominator) { d1 } rescue nil }
    class << o2; self; end.instance_eval { define_method(:denominator) { d2 } rescue nil }
    # o1.denominator returns d1 and o1.denominator returns d2

    c = Complex(o1, o2)

    d1 = d2 = 0
    assert_equal(0, c.denominator)

    d1 = d2 = -1
    assert_equal(1, c.denominator)

    d1 = d2 = 256
    assert_equal(256, c.denominator)

    d1, d2 = 512, 256
    assert_equal(512, c.denominator)

    d1, d2 = 256, 512
    assert_equal(512, c.denominator)

    d1, d2 = -(2**100), -(3**100)
    assert_equal(6**100, c.denominator)

    d1, d2 = 1, 2**100
    assert_equal(2**100, c.denominator)

    Complex.const_set(:Unify, unify_val) if f
  end

=begin
  def test_abs
    b = 2**100
    def b.*(x); self; end rescue nil
    def b.+(x); -1; end rescue nil
    assert_equal(Complex(0, 1), Complex(b, 1).abs)

    def b.+(x); Complex(0, 1); end rescue nil
    c = Complex(b, 1).abs
    assert_in_delta(1/Math.sqrt(2), c.real , 0.001)
    assert_in_delta(1/Math.sqrt(2), c.image, 0.001)

    def b.+(x); Complex(0, -1); end rescue nil
    c = Complex(b, 1).abs
    assert_in_delta( 1/Math.sqrt(2), c.real , 0.001)
    assert_in_delta(-1/Math.sqrt(2), c.image, 0.001)

    inf = 1.0/0.0
    nan = inf/inf
    assert_raise(Errno::EDOM, Errno::ERANGE) { Complex(1, nan).abs }
  end
=end

  def test_coerce
    c = Complex(6, 3)
    assert_equal(Complex(42, 0), c.coerce(42).first)
    assert_raise(TypeError) { c.coerce(Object.new) }

    o = Object.new
    def o.coerce(x); [x.real, x.image]; end
    assert_equal(9, c + o)
    assert_equal(3, c - o)
    assert_equal(18, c * o)
    assert_equal(2, c / o)
    assert_equal(216, c ** o)
  end

  def test_add2
    assert_equal(Complex(2**100, 1), Complex(0, 1) + 2**100)
  end

  def test_mul2
    assert_equal(Complex(0.0, 0.0), Complex(1.0, 1.0) * 0)
    assert_equal(Complex(0, 0), Complex(0, 0) * (2**100))
  end

  def test_expt2
    assert_equal(Complex(1, 0), Complex(2, 2) ** 0)
    assert_equal(Complex(0, -1), Complex(0, 1) ** (2**100-1))
    assert_equal(Complex(1, 0), Complex(1, 0) ** Rational(1, 2**100))
  end

  def test_fixed_bug
    if defined?(Rational) && !Rational.instance_variable_get('@RCS_ID')
      assert_equal(Complex(1), 1 ** Complex(1))
    end
    assert_equal('-1.0-0.0i', Complex(-1.0, -0.0).to_s)
  end

  def test_known_bug
  end

end
