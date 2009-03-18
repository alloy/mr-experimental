/**********************************************************************

  struct.c -

  $Author: nobu $
  created at: Tue Mar 22 18:44:30 JST 1995

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#include "ruby/ruby.h"
#include "ruby/node.h"
#include "roxor.h"

VALUE rb_cStruct;

static VALUE struct_alloc(VALUE);

VALUE
rb_struct_iv_get(VALUE c, const char *name)
{
    ID id;

    id = rb_intern(name);
    for (;;) {
	if (rb_ivar_defined(c, id))
	    return rb_ivar_get(c, id);
	c = RCLASS_SUPER(c);
	if (c == 0 || c == rb_cStruct)
	    return Qnil;
    }
}

VALUE
rb_struct_s_members(VALUE klass)
{
    VALUE members = rb_struct_iv_get(klass, "__members__");

    if (NIL_P(members)) {
	rb_raise(rb_eTypeError, "uninitialized struct");
    }
    if (TYPE(members) != T_ARRAY) {
	rb_raise(rb_eTypeError, "corrupted struct");
    }
    return members;
}

VALUE
rb_struct_members(VALUE s)
{
    VALUE members = rb_struct_s_members(rb_obj_class(s));

    if (RSTRUCT_LEN(s) != RARRAY_LEN(members)) {
	rb_raise(rb_eTypeError, "struct size differs (%ld required %ld given)",
		 RARRAY_LEN(members), RSTRUCT_LEN(s));
    }
    return members;
}

static VALUE
rb_struct_s_members_m(VALUE klass)
{
#if WITH_OBJC
    return rb_ary_dup(rb_struct_s_members(klass));
#else
    VALUE members, ary;
    VALUE *p, *pend;

    members = rb_struct_s_members(klass);
    ary = rb_ary_new2(RARRAY_LEN(members));
    p = RARRAY_PTR(members); pend = p + RARRAY_LEN(members);
    while (p < pend) {
	rb_ary_push(ary, *p);
	p++;
    }

    return ary;
#endif
}

/*
 *  call-seq:
 *     struct.members    => array
 *  
 *  Returns an array of strings representing the names of the instance
 *  variables.
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     joe.members   #=> [:name, :address, :zip]
 */

static VALUE
rb_struct_members_m(VALUE obj, SEL sel)
{
    return rb_struct_s_members_m(rb_obj_class(obj));
}

VALUE
rb_struct_getmember(VALUE obj, ID id)
{
    VALUE members, slot;
    long i;

    members = rb_struct_members(obj);
    slot = ID2SYM(id);
    for (i=0; i<RARRAY_LEN(members); i++) {
	if (RARRAY_AT(members, i) == slot) {
	    return RSTRUCT_PTR(obj)[i];
	}
    }
    rb_name_error(id, "%s is not struct member", rb_id2name(id));
    return Qnil;		/* not reached */
}

static VALUE
rb_struct_ref(VALUE obj)
{
    return rb_struct_getmember(obj, rb_frame_this_func());
}

static VALUE rb_struct_ref0(VALUE obj) {return RSTRUCT_PTR(obj)[0];}
static VALUE rb_struct_ref1(VALUE obj) {return RSTRUCT_PTR(obj)[1];}
static VALUE rb_struct_ref2(VALUE obj) {return RSTRUCT_PTR(obj)[2];}
static VALUE rb_struct_ref3(VALUE obj) {return RSTRUCT_PTR(obj)[3];}
static VALUE rb_struct_ref4(VALUE obj) {return RSTRUCT_PTR(obj)[4];}
static VALUE rb_struct_ref5(VALUE obj) {return RSTRUCT_PTR(obj)[5];}
static VALUE rb_struct_ref6(VALUE obj) {return RSTRUCT_PTR(obj)[6];}
static VALUE rb_struct_ref7(VALUE obj) {return RSTRUCT_PTR(obj)[7];}
static VALUE rb_struct_ref8(VALUE obj) {return RSTRUCT_PTR(obj)[8];}
static VALUE rb_struct_ref9(VALUE obj) {return RSTRUCT_PTR(obj)[9];}

#define N_REF_FUNC (sizeof(ref_func) / sizeof(ref_func[0]))

static VALUE (*const ref_func[])(VALUE) = {
    rb_struct_ref0,
    rb_struct_ref1,
    rb_struct_ref2,
    rb_struct_ref3,
    rb_struct_ref4,
    rb_struct_ref5,
    rb_struct_ref6,
    rb_struct_ref7,
    rb_struct_ref8,
    rb_struct_ref9,
};

static void
rb_struct_modify(VALUE s)
{
    if (OBJ_FROZEN(s)) rb_error_frozen("Struct");
    if (!OBJ_TAINTED(s) && rb_safe_level() >= 4)
       rb_raise(rb_eSecurityError, "Insecure: can't modify Struct");
}

static VALUE
rb_struct_set(VALUE obj, VALUE val)
{
    VALUE members, slot;
    long i;

    members = rb_struct_members(obj);
    rb_struct_modify(obj);
    for (i=0; i<RARRAY_LEN(members); i++) {
	slot = RARRAY_AT(members, i);
	if (rb_id_attrset(SYM2ID(slot)) == rb_frame_this_func()) {
	    return RSTRUCT_PTR(obj)[i] = val;
	}
    }
    rb_name_error(rb_frame_this_func(), "`%s' is not a struct member",
		  rb_id2name(rb_frame_this_func()));
    return Qnil;		/* not reached */
}

static VALUE
make_struct(VALUE name, VALUE members, VALUE klass)
{
    VALUE nstr;
    ID id;
    long i;

    OBJ_FREEZE(members);
    if (NIL_P(name)) {
	nstr = rb_class_new(klass);
#if !WITH_OBJC
	rb_make_metaclass(nstr, RBASIC(klass)->klass);
#endif
	rb_class_inherited(klass, nstr);
    }
    else {
	/* old style: should we warn? */
	name = rb_str_to_str(name);
	id = rb_to_id(name);
	if (!rb_is_const_id(id)) {
	    rb_name_error(id, "identifier %s needs to be constant", StringValuePtr(name));
	}
	if (rb_const_defined_at(klass, id)) {
	    rb_warn("redefining constant Struct::%s", StringValuePtr(name));
	    rb_mod_remove_const(klass, ID2SYM(id));
	}
	nstr = rb_define_class_under(klass, rb_id2name(id), klass);
    }
    rb_iv_set(nstr, "__size__", LONG2NUM(RARRAY_LEN(members)));
    rb_iv_set(nstr, "__members__", members);

    rb_define_alloc_func(nstr, struct_alloc);
    rb_define_singleton_method(nstr, "new", rb_class_new_instance, -1);
    rb_define_singleton_method(nstr, "[]", rb_class_new_instance, -1);
    rb_define_singleton_method(nstr, "members", rb_struct_s_members_m, 0);
    for (i=0; i< RARRAY_LEN(members); i++) {
	ID id = SYM2ID(RARRAY_AT(members, i));
	if (rb_is_local_id(id) || rb_is_const_id(id)) {
	    if (i < N_REF_FUNC) {
		rb_define_method_id(nstr, id, ref_func[i], 0);
	    }
	    else {
		rb_define_method_id(nstr, id, rb_struct_ref, 0);
	    }
	    rb_define_method_id(nstr, rb_id_attrset(id), rb_struct_set, 1);
	}
    }

    return nstr;
}

VALUE
rb_struct_alloc_noinit(VALUE klass)
{
    return struct_alloc(klass);
}

VALUE
rb_struct_define_without_accessor(const char *class_name, VALUE super, rb_alloc_func_t alloc, ...)
{
    VALUE klass;
    va_list ar;
    VALUE members;
    long i;
    char *name;

    members = rb_ary_new2(0);
    va_start(ar, alloc);
    i = 0;
    while ((name = va_arg(ar, char*)) != NULL) {
        rb_ary_push(members, ID2SYM(rb_intern(name)));
    }
    va_end(ar);
    OBJ_FREEZE(members);

    if (class_name) {
        klass = rb_define_class(class_name, super);
    }
    else {
	klass = rb_class_new(super);
	rb_make_metaclass(klass, RBASIC(super)->klass);
	rb_class_inherited(super, klass);
    }

    rb_iv_set(klass, "__size__", LONG2NUM(RARRAY_LEN(members)));
    rb_iv_set(klass, "__members__", members);

    if (alloc)
        rb_define_alloc_func(klass, alloc);
    else
        rb_define_alloc_func(klass, struct_alloc);

    return klass;
}

VALUE
rb_struct_define(const char *name, ...)
{
    va_list ar;
    VALUE nm, ary;
    char *mem;

    if (!name) nm = Qnil;
    else nm = rb_str_new2(name);
    ary = rb_ary_new();

    va_start(ar, name);
    while ((mem = va_arg(ar, char*)) != 0) {
	ID slot = rb_intern(mem);
	rb_ary_push(ary, ID2SYM(slot));
    }
    va_end(ar);

    return make_struct(nm, ary, rb_cStruct);
}

/*
 *  call-seq:
 *     Struct.new( [aString] [, aSym]+> )    => StructClass
 *     StructClass.new(arg, ...)             => obj
 *     StructClass[arg, ...]                 => obj
 *
 *  Creates a new class, named by <i>aString</i>, containing accessor
 *  methods for the given symbols. If the name <i>aString</i> is
 *  omitted, an anonymous structure class will be created. Otherwise,
 *  the name of this struct will appear as a constant in class
 *  <code>Struct</code>, so it must be unique for all
 *  <code>Struct</code>s in the system and should start with a capital
 *  letter. Assigning a structure class to a constant effectively gives
 *  the class the name of the constant.
 *     
 *  <code>Struct::new</code> returns a new <code>Class</code> object,
 *  which can then be used to create specific instances of the new
 *  structure. The number of actual parameters must be
 *  less than or equal to the number of attributes defined for this
 *  class; unset parameters default to \nil{}.  Passing too many
 *  parameters will raise an \E{ArgumentError}.
 *
 *  The remaining methods listed in this section (class and instance)
 *  are defined for this generated class. 
 *     
 *     # Create a structure with a name in Struct
 *     Struct.new("Customer", :name, :address)    #=> Struct::Customer
 *     Struct::Customer.new("Dave", "123 Main")   #=> #<struct Struct::Customer name="Dave", address="123 Main">
 *     
 *     # Create a structure named by its constant
 *     Customer = Struct.new(:name, :address)     #=> Customer
 *     Customer.new("Dave", "123 Main")           #=> #<struct Customer name="Dave", address="123 Main">
 */

VALUE rb_mod_module_eval(VALUE mod, SEL sel, int argc, VALUE *argv);

static VALUE
rb_struct_s_def(VALUE klass, SEL sel, int argc, VALUE *argv)
{
    VALUE name, rest;
    long i;
    VALUE st;
    ID id;

    rb_scan_args(argc, argv, "1*", &name, &rest);
    if (!NIL_P(name) && SYMBOL_P(name)) {
	rb_ary_unshift(rest, name);
	name = Qnil;
    }
    for (i=0; i<RARRAY_LEN(rest); i++) {
	id = rb_to_id(RARRAY_AT(rest, i));
	rb_ary_store(rest, i, ID2SYM(id));
    }
    st = make_struct(name, rest, klass);
    if (rb_block_given_p()) {
	rb_mod_module_eval(st, 0, 0, 0);
    }

    return st;
}

/*
 */

VALUE
rb_struct_initialize(VALUE self, SEL sel, VALUE values)
{
    VALUE klass = rb_obj_class(self);
    VALUE size;
    long n;

    rb_struct_modify(self);
    size = rb_struct_iv_get(klass, "__size__");
    n = FIX2LONG(size);
    if (n < RARRAY_LEN(values)) {
	rb_raise(rb_eArgError, "struct size differs");
    }
    MEMCPY(RSTRUCT_PTR(self), RARRAY_PTR(values), VALUE, RARRAY_LEN(values));
    if (n > RARRAY_LEN(values)) {
	rb_mem_clear(RSTRUCT_PTR(self)+RARRAY_LEN(values),
		     n-RARRAY_LEN(values));
    }
    return Qnil;
}

static VALUE
struct_alloc(VALUE klass)
{
    VALUE size;
    long n;
    NEWOBJ(st, struct RStruct);
    OBJSETUP(st, klass, T_STRUCT);

    size = rb_struct_iv_get(klass, "__size__");
    n = FIX2LONG(size);

    if (0 < n && n <= RSTRUCT_EMBED_LEN_MAX) {
        RBASIC(st)->flags &= ~RSTRUCT_EMBED_LEN_MASK;
        RBASIC(st)->flags |= n << RSTRUCT_EMBED_LEN_SHIFT;
	rb_mem_clear(st->as.ary, n);
    }
    else {
	GC_WB(&st->as.heap.ptr, ALLOC_N(VALUE, n));
	rb_mem_clear(st->as.heap.ptr, n);
	st->as.heap.len = n;
    }

    return (VALUE)st;
}

VALUE
rb_struct_alloc(VALUE klass, VALUE values)
{
    return rb_class_new_instance(RARRAY_LEN(values), (VALUE *)RARRAY_PTR(values), klass);
}

VALUE
rb_struct_new(VALUE klass, ...)
{
    VALUE sz, *mem;
    long size, i;
    va_list args;

    sz = rb_struct_iv_get(klass, "__size__");
    size = FIX2LONG(sz); 
    mem = ALLOCA_N(VALUE, size);
    va_start(args, klass);
    for (i=0; i<size; i++) {
	mem[i] = va_arg(args, VALUE);
    }
    va_end(args);

    return rb_class_new_instance(size, mem, klass);
}

/*
 *  call-seq:
 *     struct.each {|obj| block }  => struct
 *  
 *  Calls <i>block</i> once for each instance variable, passing the
 *  value as a parameter.
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     joe.each {|x| puts(x) }
 *     
 *  <em>produces:</em>
 *     
 *     Joe Smith
 *     123 Maple, Anytown NC
 *     12345
 */

static VALUE
rb_struct_each(VALUE s, SEL sel)
{
    long i;

    RETURN_ENUMERATOR(s, 0, 0);
    for (i=0; i<RSTRUCT_LEN(s); i++) {
	rb_yield(RSTRUCT_PTR(s)[i]);
	RETURN_IF_BROKEN();
    }
    return s;
}

/*
 *  call-seq:
 *     struct.each_pair {|sym, obj| block }     => struct
 *  
 *  Calls <i>block</i> once for each instance variable, passing the name
 *  (as a symbol) and the value as parameters.
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     joe.each_pair {|name, value| puts("#{name} => #{value}") }
 *     
 *  <em>produces:</em>
 *     
 *     name => Joe Smith
 *     address => 123 Maple, Anytown NC
 *     zip => 12345
 */

static VALUE
rb_struct_each_pair(VALUE s, SEL sel)
{
    VALUE members;
    long i;

    RETURN_ENUMERATOR(s, 0, 0);
    members = rb_struct_members(s);
    for (i=0; i<RSTRUCT_LEN(s); i++) {
	rb_yield_values(2, rb_ary_entry(members, i), RSTRUCT_PTR(s)[i]);
	RETURN_IF_BROKEN();
    }
    return s;
}

static VALUE
inspect_struct(VALUE s, VALUE dummy, int recur)
{
    const char *cname = rb_class2name(rb_obj_class(s));
    VALUE str, members;
    long i;

    if (recur) {
	return rb_sprintf("#<struct %s:...>", cname);
    }

    members = rb_struct_members(s);
    if (cname[0] == '#') {
	str = rb_str_new2("#<struct ");
    }
    else {
	str = rb_sprintf("#<struct %s ", cname);
    }
    for (i=0; i<RSTRUCT_LEN(s); i++) {
	VALUE slot;
	ID id;

	if (i > 0) {
	    rb_str_cat2(str, ", ");
	}
	slot = RARRAY_AT(members, i);
	id = SYM2ID(slot);
	if (rb_is_local_id(id) || rb_is_const_id(id)) {
	    rb_str_append(str, rb_id2str(id));
	}
	else {
	    rb_str_append(str, rb_inspect(slot));
	}
	rb_str_cat2(str, "=");
	rb_str_append(str, rb_inspect(RSTRUCT_PTR(s)[i]));
    }
    rb_str_cat2(str, ">");
    OBJ_INFECT(str, s);

    return str;
}

/*
 * call-seq:
 *   struct.to_s      => string
 *   struct.inspect   => string
 *
 * Describe the contents of this struct in a string.
 */

static VALUE
rb_struct_inspect(VALUE s, SEL sel)
{
    return rb_exec_recursive(inspect_struct, s, 0);
}

/*
 *  call-seq:
 *     struct.to_a     => array
 *     struct.values   => array
 *  
 *  Returns the values for this instance as an array.
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     joe.to_a[1]   #=> "123 Maple, Anytown NC"
 */

static VALUE
rb_struct_to_a(VALUE s, SEL sel)
{
    return rb_ary_new4(RSTRUCT_LEN(s), RSTRUCT_PTR(s));
}

/* :nodoc: */
static VALUE
rb_struct_init_copy(VALUE copy, SEL sel, VALUE s)
{
    if (copy == s) return copy;
    rb_check_frozen(copy);
    if (!rb_obj_is_instance_of(s, rb_obj_class(copy))) {
	rb_raise(rb_eTypeError, "wrong argument class");
    }
    if (RSTRUCT_LEN(copy) != RSTRUCT_LEN(s)) {
	rb_raise(rb_eTypeError, "struct size mismatch");
    }
    MEMCPY(RSTRUCT_PTR(copy), RSTRUCT_PTR(s), VALUE, RSTRUCT_LEN(copy));

    return copy;
}

static VALUE
rb_struct_aref_id(VALUE s, ID id)
{
    VALUE members;
    long i, len;

    members = rb_struct_members(s);
    len = RARRAY_LEN(members);
    for (i=0; i<len; i++) {
	if (SYM2ID(RARRAY_AT(members, i)) == id) {
	    return RSTRUCT_PTR(s)[i];
	}
    }
    rb_name_error(id, "no member '%s' in struct", rb_id2name(id));
    return Qnil;		/* not reached */
}

/*
 *  call-seq:
 *     struct[symbol]    => anObject
 *     struct[fixnum]    => anObject 
 *  
 *  Attribute Reference---Returns the value of the instance variable
 *  named by <i>symbol</i>, or indexed (0..length-1) by
 *  <i>fixnum</i>. Will raise <code>NameError</code> if the named
 *  variable does not exist, or <code>IndexError</code> if the index is
 *  out of range.
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     
 *     joe["name"]   #=> "Joe Smith"
 *     joe[:name]    #=> "Joe Smith"
 *     joe[0]        #=> "Joe Smith"
 */

static VALUE
rb_struct_aref_imp(VALUE s, SEL sel, VALUE idx)
{
    long i;

    if (TYPE(idx) == T_STRING || TYPE(idx) == T_SYMBOL) {
	return rb_struct_aref_id(s, rb_to_id(idx));
    }

    i = NUM2LONG(idx);
    if (i < 0) i = RSTRUCT_LEN(s) + i;
    if (i < 0)
        rb_raise(rb_eIndexError, "offset %ld too small for struct(size:%ld)",
		 i, RSTRUCT_LEN(s));
    if (RSTRUCT_LEN(s) <= i)
        rb_raise(rb_eIndexError, "offset %ld too large for struct(size:%ld)",
		 i, RSTRUCT_LEN(s));
    return RSTRUCT_PTR(s)[i];
}

VALUE
rb_struct_aref(VALUE s, VALUE idx)
{
    return rb_struct_aref_imp(s, 0, idx);
}

static VALUE
rb_struct_aset_id(VALUE s, ID id, VALUE val)
{
    VALUE members;
    long i, len;

    members = rb_struct_members(s);
    rb_struct_modify(s);
    len = RARRAY_LEN(members);
    if (RSTRUCT_LEN(s) != RARRAY_LEN(members)) {
	rb_raise(rb_eTypeError, "struct size differs (%ld required %ld given)",
		 RARRAY_LEN(members), RSTRUCT_LEN(s));
    }
    for (i=0; i<len; i++) {
	if (SYM2ID(RARRAY_AT(members, i)) == id) {
	    RSTRUCT_PTR(s)[i] = val;
	    return val;
	}
    }
    rb_name_error(id, "no member '%s' in struct", rb_id2name(id));
}

/*
 *  call-seq:
 *     struct[symbol] = obj    => obj
 *     struct[fixnum] = obj    => obj
 *  
 *  Attribute Assignment---Assigns to the instance variable named by
 *  <i>symbol</i> or <i>fixnum</i> the value <i>obj</i> and
 *  returns it. Will raise a <code>NameError</code> if the named
 *  variable does not exist, or an <code>IndexError</code> if the index
 *  is out of range.
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     
 *     joe["name"] = "Luke"
 *     joe[:zip]   = "90210"
 *     
 *     joe.name   #=> "Luke"
 *     joe.zip    #=> "90210"
 */

static VALUE
rb_struct_aset_imp(VALUE s, SEL sel, VALUE idx, VALUE val)
{
    long i;

    if (TYPE(idx) == T_STRING || TYPE(idx) == T_SYMBOL) {
	return rb_struct_aset_id(s, rb_to_id(idx), val);
    }

    i = NUM2LONG(idx);
    if (i < 0) i = RSTRUCT_LEN(s) + i;
    if (i < 0) {
        rb_raise(rb_eIndexError, "offset %ld too small for struct(size:%ld)",
		 i, RSTRUCT_LEN(s));
    }
    if (RSTRUCT_LEN(s) <= i) {
        rb_raise(rb_eIndexError, "offset %ld too large for struct(size:%ld)",
		 i, RSTRUCT_LEN(s));
    }
    rb_struct_modify(s);
    return RSTRUCT_PTR(s)[i] = val;
}

VALUE
rb_struct_aset(VALUE s, VALUE idx, VALUE val)
{
    return rb_struct_aset_imp(s, 0, idx, val);
}

static VALUE
struct_entry(VALUE s, long n)
{
    return rb_struct_aref(s, LONG2NUM(n));
}

/* 
 * call-seq:
 *   struct.values_at(selector,... )  => an_array
 *
 *   Returns an array containing the elements in
 *   _self_ corresponding to the given selector(s). The selectors
 *   may be either integer indices or ranges. 
 *   See also </code>.select<code>.
 * 
 *      a = %w{ a b c d e f }
 *      a.values_at(1, 3, 5)
 *      a.values_at(1, 3, 5, 7)
 *      a.values_at(-1, -3, -5, -7)
 *      a.values_at(1..3, 2...5)
 */

static VALUE
rb_struct_values_at(VALUE s, SEL sel, int argc, VALUE *argv)
{
    return rb_get_values_at(s, RSTRUCT_LEN(s), argc, argv, struct_entry);
}

/*
 *  call-seq:
 *     struct.select {|i| block }    => array
 *  
 *  Invokes the block passing in successive elements from
 *  <i>struct</i>, returning an array containing those elements
 *  for which the block returns a true value (equivalent to
 *  <code>Enumerable#select</code>).
 *     
 *     Lots = Struct.new(:a, :b, :c, :d, :e, :f)
 *     l = Lots.new(11, 22, 33, 44, 55, 66)
 *     l.select {|v| (v % 2).zero? }   #=> [22, 44, 66]
 */

static VALUE
rb_struct_select(VALUE s, SEL sel, int argc, VALUE *argv)
{
    VALUE result;
    long i;

    if (argc > 0) {
	rb_raise(rb_eArgError, "wrong number of arguments (%d for 0)", argc);
    }
    result = rb_ary_new();
    for (i = 0; i < RSTRUCT_LEN(s); i++) {
	VALUE v = rb_yield(RSTRUCT_PTR(s)[i]);
	RETURN_IF_BROKEN();
	if (RTEST(v)) {
	    rb_ary_push(result, RSTRUCT_PTR(s)[i]);
	}
    }

    return result;
}

/*
 *  call-seq:
 *     struct == other_struct     => true or false
 *  
 *  Equality---Returns <code>true</code> if <i>other_struct</i> is
 *  equal to this one: they must be of the same class as generated by
 *  <code>Struct::new</code>, and the values of all instance variables
 *  must be equal (according to <code>Object#==</code>).
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe   = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     joejr = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     jane  = Customer.new("Jane Doe", "456 Elm, Anytown NC", 12345)
 *     joe == joejr   #=> true
 *     joe == jane    #=> false
 */

static VALUE
rb_struct_equal(VALUE s, SEL sel, VALUE s2)
{
    long i;

    if (s == s2) return Qtrue;
    if (TYPE(s2) != T_STRUCT) return Qfalse;
    if (rb_obj_class(s) != rb_obj_class(s2)) return Qfalse;
    if (RSTRUCT_LEN(s) != RSTRUCT_LEN(s2)) {
	rb_bug("inconsistent struct"); /* should never happen */
    }

    for (i=0; i<RSTRUCT_LEN(s); i++) {
	if (!rb_equal(RSTRUCT_PTR(s)[i], RSTRUCT_PTR(s2)[i])) return Qfalse;
    }
    return Qtrue;
}

/*
 * call-seq:
 *   struct.hash   => fixnum
 *
 * Return a hash value based on this struct's contents.
 */

static VALUE
rb_struct_hash(VALUE s, SEL sel)
{
    long i, h;
    VALUE n;

    h = rb_hash(rb_obj_class(s));
    for (i = 0; i < RSTRUCT_LEN(s); i++) {
	h = (h << 1) | (h<0 ? 1 : 0);
	n = rb_hash(RSTRUCT_PTR(s)[i]);
	h ^= NUM2LONG(n);
    }
    return LONG2FIX(h);
}

/*
 * code-seq:
 *   struct.eql?(other)   => true or false
 *
 * Two structures are equal if they are the same object, or if all their
 * fields are equal (using <code>eql?</code>).
 */

static VALUE
rb_struct_eql(VALUE s, SEL sel, VALUE s2)
{
    long i;

    if (s == s2) return Qtrue;
    if (TYPE(s2) != T_STRUCT) return Qfalse;
    if (rb_obj_class(s) != rb_obj_class(s2)) return Qfalse;
    if (RSTRUCT_LEN(s) != RSTRUCT_LEN(s2)) {
	rb_bug("inconsistent struct"); /* should never happen */
    }

    for (i=0; i<RSTRUCT_LEN(s); i++) {
	if (!rb_eql(RSTRUCT_PTR(s)[i], RSTRUCT_PTR(s2)[i])) return Qfalse;
    }
    return Qtrue;
}

/*
 *  call-seq:
 *     struct.length    => fixnum
 *     struct.size      => fixnum
 *  
 *  Returns the number of instance variables.
 *     
 *     Customer = Struct.new(:name, :address, :zip)
 *     joe = Customer.new("Joe Smith", "123 Maple, Anytown NC", 12345)
 *     joe.length   #=> 3
 */

static VALUE
rb_struct_size(VALUE s, SEL sel)
{
    return LONG2FIX(RSTRUCT_LEN(s));
}

/*
 *  A <code>Struct</code> is a convenient way to bundle a number of
 *  attributes together, using accessor methods, without having to write
 *  an explicit class.
 *     
 *  The <code>Struct</code> class is a generator of specific classes,
 *  each one of which is defined to hold a set of variables and their
 *  accessors. In these examples, we'll call the generated class
 *  ``<i>Customer</i>Class,'' and we'll show an example instance of that
 *  class as ``<i>Customer</i>Inst.''
 *     
 *  In the descriptions that follow, the parameter <i>symbol</i> refers
 *  to a symbol, which is either a quoted string or a
 *  <code>Symbol</code> (such as <code>:name</code>).
 */
void
Init_Struct(void)
{
    rb_cStruct = rb_define_class("Struct", rb_cObject);
    rb_include_module(rb_cStruct, rb_mEnumerable);

    rb_undef_alloc_func(rb_cStruct);
    rb_objc_define_method(*(VALUE *)rb_cStruct, "new", rb_struct_s_def, -1);

    rb_objc_define_method(rb_cStruct, "initialize", rb_struct_initialize, -2);
    rb_objc_define_method(rb_cStruct, "initialize_copy", rb_struct_init_copy, 1);

    rb_objc_define_method(rb_cStruct, "==", rb_struct_equal, 1);
    rb_objc_define_method(rb_cStruct, "eql?", rb_struct_eql, 1);
    rb_objc_define_method(rb_cStruct, "hash", rb_struct_hash, 0);

    rb_objc_define_method(rb_cStruct, "to_s", rb_struct_inspect, 0);
    rb_objc_define_method(rb_cStruct, "inspect", rb_struct_inspect, 0);
    rb_objc_define_method(rb_cStruct, "to_a", rb_struct_to_a, 0);
    rb_objc_define_method(rb_cStruct, "values", rb_struct_to_a, 0);
    rb_objc_define_method(rb_cStruct, "size", rb_struct_size, 0);
    rb_objc_define_method(rb_cStruct, "length", rb_struct_size, 0);

    rb_objc_define_method(rb_cStruct, "each", rb_struct_each, 0);
    rb_objc_define_method(rb_cStruct, "each_pair", rb_struct_each_pair, 0);
    rb_objc_define_method(rb_cStruct, "[]", rb_struct_aref, 1);
    rb_objc_define_method(rb_cStruct, "[]=", rb_struct_aset, 2);
    rb_objc_define_method(rb_cStruct, "select", rb_struct_select, -1);
    rb_objc_define_method(rb_cStruct, "values_at", rb_struct_values_at, -1);

    rb_objc_define_method(rb_cStruct, "members", rb_struct_members_m, 0);
}
