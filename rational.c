/*
  rational.c: Coded by Tadayoshi Funaba 2008

  This implementation is based on Keiju Ishitsuka's Rational library
  which is written in ruby.
*/

#include "ruby.h"
#include <math.h>
#include <float.h>

#define NDEBUG
#include <assert.h>

#ifndef RATIONAL_NAME
#define RATIONAL_NAME "Rational"
#endif

#define ZERO INT2FIX(0)
#define ONE INT2FIX(1)
#define TWO INT2FIX(2)

VALUE rb_cRational;

static ID id_Unify, id_abs, id_cmp, id_convert, id_equal_p,
  id_expt, id_floor, id_format, id_idiv, id_inspect, id_negate, id_new,
  id_new_bang, id_to_f, id_to_i, id_to_s, id_truncate;

#define f_boolcast(x) ((x) ? Qtrue : Qfalse)

#define binop(n,op) \
inline static VALUE \
f_##n(VALUE x, VALUE y)\
{\
  return rb_funcall(x, op, 1, y);\
}

#define fun1(n) \
inline static VALUE \
f_##n(VALUE x)\
{\
    return rb_funcall(x, id_##n, 0);\
}

#define fun2(n) \
inline static VALUE \
f_##n(VALUE x, VALUE y)\
{\
    return rb_funcall(x, id_##n, 1, y);\
}

inline static VALUE
f_add(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(y)) {
	if (FIX2LONG(y) == 0)
	    r = x;
	else
	    r = rb_funcall(x, '+', 1, y);
    }
    else if (FIXNUM_P(x)) {
	if (FIX2LONG(x) == 0)
	    r = y;
	else
	    r = rb_funcall(x, '+', 1, y);
    }
    else
	r = rb_funcall(x, '+', 1, y);
    return r;
}

inline static VALUE
f_cmp(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(x) && FIXNUM_P(y)) {
	long c = FIX2LONG(x) - FIX2LONG(y);
	if (c > 0)
	    c = 1;
	else if (c < 0)
	    c = -1;
	r = INT2FIX(c);
    }
    else
	r = rb_funcall(x, id_cmp, 1, y);
    return r;
}

inline static VALUE
f_div(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(y) && FIX2LONG(y) == 1)
	r = x;
    else
	r = rb_funcall(x, '/', 1, y);
    return r;
}

inline static VALUE
f_gt_p(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(x) && FIXNUM_P(y))
	r = f_boolcast(FIX2LONG(x) > FIX2LONG(y));
    else
	r = rb_funcall(x, '>', 1, y);
    return r;
}

inline static VALUE
f_lt_p(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(x) && FIXNUM_P(y))
	r = f_boolcast(FIX2LONG(x) < FIX2LONG(y));
    else
	r = rb_funcall(x, '<', 1, y);
    return r;
}

binop(mod, '%')

inline static VALUE
f_mul(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(y)) {
	long _iy = FIX2LONG(y);
	if (_iy == 0) {
	    if (TYPE(x) == T_FLOAT)
		r = rb_float_new(0.0);
	    else
		r = ZERO;
	}
	else if (_iy == 1)
	    r = x;
	else
	    r = rb_funcall(x, '*', 1, y);
    }
    else if (FIXNUM_P(x)) {
	long _ix = FIX2LONG(x);
	if (_ix == 0) {
	    if (TYPE(y) == T_FLOAT)
		r = rb_float_new(0.0);
	    else
		r = ZERO;
	}
	else if (_ix == 1)
	    r = y;
	else
	    r = rb_funcall(x, '*', 1, y);
    }
    else
	r = rb_funcall(x, '*', 1, y);
    return r;
}

inline static VALUE
f_sub(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(y)) {
	if (FIX2LONG(y) == 0)
	    r = x;
	else
	    r = rb_funcall(x, '-', 1, y);
    }
    else
	r = rb_funcall(x, '-', 1, y);
    return r;
}

binop(xor, '^')

fun1(abs)
fun1(floor)
fun1(inspect)
fun1(negate)
fun1(to_f)
fun1(to_i)
fun1(to_s)
fun1(truncate)

inline static VALUE
f_equal_p(VALUE x, VALUE y)
{
    VALUE r;
    if (FIXNUM_P(x) && FIXNUM_P(y))
	r = f_boolcast(FIX2LONG(x) == FIX2LONG(y));
    else
	r = rb_funcall(x, id_equal_p, 1, y);
    return r;
}

fun2(expt)
fun2(idiv)

inline static VALUE
f_negative_p(VALUE x)
{
    VALUE r;
    if (FIXNUM_P(x))
	r = f_boolcast(FIX2LONG(x) < 0);
    else
	r = rb_funcall(x, '<', 1, ZERO);
    return r;
}

inline static VALUE
f_zero_p(VALUE x)
{
    VALUE r;
    if (FIXNUM_P(x))
	r = f_boolcast(FIX2LONG(x) == 0);
    else
	r = rb_funcall(x, id_equal_p, 1, ZERO);
    return r;
}

inline static VALUE
f_one_p(VALUE x)
{
    VALUE r;
    if (FIXNUM_P(x))
	r = f_boolcast(FIX2LONG(x) == 1);
    else
	r = rb_funcall(x, id_equal_p, 1, ONE);
    return r;
}

inline static VALUE
f_kind_of_p(VALUE x, VALUE c)
{
    return rb_obj_is_kind_of(x, c);
}

inline static VALUE
k_numeric_p(VALUE x)
{
    return f_kind_of_p(x, rb_cNumeric);
}

inline static VALUE
k_integer_p(VALUE x)
{
    return f_kind_of_p(x, rb_cInteger);
}

inline static VALUE
k_float_p(VALUE x)
{
    return f_kind_of_p(x, rb_cFloat);
}

inline static VALUE
k_rational_p(VALUE x)
{
    return f_kind_of_p(x, rb_cRational);
}

#ifndef NDEBUG
#define f_gcd f_gcd_orig
#endif

inline static long
i_gcd(long x, long y)
{
    long b;

    if (x < 0)
	x = -x;
    if (y < 0)
	y = -y;

    if (x == 0)
	return y;
    if (y == 0)
	return x;

    b = 0;
    while ((x & 1) == 0 && (y & 1) == 0) {
	b += 1;
	x >>= 1;
	y >>= 1;
    }

    while ((x & 1) == 0)
	x >>= 1;

    while ((y & 1) == 0)
	y >>= 1;

    while (x != y) {
	if (y > x) {
	    long t;
	    t = x;
	    x = y;
	    y = t;
	}
	x -= y;
	while ((x & 1) == 0)
	    x >>= 1;
    }

    return x << b;
}

inline static VALUE
f_gcd(VALUE x, VALUE y)
{
    VALUE z;

    if (FIXNUM_P(x) && FIXNUM_P(y))
	return LONG2NUM(i_gcd(FIX2LONG(x), FIX2LONG(y)));

    if (f_negative_p(x))
	x = f_negate(x);
    if (f_negative_p(y))
	y = f_negate(y);

    if (f_zero_p(x))
	return y;
    if (f_zero_p(y))
	return x;

    for (;;) {
	if (FIXNUM_P(x)) {
	    if (FIX2LONG(x) == 0)
		return y;
	    if (FIXNUM_P(y))
		return LONG2NUM(i_gcd(FIX2LONG(x), FIX2LONG(y)));
	}
	z = x;
	x = f_mod(y, x);
	y = z;
    }
    /* NOTREACHED */
}

#ifndef NDEBUG
#undef f_gcd

inline static VALUE
f_gcd(VALUE x, VALUE y)
{
    VALUE r = f_gcd_orig(x, y);
    if (!f_zero_p(r)) {
	assert(f_zero_p(f_mod(x, r)));
	assert(f_zero_p(f_mod(y, r)));
    }
    return r;
}
#endif

inline static VALUE
f_lcm(VALUE x, VALUE y)
{
    if (f_zero_p(x) || f_zero_p(y))
	return ZERO;
    else
	return f_abs(f_mul(f_div(x, f_gcd(x, y)), y));
}

#define get_dat1(x) \
    struct RRational *dat;\
    dat = ((struct RRational *)(x))

#define get_dat2(x,y) \
    struct RRational *adat, *bdat;\
    adat = ((struct RRational *)(x));\
    bdat = ((struct RRational *)(y))

inline static VALUE
nurat_s_new_internal(VALUE klass, VALUE num, VALUE den)
{
    NEWOBJ(obj, struct RRational);
    OBJSETUP(obj, klass, T_RATIONAL);

    obj->num = num;
    obj->den = den;

    return (VALUE)obj;
}

static VALUE
nurat_s_alloc(VALUE klass)
{
    return nurat_s_new_internal(klass, ZERO, ONE);
}

static VALUE
nurat_s_new_bang(int argc, VALUE *argv, VALUE klass)
{
    VALUE num, den;

    switch (rb_scan_args(argc, argv, "11", &num, &den)) {
      case 1:
	if (!k_integer_p(num))
	    num = f_to_i(num);
	den = ONE;
	break;
      default:
	if (!k_integer_p(num))
	    num = f_to_i(num);
	if (!k_integer_p(den))
	    den = f_to_i(den);

	switch (FIX2INT(f_cmp(den, ZERO))) {
	  case -1:
	    num = f_negate(num);
	    den = f_negate(den);
	    break;
	  case 0:
	    rb_raise(rb_eZeroDivError, "devided by zero");
	    break;
	}
	break;
    }

    return nurat_s_new_internal(klass, num, den);
}

inline static VALUE
f_rational_new_bang1(VALUE klass, VALUE x)
{
    return nurat_s_new_internal(klass, x, ONE);
}

inline static VALUE
f_rational_new_bang2(VALUE klass, VALUE x, VALUE y)
{
    assert(!f_negative_p(y));
    assert(!f_zero_p(y));
    return nurat_s_new_internal(klass, x, y);
}

#define f_unify_p(klass) rb_const_defined(klass, id_Unify)

inline static void
nurat_int_check(VALUE num)
{
    switch (TYPE(num)) {
      case T_FIXNUM:
      case T_BIGNUM:
	break;
      default:
	rb_raise(rb_eArgError, "not an integer");
    }
}

inline static VALUE
nurat_s_canonicalize_internal(VALUE klass, VALUE num, VALUE den)
{
    VALUE gcd;

    switch (FIX2INT(f_cmp(den, ZERO))) {
      case -1:
	num = f_negate(num);
	den = f_negate(den);
	break;
      case 0:
	rb_raise(rb_eZeroDivError, "devided by zero");
	break;
    }

    gcd = f_gcd(num, den);
    num = f_idiv(num, gcd);
    den = f_idiv(den, gcd);

    if (f_one_p(den) && f_unify_p(klass))
	return num;
    else
	return nurat_s_new_internal(klass, num, den);
}

inline static VALUE
nurat_s_canonicalize_internal_no_reduce(VALUE klass, VALUE num, VALUE den)
{
    switch (FIX2INT(f_cmp(den, ZERO))) {
      case -1:
	num = f_negate(num);
	den = f_negate(den);
	break;
      case 0:
	rb_raise(rb_eZeroDivError, "devided by zero");
	break;
    }

    if (f_equal_p(den, ONE) && f_unify_p(klass))
	return num;
    else
	return nurat_s_new_internal(klass, num, den);
}

#if 0
static VALUE
nurat_s_canonicalize(int argc, VALUE *argv, VALUE klass)
{
    VALUE num, den;

    if (rb_scan_args(argc, argv, "11", &num, &den) == 1) {
	den = ONE;
    }

    nurat_int_check(num);
    nurat_int_check(den);

    return nurat_s_canonicalize_internal(klass, num, den);
}
#endif

static VALUE
nurat_s_new(VALUE klass, VALUE num, VALUE den)
{
    nurat_int_check(num);
    nurat_int_check(den);

    return nurat_s_canonicalize_internal(klass, num, den);
}

static VALUE
nurat_s_new_m(int argc, VALUE *argv, VALUE klass)
{
    VALUE num, den;

    if (rb_scan_args(argc, argv, "11", &num, &den) == 1) {
	den = ONE;
    }
    return nurat_s_new(klass, num, den);
}

inline static VALUE
f_rational_new1(VALUE klass, VALUE x)
{
    assert(!k_rational_p(x));
    return nurat_s_canonicalize_internal(klass, x, ONE);
}

inline static VALUE
f_rational_new2(VALUE klass, VALUE x, VALUE y)
{
    assert(!k_rational_p(x));
    assert(!k_rational_p(y));
    return nurat_s_canonicalize_internal(klass, x, y);
}

inline static VALUE
f_rational_new_no_reduce1(VALUE klass, VALUE x)
{
    assert(!k_rational_p(x));
    return nurat_s_canonicalize_internal_no_reduce(klass, x, ONE);
}

inline static VALUE
f_rational_new_no_reduce2(VALUE klass, VALUE x, VALUE y)
{
    assert(!k_rational_p(x));
    assert(!k_rational_p(y));
    return nurat_s_canonicalize_internal_no_reduce(klass, x, y);
}

static VALUE
nurat_f_rational(int argc, VALUE *argv, VALUE klass)
{
    return rb_funcall2(rb_cRational, id_convert, argc, argv);
}

static VALUE
nurat_numerator(VALUE self)
{
    get_dat1(self);
    return dat->num;
}

static VALUE
nurat_denominator(VALUE self)
{
    get_dat1(self);
    return dat->den;
}

#ifndef NDEBUG
#define f_imul f_imul_orig
#endif

inline static VALUE
f_imul(long a, long b)
{
    VALUE r;
    long c;

    if (a == 0 || b == 0)
	return ZERO;
    else if (a == 1)
	return LONG2NUM(b);
    else if (b == 1)
	return LONG2NUM(a);

    c = a * b;
    r = LONG2NUM(c);
    if (NUM2LONG(r) != c || (c / a) != b)
	r = rb_big_mul(rb_int2big(a), rb_int2big(b));
    return r;
}

#ifndef NDEBUG
#undef f_imul

inline static VALUE
f_imul(long x, long y)
{
    VALUE r = f_imul_orig(x, y);
    assert(f_equal_p(r, f_mul(LONG2NUM(x), LONG2NUM(y))));
    return r;
}
#endif

inline static VALUE
f_addsub(VALUE self, VALUE anum, VALUE aden, VALUE bnum, VALUE bden, int k)
{
    VALUE num, den;

    if (FIXNUM_P(anum) && FIXNUM_P(aden) &&
	FIXNUM_P(bnum) && FIXNUM_P(bden)) {
	long an = FIX2LONG(anum);
	long ad = FIX2LONG(aden);
	long bn = FIX2LONG(bnum);
	long bd = FIX2LONG(bden);
	long ig = i_gcd(ad, bd);

	VALUE g = LONG2NUM(ig);
	VALUE a = f_imul(an, bd / ig);
	VALUE b = f_imul(bn, ad / ig);
	VALUE c;

	if (k == '+')
	    c = f_add(a, b);
	else
	    c = f_sub(a, b);

	b = f_idiv(aden, g);
	g = f_gcd(c, g);
	num = f_idiv(c, g);
	a = f_idiv(bden, g);
	den = f_mul(a, b);
    }
    else {
	VALUE g = f_gcd(aden, bden);
	VALUE a = f_mul(anum, f_idiv(bden, g));
	VALUE b = f_mul(bnum, f_idiv(aden, g));
	VALUE c;

	if (k == '+')
	    c = f_add(a, b);
	else
	    c = f_sub(a, b);

	b = f_idiv(aden, g);
	g = f_gcd(c, g);
	num = f_idiv(c, g);
	a = f_idiv(bden, g);
	den = f_mul(a, b);
    }
    return f_rational_new_no_reduce2(CLASS_OF(self), num, den);
}

static VALUE
nurat_add(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	{
	    get_dat1(self);

	    return f_addsub(self,
			    dat->num, dat->den,
			    other, ONE, '+');
	}
      case T_FLOAT:
	return f_add(f_to_f(self), other);
      case T_RATIONAL:
	{
	    get_dat2(self, other);

	    return f_addsub(self,
			    adat->num, adat->den,
			    bdat->num, bdat->den, '+');
	}
      default:
	return rb_num_coerce_bin(self, other, '+');
    }
}

static VALUE
nurat_sub(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	{
	    get_dat1(self);

	    return f_addsub(self,
			    dat->num, dat->den,
			    other, ONE, '-');
	}
      case T_FLOAT:
	return f_sub(f_to_f(self), other);
      case T_RATIONAL:
	{
	    get_dat2(self, other);

	    return f_addsub(self,
			    adat->num, adat->den,
			    bdat->num, bdat->den, '-');
	}
      default:
	return rb_num_coerce_bin(self, other, '-');
    }
}

inline static VALUE
f_muldiv(VALUE self, VALUE anum, VALUE aden, VALUE bnum, VALUE bden, int k)
{
    VALUE num, den;

    if (k == '/') {
	VALUE t;

	if (f_negative_p(bnum)) {
	    anum = f_negate(anum);
	    bnum = f_negate(bnum);
	}
	t = bnum;
	bnum = bden;
	bden = t;
    }

    if (FIXNUM_P(anum) && FIXNUM_P(aden) &&
	FIXNUM_P(bnum) && FIXNUM_P(bden)) {
	long an = FIX2LONG(anum);
	long ad = FIX2LONG(aden);
	long bn = FIX2LONG(bnum);
	long bd = FIX2LONG(bden);
	long g1 = i_gcd(an, bd);
	long g2 = i_gcd(ad, bn);

	num = f_imul(an / g1, bn / g2);
	den = f_imul(ad / g2, bd / g1);
    }
    else {
	VALUE g1 = f_gcd(anum, bden);
	VALUE g2 = f_gcd(aden, bnum);

	num = f_mul(f_idiv(anum, g1), f_idiv(bnum, g2));
	den = f_mul(f_idiv(aden, g2), f_idiv(bden, g1));
    }
    return f_rational_new_no_reduce2(CLASS_OF(self), num, den);
}

static VALUE
nurat_mul(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	{
	    get_dat1(self);

	    return f_muldiv(self,
			    dat->num, dat->den,
			    other, ONE, '*');
	}
      case T_FLOAT:
	return f_mul(f_to_f(self), other);
      case T_RATIONAL:
	{
	    get_dat2(self, other);

	    return f_muldiv(self,
			    adat->num, adat->den,
			    bdat->num, bdat->den, '*');
	}
      default:
	return rb_num_coerce_bin(self, other, '*');
    }
}

static VALUE
nurat_div(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	if (f_zero_p(other))
	    rb_raise(rb_eZeroDivError, "devided by zero");
	{
	    get_dat1(self);

	    return f_muldiv(self,
			    dat->num, dat->den,
			    other, ONE, '/');
	}
      case T_FLOAT:
	return rb_funcall(f_to_f(self), '/', 1, other);
      case T_RATIONAL:
	if (f_zero_p(other))
	    rb_raise(rb_eZeroDivError, "devided by zero");
	{
	    get_dat2(self, other);

	    return f_muldiv(self,
			    adat->num, adat->den,
			    bdat->num, bdat->den, '/');
	}
      default:
	return rb_num_coerce_bin(self, other, '/');
    }
}

static VALUE
nurat_fdiv(VALUE self, VALUE other)
{
    return f_div(f_to_f(self), other);
}

static VALUE
nurat_expt(VALUE self, VALUE other)
{
    if (f_zero_p(other))
	return f_rational_new_bang1(CLASS_OF(self), ONE);

    if (k_rational_p(other)) {
	get_dat1(other);

	if (f_one_p(dat->den))
	    other = dat->num; /* good? */
    }

    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	{
	    VALUE num, den;

	    get_dat1(self);

	    switch (FIX2INT(f_cmp(other, ZERO))) {
	      case 1:
		num = f_expt(dat->num, other);
		den = f_expt(dat->den, other);
		break;
	      case -1:
		num = f_expt(dat->den, f_negate(other));
		den = f_expt(dat->num, f_negate(other));
		break;
	      default:
		num = ONE;
		den = ONE;
		break;
	    }
	    return f_rational_new2(CLASS_OF(self), num, den);
	}
      case T_FLOAT:
      case T_RATIONAL:
	return f_expt(f_to_f(self), other);
      default:
	return rb_num_coerce_bin(self, other, id_expt);
    }
}

static VALUE
nurat_cmp(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	{
	    get_dat1(self);

	    if (FIXNUM_P(dat->den) && FIX2LONG(dat->den) == 1)
		return f_cmp(dat->num, other);
	    else
		return f_cmp(self, f_rational_new_bang1(CLASS_OF(self), other));
	}
      case T_FLOAT:
	return f_cmp(f_to_f(self), other);
      case T_RATIONAL:
	{
	    VALUE num1, num2;

	    get_dat2(self, other);

	    if (FIXNUM_P(adat->num) && FIXNUM_P(adat->den) &&
		FIXNUM_P(bdat->num) && FIXNUM_P(bdat->den)) {
		num1 = f_imul(FIX2LONG(adat->num), FIX2LONG(bdat->den));
		num2 = f_imul(FIX2LONG(bdat->num), FIX2LONG(adat->den));
	    }
	    else {
		num1 = f_mul(adat->num, bdat->den);
		num2 = f_mul(bdat->num, adat->den);
	    }
	    return f_cmp(f_sub(num1, num2), ZERO);
	}
      default:
	return rb_num_coerce_bin(self, other, id_cmp);
    }
}

static VALUE
nurat_equal_p(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	{
	    get_dat1(self);

	    if (!FIXNUM_P(dat->den))
		return Qfalse;
	    if (FIX2LONG(dat->den) != 1)
		return Qfalse;
	    if (f_equal_p(dat->num, other))
		return Qtrue;
	    else
		return Qfalse;
	}
      case T_FLOAT:
	return f_equal_p(f_to_f(self), other);
      case T_RATIONAL:
	{
	    get_dat2(self, other);

	    return f_boolcast(f_equal_p(adat->num, bdat->num) &&
			      f_equal_p(adat->den, bdat->den));
	}
      default:
	return f_equal_p(other, self);
    }
}

static VALUE
nurat_coerce(VALUE self, VALUE other)
{
    switch (TYPE(other)) {
      case T_FIXNUM:
      case T_BIGNUM:
	return rb_assoc_new(f_rational_new_bang1(CLASS_OF(self), other), self);
      case T_FLOAT:
	return rb_assoc_new(other, f_to_f(self));
    }

    rb_raise(rb_eTypeError, "%s can't be coerced into %s",
	     rb_obj_classname(other), rb_obj_classname(self));
    return Qnil;
}

static VALUE
nurat_idiv(VALUE self, VALUE other)
{
    return f_floor(f_div(self, other));
}

static VALUE
nurat_mod(VALUE self, VALUE other)
{
    VALUE val = f_floor(f_div(self, other));
    return f_sub(self, f_mul(other, val));
}

static VALUE
nurat_divmod(VALUE self, VALUE other)
{
    VALUE val = f_floor(f_div(self, other));
    return rb_assoc_new(val, f_sub(self, f_mul(other, val)));
}

#if 0
static VALUE
nurat_quot(VALUE self, VALUE other)
{
    return f_truncate(f_div(self, other));
}
#endif

static VALUE
nurat_rem(VALUE self, VALUE other)
{
    VALUE val = f_truncate(f_div(self, other));
    return f_sub(self, f_mul(other, val));
}

#if 0
static VALUE
nurat_quotrem(VALUE self, VALUE other)
{
    VALUE val = f_truncate(f_div(self, other));
    return rb_assoc_new(val, f_sub(self, f_mul(other, val)));
}
#endif

static VALUE
nurat_abs(VALUE self)
{
    if (!f_negative_p(self))
	return self;
    else
	return f_negate(self);
}

#if 0
static VALUE
nurat_true(VALUE self)
{
    return Qtrue;
}
#endif

static VALUE
nurat_floor(VALUE self)
{
    get_dat1(self);
    return f_idiv(dat->num, dat->den);
}

static VALUE
nurat_ceil(VALUE self)
{
    get_dat1(self);
    return f_negate(f_idiv(f_negate(dat->num), dat->den));
}

static VALUE
nurat_truncate(VALUE self)
{
    get_dat1(self);
    if (f_negative_p(dat->num))
	return f_negate(f_idiv(f_negate(dat->num), dat->den));
    return f_idiv(dat->num, dat->den);
}

static VALUE
nurat_round(VALUE self)
{
    get_dat1(self);

    if (f_negative_p(dat->num)) {
	VALUE num, den;

	num = f_negate(dat->num);
	num = f_add(f_mul(num, TWO), dat->den);
	den = f_mul(dat->den, TWO);
	return f_negate(f_idiv(num, den));
    }
    else {
	VALUE num = f_add(f_mul(dat->num, TWO), dat->den);
	VALUE den = f_mul(dat->den, TWO);
	return f_idiv(num, den);
    }
}

#define f_size(x) rb_funcall(x, rb_intern("size"), 0)
#define f_rshift(x,y) rb_funcall(x, rb_intern(">>"), 1, y)

inline static long
i_ilog2(VALUE x)
{
    long q, r, fx;

    assert(!f_lt_p(x, ONE));

    q = (NUM2LONG(f_size(x)) - sizeof(long)) * 8 + 1;

    if (q > 0)
	x = f_rshift(x, LONG2NUM(q));

    fx = NUM2LONG(x);

    r = -1;
    while (fx) {
	fx >>= 1;
	r += 1;
    }

    return q + r;
}

static VALUE
nurat_to_f(VALUE self)
{
    VALUE num, den;
    int minus = 0;
    long nl, dl, ml, ne, de;
    int e;
    double f;

    {
	get_dat1(self);

	if (f_zero_p(dat->num))
	    return rb_float_new(0.0);

	num = dat->num;
	den = dat->den;
    }

    if (f_negative_p(num)) {
	num = f_negate(num);
	minus = 1;
    }

    nl = i_ilog2(num);
    dl = i_ilog2(den);
    ml = (long)(log(DBL_MAX) / log(2.0) - 1); /* should be a static */

    ne = 0;
    if (nl > ml) {
	ne = nl - ml;
	num = f_rshift(num, LONG2NUM(ne));
    }

    de = 0;
    if (dl > ml) {
	de = dl - ml;
	den = f_rshift(den, LONG2NUM(de));
    }

    e = (int)(ne - de);

    if ((e > DBL_MAX_EXP) || (e < DBL_MIN_EXP)) {
	rb_warning("%s out of Float range", rb_obj_classname(self));
	return rb_float_new(e > 0 ? HUGE_VAL : 0.0);
    }

    f = NUM2DBL(num) / NUM2DBL(den);
    if (minus)
	f = -f;
    f = ldexp(f, e);

    if (isinf(f) || isnan(f))
	rb_warning("%s out of Float range", rb_obj_classname(self));

    return rb_float_new(f);
}

static VALUE
nurat_to_r(VALUE self)
{
    return self;
}

static VALUE
nurat_hash(VALUE self)
{
    get_dat1(self);
    return f_xor(dat->num, dat->den);
}

static VALUE
nurat_to_s(VALUE self)
{
    get_dat1(self);

    if (f_one_p(dat->den))
	return f_to_s(dat->num);
    else
	return rb_funcall(rb_mKernel, id_format, 3,
			  rb_str_new2("%d/%d"), dat->num, dat->den);
}

static VALUE
nurat_inspect(VALUE self)
{
    get_dat1(self);
    return rb_funcall(rb_mKernel, id_format, 3,
		      rb_str_new2("Rational(%d, %d)"), dat->num, dat->den);
}

static VALUE
nurat_marshal_dump(VALUE self)
{
    get_dat1(self);
    return rb_assoc_new(dat->num, dat->den);
}

static VALUE
nurat_marshal_load(VALUE self, VALUE a)
{
    get_dat1(self);
    dat->num = RARRAY_AT(a, 0);
    dat->den = RARRAY_AT(a, 1);

    if (f_zero_p(dat->den))
	rb_raise(rb_eZeroDivError, "devided by zero");

    return self;
}

/* --- */

VALUE
rb_gcd(VALUE self, VALUE other)
{
    nurat_int_check(other);
    return f_gcd(self, other);
}

VALUE
rb_lcm(VALUE self, VALUE other)
{
    nurat_int_check(other);
    return f_lcm(self, other);
}

VALUE
rb_gcdlcm(VALUE self, VALUE other)
{
    nurat_int_check(other);
    return rb_assoc_new(f_gcd(self, other), f_lcm(self, other));
}

VALUE
rb_rational_raw(VALUE x, VALUE y)
{
    return nurat_s_new_internal(rb_cRational, x, y);
}

VALUE
rb_rational_new(VALUE x, VALUE y)
{
    return nurat_s_canonicalize_internal(rb_cRational, x, y);
}

static VALUE nurat_s_convert(int argc, VALUE *argv, VALUE klass);

VALUE
rb_Rational(VALUE x, VALUE y)
{
    VALUE a[2];
    a[0] = x;
    a[1] = y;
    return nurat_s_convert(2, a, rb_cRational);
}

static VALUE
nilclass_to_r(VALUE self)
{
    return rb_rational_new1(INT2FIX(0));
}

static VALUE
integer_to_r(VALUE self)
{
    return rb_rational_new1(self);
}

static VALUE
float_decode(VALUE self)
{
    double f;
    int n;

    f = frexp(RFLOAT_VALUE(self), &n);
    f = ldexp(f, DBL_MANT_DIG);
    n -= DBL_MANT_DIG;
    return rb_assoc_new(f_to_i(rb_float_new(f)), INT2FIX(n));
}

static VALUE
float_to_r(VALUE self)
{
    VALUE a = float_decode(self);
    return f_mul(RARRAY_AT(a, 0),
		 f_expt(INT2FIX(FLT_RADIX), RARRAY_AT(a, 1)));
}

static VALUE rat_pat, an_e_pat, a_dot_pat, underscores_pat, an_underscore;

#define DIGITS "(?:\\d(?:_\\d|\\d)*)"
#define NUMERATOR "(?:" DIGITS "?\\.)?" DIGITS "(?:[eE][-+]?" DIGITS ")?"
#define DENOMINATOR "[-+]?" DIGITS
#define PATTERN "\\A([-+])?(" NUMERATOR ")(?:\\/(" DENOMINATOR "))?"

static void
make_patterns(void)
{
    static char rat_pat_source[] = PATTERN;
    static char an_e_pat_source[] = "[eE]";
    static char a_dot_pat_source[] = "\\.";
    static char underscores_pat_source[] = "_+";

    rat_pat = rb_reg_new(rat_pat_source, sizeof rat_pat_source - 1, 0);
    rb_global_variable(&rat_pat);

    an_e_pat = rb_reg_new(an_e_pat_source, sizeof an_e_pat_source - 1, 0);
    rb_global_variable(&an_e_pat);

    a_dot_pat = rb_reg_new(a_dot_pat_source, sizeof a_dot_pat_source - 1, 0);
    rb_global_variable(&a_dot_pat);

    underscores_pat = rb_reg_new(underscores_pat_source,
				 sizeof underscores_pat_source - 1, 0);
    rb_global_variable(&underscores_pat);

    an_underscore = rb_str_new2("_");
    rb_global_variable(&an_underscore);
}

#define id_strip rb_intern("strip")
#define f_strip(x) rb_funcall(x, id_strip, 0)

#define id_match rb_intern("match")
#define f_match(x,y) rb_funcall(x, id_match, 1, y)

#define id_aref rb_intern("[]")
#define f_aref(x,y) rb_funcall(x, id_aref, 1, y)

#define id_post_match rb_intern("post_match")
#define f_post_match(x) rb_funcall(x, id_post_match, 0)

#define id_split rb_intern("split")
#define f_split(x,y) rb_funcall(x, id_split, 1, y)

#include <ctype.h>

static VALUE
string_to_r_internal(VALUE self)
{
    VALUE s, m;

    s = f_strip(self);

    if (RSTRING_LEN(s) == 0)
	return rb_assoc_new(Qnil, self);

    m = f_match(rat_pat, s);

    if (!NIL_P(m)) {
	VALUE v, ifp, exp, ip, fp;
	VALUE si = f_aref(m, INT2FIX(1));
	VALUE nu = f_aref(m, INT2FIX(2));
	VALUE de = f_aref(m, INT2FIX(3));
	VALUE re = f_post_match(m);

	{
	    VALUE a;

	    a = f_split(nu, an_e_pat);
	    ifp = RARRAY_AT(a, 0);
	    if (RARRAY_LEN(a) != 2)
		exp = Qnil;
	    else
		exp = RARRAY_AT(a, 1);

	    a = f_split(ifp, a_dot_pat);
	    ip = RARRAY_AT(a, 0);
	    if (RARRAY_LEN(a) != 2)
		fp = Qnil;
	    else
		fp = RARRAY_AT(a, 1);
	}

	v = rb_rational_new1(f_to_i(ip));

	if (!NIL_P(fp)) {
	    char *p = StringValuePtr(fp);
	    long count = 0;
	    VALUE l;

	    while (*p) {
		if (rb_isdigit(*p))
		    count++;
		p++;
	    }

	    l = f_expt(INT2FIX(10), LONG2NUM(count));
	    v = f_mul(v, l);
	    v = f_add(v, f_to_i(fp));
	    v = f_div(v, l);
	}
	if (!NIL_P(exp))
	    v = f_mul(v, f_expt(INT2FIX(10), f_to_i(exp)));
	if (!NIL_P(si) && *StringValuePtr(si) == '-')
	    v = f_negate(v);
	if (!NIL_P(de))
	    v = f_div(v, f_to_i(de));

	return rb_assoc_new(v, re);
    }
    return rb_assoc_new(Qnil, self);
}

static VALUE
string_to_r_strict(VALUE self)
{
    VALUE a = string_to_r_internal(self);
    if (NIL_P(RARRAY_AT(a, 0)) || RSTRING_LEN(RARRAY_AT(a, 1)) > 0) {
	VALUE s = f_inspect(self);
	rb_raise(rb_eArgError, "invalid value for Rational: %s",
		 StringValuePtr(s));
    }
    return RARRAY_AT(a, 0);
}

#define id_gsub rb_intern("gsub")
#define f_gsub(x,y,z) rb_funcall(x, id_gsub, 2, y, z)

static VALUE
string_to_r(VALUE self)
{
    VALUE s = f_gsub(self, underscores_pat, an_underscore);
    VALUE a = string_to_r_internal(s);
    if (!NIL_P(RARRAY_AT(a, 0)))
	return RARRAY_AT(a, 0);
    return rb_rational_new1(INT2FIX(0));
}

#define id_to_r rb_intern("to_r")
#define f_to_r(x) rb_funcall(x, id_to_r, 0)

static VALUE
nurat_s_convert(int argc, VALUE *argv, VALUE klass)
{
    VALUE a1, a2;

    if (rb_scan_args(argc, argv, "02", &a1, &a2) == 1) {
	a2 = ONE;
    }

    switch (TYPE(a1)) {
      case T_COMPLEX:
	if (k_float_p(RCOMPLEX(a1)->image) || !f_zero_p(RCOMPLEX(a1)->image)) {
	    VALUE s = f_to_s(a1);
	    rb_raise(rb_eRangeError, "can't accept %s",
		     StringValuePtr(s));
	}
	a1 = RCOMPLEX(a1)->real;
    }

    switch (TYPE(a2)) {
      case T_COMPLEX:
	if (k_float_p(RCOMPLEX(a2)->image) || !f_zero_p(RCOMPLEX(a2)->image)) {
	    VALUE s = f_to_s(a2);
	    rb_raise(rb_eRangeError, "can't accept %s",
		     StringValuePtr(s));
	}
	a2 = RCOMPLEX(a2)->real;
    }

    switch (TYPE(a1)) {
      case T_FIXNUM:
      case T_BIGNUM:
	break;
      case T_FLOAT:
	a1 = f_to_r(a1);
	break;
      case T_STRING:
	a1 = string_to_r_strict(a1);
	break;
    }

    switch (TYPE(a2)) {
      case T_FIXNUM:
      case T_BIGNUM:
	break;
      case T_FLOAT:
	a2 = f_to_r(a2);
	break;
      case T_STRING:
	a2 = string_to_r_strict(a2);
	break;
    }

    switch (TYPE(a1)) {
      case T_RATIONAL:
	if (NIL_P(a2) || f_zero_p(a2))
	    return a1;
	else
	    return f_div(a1, a2);
    }

    switch (TYPE(a2)) {
      case T_RATIONAL:
	return f_div(a1, a2);
    }

    return nurat_s_new(klass, a1, a2);
}

static VALUE
nurat_s_induced_from(VALUE klass, VALUE n)
{
    return f_to_r(n);
}

void
Init_Rational(void)
{
    assert(fprintf(stderr, "assert() is now active\n"));

    id_Unify = rb_intern("Unify");
    id_abs = rb_intern("abs");
    id_cmp = rb_intern("<=>");
    id_convert = rb_intern("convert");
    id_equal_p = rb_intern("==");
    id_expt = rb_intern("**");
    id_floor = rb_intern("floor");
    id_format = rb_intern("format");
    id_idiv = rb_intern("div");
    id_inspect = rb_intern("inspect");
    id_negate = rb_intern("-@");
    id_new = rb_intern("new");
    id_new_bang = rb_intern("new!");
    id_to_f = rb_intern("to_f");
    id_to_i = rb_intern("to_i");
    id_to_s = rb_intern("to_s");
    id_truncate = rb_intern("truncate");

    rb_cRational = rb_define_class(RATIONAL_NAME, rb_cNumeric);

    rb_define_alloc_func(rb_cRational, nurat_s_alloc);
//    rb_funcall(rb_cRational, rb_intern("private_class_method"), 1,
//	       ID2SYM(rb_intern("allocate")));

    rb_define_singleton_method(rb_cRational, "new!", nurat_s_new_bang, -1);
//    rb_funcall(rb_cRational, rb_intern("private_class_method"), 1,
//	       ID2SYM(rb_intern("new!")));

    rb_define_singleton_method(rb_cRational, "new", nurat_s_new_m, -1);
//    rb_funcall(rb_cRational, rb_intern("private_class_method"), 1,
//	       ID2SYM(rb_intern("new")));

    rb_define_global_function(RATIONAL_NAME, nurat_f_rational, -1);

    rb_define_method(rb_cRational, "numerator", nurat_numerator, 0);
    rb_define_method(rb_cRational, "denominator", nurat_denominator, 0);

    rb_define_method(rb_cRational, "+", nurat_add, 1);
    rb_define_method(rb_cRational, "-", nurat_sub, 1);
    rb_define_method(rb_cRational, "*", nurat_mul, 1);
    rb_define_method(rb_cRational, "/", nurat_div, 1);
    rb_define_method(rb_cRational, "quo", nurat_div, 1);
    rb_define_method(rb_cRational, "fdiv", nurat_fdiv, 1);
    rb_define_method(rb_cRational, "**", nurat_expt, 1);

    rb_define_method(rb_cRational, "<=>", nurat_cmp, 1);
    rb_define_method(rb_cRational, "==", nurat_equal_p, 1);
    rb_define_method(rb_cRational, "coerce", nurat_coerce, 1);

    rb_define_method(rb_cRational, "div", nurat_idiv, 1);
#if NUBY
    rb_define_method(rb_cRational, "//", nurat_idiv, 1);
#endif
    rb_define_method(rb_cRational, "modulo", nurat_mod, 1);
    rb_define_method(rb_cRational, "%", nurat_mod, 1);
    rb_define_method(rb_cRational, "divmod", nurat_divmod, 1);

#if 0
    rb_define_method(rb_cRational, "quot", nurat_quot, 1);
#endif
    rb_define_method(rb_cRational, "remainder", nurat_rem, 1);
#if 0
    rb_define_method(rb_cRational, "quotrem", nurat_quotrem, 1);
#endif

    rb_define_method(rb_cRational, "abs", nurat_abs, 0);

#if 0
    rb_define_method(rb_cRational, "rational?", nurat_true, 0);
    rb_define_method(rb_cRational, "exact?", nurat_true, 0);
#endif

    rb_define_method(rb_cRational, "floor", nurat_floor, 0);
    rb_define_method(rb_cRational, "ceil", nurat_ceil, 0);
    rb_define_method(rb_cRational, "truncate", nurat_truncate, 0);
    rb_define_method(rb_cRational, "round", nurat_round, 0);

    rb_define_method(rb_cRational, "to_i", nurat_truncate, 0);
    rb_define_method(rb_cRational, "to_f", nurat_to_f, 0);
    rb_define_method(rb_cRational, "to_r", nurat_to_r, 0);

    rb_define_method(rb_cRational, "hash", nurat_hash, 0);

    rb_define_method(rb_cRational, "to_s", nurat_to_s, 0);
    rb_define_method(rb_cRational, "inspect", nurat_inspect, 0);

    rb_define_method(rb_cRational, "marshal_dump", nurat_marshal_dump, 0);
    rb_define_method(rb_cRational, "marshal_load", nurat_marshal_load, 1);

    /* --- */

    rb_define_method(rb_cInteger, "gcd", rb_gcd, 1);
    rb_define_method(rb_cInteger, "lcm", rb_lcm, 1);
    rb_define_method(rb_cInteger, "gcdlcm", rb_gcdlcm, 1);

    rb_define_method(rb_cNilClass, "to_r", nilclass_to_r, 0);
    rb_define_method(rb_cInteger, "to_r", integer_to_r, 0);
    rb_define_method(rb_cFloat, "to_r", float_to_r, 0);

    make_patterns();

    rb_define_method(rb_cString, "to_r", string_to_r, 0);

    rb_define_singleton_method(rb_cRational, "convert", nurat_s_convert, -1);
//    rb_funcall(rb_cRational, rb_intern("private_class_method"), 1,
//	       ID2SYM(rb_intern("convert")));

    rb_include_module(rb_cRational, rb_mPrecision);
    rb_define_singleton_method(rb_cRational, "induced_from",
			       nurat_s_induced_from, 1);
}
