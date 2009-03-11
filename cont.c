/**********************************************************************

  cont.c - 

  $Author: matz $
  created at: Thu May 23 09:03:43 2007

  Copyright (C) 2007 Koichi Sasada

**********************************************************************/

#include "ruby/ruby.h"

enum context_type {
    CONTINUATION_CONTEXT = 0,
    FIBER_CONTEXT = 1,
    ROOT_FIBER_CONTEXT = 2,
};

typedef struct rb_context_struct {
    VALUE self;
    VALUE value;
    VALUE *vm_stack;
    VALUE *machine_stack;
    VALUE *machine_stack_src;
#ifdef __ia64
    VALUE *machine_register_stack;
    VALUE *machine_register_stack_src;
    int machine_register_stack_size;
#endif
    rb_thread_t saved_thread;
    rb_jmpbuf_t jmpbuf;
    int machine_stack_size;
    VALUE prev;
    int alive;
    enum context_type type;
} rb_context_t;

static VALUE rb_cContinuation;
static VALUE rb_cFiber;
static VALUE rb_eFiberError;

#define GetContPtr(obj, ptr)  \
  Data_Get_Struct(obj, rb_context_t, ptr)

NOINLINE(static VALUE cont_capture(volatile int *stat));

#if !WITH_OBJC
void rb_thread_mark(rb_thread_t *th);

static void
cont_mark(void *ptr)
{
    RUBY_MARK_ENTER("cont");
    if (ptr) {
	rb_context_t *cont = ptr;
	rb_gc_mark(cont->value);
	rb_gc_mark(cont->prev);
	rb_thread_mark(&cont->saved_thread);

	if (cont->vm_stack) {
	    rb_gc_mark_locations(cont->vm_stack,
				 cont->vm_stack + cont->saved_thread.stack_size);
	}

	if (cont->machine_stack) {
	    rb_gc_mark_locations(cont->machine_stack,
				 cont->machine_stack + cont->machine_stack_size);
	}
#ifdef __ia64
	if (cont->machine_register_stack) {
	    rb_gc_mark_locations(cont->machine_register_stack,
				 cont->machine_register_stack + cont->machine_register_stack_size);
	}
#endif
    }
    RUBY_MARK_LEAVE("cont");
}
#else /* !WITH_OBJC */
# define cont_mark (NULL)
#endif

static void
cont_free(void *ptr)
{
    RUBY_FREE_ENTER("cont");
    if (ptr) {
	rb_context_t *cont = ptr;
	RUBY_FREE_UNLESS_NULL(cont->saved_thread.stack);
	RUBY_FREE_UNLESS_NULL(cont->machine_stack);
#ifdef __ia64
	RUBY_FREE_UNLESS_NULL(cont->machine_register_stack);
#endif
	RUBY_FREE_UNLESS_NULL(cont->vm_stack);

	if (cont->type == FIBER_CONTEXT) {
	    st_free_table(cont->saved_thread.local_storage);
	}

	ruby_xfree(ptr);
    }
    RUBY_FREE_LEAVE("cont");
}

static void
cont_save_machine_stack(rb_thread_t *th, rb_context_t *cont)
{
#if !WITH_OBJC
    int size;
    rb_thread_t *sth = &cont->saved_thread;

    SET_MACHINE_STACK_END(&th->machine_stack_end);
#ifdef __ia64
    th->machine_register_stack_end = rb_ia64_bsp();
#endif

    if (th->machine_stack_start > th->machine_stack_end) {
	size = cont->machine_stack_size = th->machine_stack_start - th->machine_stack_end;
	cont->machine_stack_src = th->machine_stack_end;
    }
    else {
	size = cont->machine_stack_size = th->machine_stack_end - th->machine_stack_start;
	cont->machine_stack_src = th->machine_stack_start;
    }

    if (cont->machine_stack) {
	REALLOC_N(cont->machine_stack, VALUE, size);
    }
    else {
	GC_WB(&cont->machine_stack, ALLOC_N(VALUE, size));
    }

    FLUSH_REGISTER_WINDOWS;
    MEMCPY(cont->machine_stack, cont->machine_stack_src, VALUE, size);

#ifdef __ia64
    rb_ia64_flushrs();
    size = cont->machine_register_stack_size = th->machine_register_stack_end - th->machine_register_stack_start;
    cont->machine_register_stack_src = th->machine_register_stack_start;
    if (cont->machine_register_stack) {
	REALLOC_N(cont->machine_register_stack, VALUE, size);
    }
    else {
	GC_WB(&cont->machine_register_stack, ALLOC_N(VALUE, size));
    }

    MEMCPY(cont->machine_register_stack, cont->machine_register_stack_src, VALUE, size);
#endif

    sth->machine_stack_start = sth->machine_stack_end = 0;
#ifdef __ia64
    sth->machine_register_stack_start = sth->machine_register_stack_end = 0;
#endif
#endif
}

static rb_context_t *
cont_new(VALUE klass)
{
    rb_context_t *cont;
    volatile VALUE contval;
    rb_thread_t *th = GET_THREAD();

    contval = Data_Make_Struct(klass, rb_context_t,
			       cont_mark, cont_free, cont);

    cont->self = contval;
    cont->alive = Qtrue;

    /* save thread context */
    cont->saved_thread = *th;

    return cont;
}

void vm_stack_to_heap(rb_thread_t *th);

static VALUE
cont_capture(volatile int *stat)
{
    rb_context_t *cont;
    rb_thread_t *th = GET_THREAD(), *sth;
    volatile VALUE contval;

    vm_stack_to_heap(th);
    cont = cont_new(rb_cContinuation);
    contval = cont->self;
    sth = &cont->saved_thread;

    GC_WB(&cont->vm_stack, ALLOC_N(VALUE, th->stack_size));
    MEMCPY(cont->vm_stack, th->stack, VALUE, th->stack_size);
    sth->stack = 0;

    cont_save_machine_stack(th, cont);

    if (ruby_setjmp(cont->jmpbuf)) {
	VALUE value;

	value = cont->value;
	cont->value = Qnil;
	*stat = 1;
	return value;
    }
    else {
	*stat = 0;
	return cont->self;
    }
}

NORETURN(static void cont_restore_1(rb_context_t *));

static void
cont_restore_1(rb_context_t *cont)
{
    rb_thread_t *th = GET_THREAD(), *sth = &cont->saved_thread;

    /* restore thread context */
    if (cont->type == CONTINUATION_CONTEXT) {
	/* continuation */
	VALUE fib;

	th->fiber = sth->fiber;
	fib = th->fiber ? th->fiber : th->root_fiber;

	if (fib) {
	    rb_context_t *fcont;
	    GetContPtr(fib, fcont);
	    th->stack_size = fcont->saved_thread.stack_size;
	    th->stack = fcont->saved_thread.stack;
	}
	MEMCPY(th->stack, cont->vm_stack, VALUE, sth->stack_size);
    }
    else {
	/* fiber */
	th->stack = sth->stack;
	th->stack_size = sth->stack_size;
	th->local_storage = sth->local_storage;
	th->fiber = cont->self;
    }

    th->cfp = sth->cfp;
    th->safe_level = sth->safe_level;
    th->raised_flag = sth->raised_flag;
    th->state = sth->state;
    th->status = sth->status;
    th->tag = sth->tag;
    th->trap_tag = sth->trap_tag;
    th->errinfo = sth->errinfo;
    th->first_proc = sth->first_proc;

    /* restore machine stack */
#ifdef _M_AMD64
    {
	/* workaround for x64 SEH */
	jmp_buf buf;
	setjmp(buf);
	((_JUMP_BUFFER*)(&cont->jmpbuf))->Frame =
	    ((_JUMP_BUFFER*)(&buf))->Frame;
    }
#endif
    if (cont->machine_stack_src) {
	FLUSH_REGISTER_WINDOWS;
	MEMCPY(cont->machine_stack_src, cont->machine_stack,
	       VALUE, cont->machine_stack_size);
    }

#ifdef __ia64
    if (cont->machine_register_stack_src) {
	MEMCPY(cont->machine_register_stack_src, cont->machine_register_stack,
	       VALUE, cont->machine_register_stack_size);
    }
#endif

    ruby_longjmp(cont->jmpbuf, 1);
}

NORETURN(NOINLINE(static void cont_restore_0(rb_context_t *, VALUE *)));

#ifdef __ia64
#define C(a) rse_##a##0, rse_##a##1, rse_##a##2, rse_##a##3, rse_##a##4
#define E(a) rse_##a##0= rse_##a##1= rse_##a##2= rse_##a##3= rse_##a##4
static volatile int C(a), C(b), C(c), C(d), C(e);
static volatile int C(f), C(g), C(h), C(i), C(j);
static volatile int C(k), C(l), C(m), C(n), C(o);
static volatile int C(p), C(q), C(r), C(s), C(t);
int rb_dummy_false = 0;
NORETURN(NOINLINE(static void register_stack_extend(rb_context_t *, VALUE *)));
static void
register_stack_extend(rb_context_t *cont, VALUE *curr_bsp)
{
    if (rb_dummy_false) {
        /* use registers as much as possible */
        E(a) = E(b) = E(c) = E(d) = E(e) =
        E(f) = E(g) = E(h) = E(i) = E(j) =
        E(k) = E(l) = E(m) = E(n) = E(o) =
        E(p) = E(q) = E(r) = E(s) = E(t) = 0;
        E(a) = E(b) = E(c) = E(d) = E(e) =
        E(f) = E(g) = E(h) = E(i) = E(j) =
        E(k) = E(l) = E(m) = E(n) = E(o) =
        E(p) = E(q) = E(r) = E(s) = E(t) = 0;
    }
    if (curr_bsp < cont->machine_register_stack_src+cont->machine_register_stack_size) {
        register_stack_extend(cont, (VALUE*)rb_ia64_bsp());
    }
    cont_restore_1(cont);
}
#undef C
#undef E
#endif

static void
cont_restore_0(rb_context_t *cont, VALUE *addr_in_prev_frame)
{
    if (cont->machine_stack_src) {
#define STACK_PAD_SIZE 1024
	VALUE space[STACK_PAD_SIZE];

#if STACK_GROW_DIRECTION < 0 /* downward */
	if (addr_in_prev_frame > cont->machine_stack_src) {
	    cont_restore_0(cont, &space[0]);
	}
#elif STACK_GROW_DIRECTION > 0 /* upward */
	if (addr_in_prev_frame < cont->machine_stack_src + cont->machine_stack_size) {
	    cont_restore_0(cont, &space[STACK_PAD_SIZE-1]);
	}
#else
	if (addr_in_prev_frame > &space[0]) {
	    /* Stack grows downward */
	    if (addr_in_prev_frame > cont->machine_stack_src) {
		cont_restore_0(cont, &space[0]);
	    }
	}
	else {
	    /* Stack grows upward */
	    if (addr_in_prev_frame < cont->machine_stack_src + cont->machine_stack_size) {
		cont_restore_0(cont, &space[STACK_PAD_SIZE-1]);
	    }
	}
#endif
    }
#ifdef __ia64
    register_stack_extend(cont, (VALUE*)rb_ia64_bsp());
#else
    cont_restore_1(cont);
#endif
}

/*
 *  Document-class: Continuation
 *
 *  Continuation objects are generated by
 *  <code>Kernel#callcc</code>. They hold a return address and execution
 *  context, allowing a nonlocal return to the end of the
 *  <code>callcc</code> block from anywhere within a program.
 *  Continuations are somewhat analogous to a structured version of C's
 *  <code>setjmp/longjmp</code> (although they contain more state, so
 *  you might consider them closer to threads).
 *     
 *  For instance:
 *     
 *     arr = [ "Freddie", "Herbie", "Ron", "Max", "Ringo" ]
 *     callcc{|$cc|}
 *     puts(message = arr.shift)
 *     $cc.call unless message =~ /Max/
 *     
 *  <em>produces:</em>
 *     
 *     Freddie
 *     Herbie
 *     Ron
 *     Max
 *     
 *  This (somewhat contrived) example allows the inner loop to abandon
 *  processing early:
 *     
 *     callcc {|cont|
 *       for i in 0..4
 *         print "\n#{i}: "
 *         for j in i*5...(i+1)*5
 *           cont.call() if j == 17
 *           printf "%3d", j
 *         end
 *       end
 *     }
 *     print "\n"
 *     
 *  <em>produces:</em>
 *     
 *     0:   0  1  2  3  4
 *     1:   5  6  7  8  9
 *     2:  10 11 12 13 14
 *     3:  15 16
 */

/*
 *  call-seq:
 *     callcc {|cont| block }   =>  obj
 *  
 *  Generates a <code>Continuation</code> object, which it passes to the
 *  associated block. Performing a <em>cont</em><code>.call</code> will
 *  cause the <code>callcc</code> to return (as will falling through the
 *  end of the block). The value returned by the <code>callcc</code> is
 *  the value of the block, or the value passed to
 *  <em>cont</em><code>.call</code>. See class <code>Continuation</code>
 *  for more details. Also see <code>Kernel::throw</code> for
 *  an alternative mechanism for unwinding a call stack.
 */

static VALUE
rb_callcc(VALUE self)
{
    volatile int called;
    volatile VALUE val = cont_capture(&called);

    if (called) {
	return val;
    }
    else {
	return rb_yield(val);
    }
}

static VALUE
make_passing_arg(int argc, VALUE *argv)
{
    switch(argc) {
      case 0:
	return Qnil;
      case 1:
	return argv[0];
      default:
	return rb_ary_new4(argc, argv);
    }
}

/*
 *  call-seq:
 *     cont.call(args, ...)
 *     cont[args, ...]
 *  
 *  Invokes the continuation. The program continues from the end of the
 *  <code>callcc</code> block. If no arguments are given, the original
 *  <code>callcc</code> returns <code>nil</code>. If one argument is
 *  given, <code>callcc</code> returns it. Otherwise, an array
 *  containing <i>args</i> is returned.
 *     
 *     callcc {|cont|  cont.call }           #=> nil
 *     callcc {|cont|  cont.call 1 }         #=> 1
 *     callcc {|cont|  cont.call 1, 2, 3 }   #=> [1, 2, 3]
 */

static VALUE
rb_cont_call(int argc, VALUE *argv, VALUE contval)
{
    rb_context_t *cont;
    rb_thread_t *th = GET_THREAD();
    GetContPtr(contval, cont);

    if (cont->saved_thread.self != th->self) {
	rb_raise(rb_eRuntimeError, "continuation called across threads");
    }
    if (cont->saved_thread.trap_tag != th->trap_tag) {
	rb_raise(rb_eRuntimeError, "continuation called across trap");
    }
    if (cont->saved_thread.fiber) {
	rb_context_t *fcont;
	GetContPtr(cont->saved_thread.fiber, fcont);

	if (th->fiber != cont->saved_thread.fiber) {
	    rb_raise(rb_eRuntimeError, "continuation called across fiber");
	}
	
	if (!fcont->alive) {
	    rb_raise(rb_eRuntimeError, "continuation called dead fiber");
	}
    }

    cont->value = make_passing_arg(argc, argv);

    cont_restore_0(cont, &contval);
    return Qnil; /* unreachable */
}

/*********/
/* fiber */
/*********/

#define FIBER_VM_STACK_SIZE (4 * 1024)

static rb_context_t *
fiber_alloc(VALUE klass)
{
    rb_context_t *cont = cont_new(klass);

    cont->type = FIBER_CONTEXT;
    cont->prev = Qnil;

    return cont;
}

static VALUE
fiber_new(VALUE klass, VALUE proc)
{
    rb_context_t *cont = fiber_alloc(klass);
    VALUE contval = cont->self;
    rb_thread_t *th = &cont->saved_thread;

    /* initialize */
    cont->vm_stack = 0;

    th->stack = 0;
    th->stack_size = FIBER_VM_STACK_SIZE;
    GC_WB(&th->stack, ALLOC_N(VALUE, th->stack_size));

    th->cfp = (void *)(th->stack + th->stack_size);
    th->cfp--;
    th->cfp->pc = 0;
    th->cfp->sp = th->stack + 1;
    th->cfp->bp = 0;
    th->cfp->lfp = th->stack;
    *th->cfp->lfp = 0;
    th->cfp->dfp = th->stack;
    th->cfp->self = Qnil;
    th->cfp->flag = 0;
    th->cfp->iseq = 0;
    th->cfp->proc = 0;
    th->cfp->block_iseq = 0;
    th->tag = 0;
    GC_WB(&th->local_storage, st_init_numtable());

    GC_WB(&th->first_proc, proc);

    MEMCPY(&cont->jmpbuf, &th->root_jmpbuf, rb_jmpbuf_t, 1);

    return contval;
}

VALUE
rb_fiber_new(VALUE (*func)(ANYARGS), VALUE obj)
{
    return fiber_new(rb_cFiber, rb_proc_new(func, obj));
}

static VALUE
rb_fiber_s_new(VALUE self)
{
    return fiber_new(self, rb_block_proc());
}

static VALUE
return_fiber(void)
{
    rb_context_t *cont;
    VALUE curr = rb_fiber_current();
    GetContPtr(curr, cont);

    if (cont->prev == Qnil) {
	rb_thread_t *th = GET_THREAD();

	if (th->root_fiber != curr) {
	    return th->root_fiber;
	}
	else {
	    rb_raise(rb_eFiberError, "can't yield from root fiber");
	}
    }
    else {
	VALUE prev = cont->prev;
	cont->prev = Qnil;
	return prev;
    }
}

VALUE rb_fiber_transfer(VALUE fib, int argc, VALUE *argv);

static void
rb_fiber_terminate(rb_context_t *cont)
{
    VALUE value = cont->value;
    cont->alive = Qfalse;
    rb_fiber_transfer(return_fiber(), 1, &value);
}

void
rb_fiber_start(void)
{
    rb_thread_t *th = GET_THREAD();
    rb_context_t *cont;
//    rb_proc_t *proc;
//    VALUE args;
    int state;

    GetContPtr(th->fiber, cont);
    TH_PUSH_TAG(th);
    if ((state = EXEC_TAG()) == 0) {
#if 0 // TODO
	GetProcPtr(cont->saved_thread.first_proc, proc);
	args = cont->value;
	cont->value = Qnil;
	th->errinfo = Qnil;
	GC_WB(&th->local_lfp, proc->block.lfp);
	th->local_svar = Qnil;

	cont->value = vm_invoke_proc(th, proc, proc->block.self, 1, &args, 0);
#endif
    }
    TH_POP_TAG();

    if (state) {
	if (TAG_RAISE) {
	    th->thrown_errinfo = th->errinfo;
	}
	else {
	    th->thrown_errinfo =
	      vm_make_jump_tag_but_local_jump(state, th->errinfo);
	}
	RUBY_VM_SET_INTERRUPT(th);
    }

    rb_fiber_terminate(cont);
    rb_bug("rb_fiber_start: unreachable");
}

VALUE
rb_fiber_current()
{
    rb_thread_t *th = GET_THREAD();
    if (th->fiber == 0) {
	/* save root */
	rb_context_t *cont = fiber_alloc(rb_cFiber);
	cont->type = ROOT_FIBER_CONTEXT;
	th->root_fiber = th->fiber = cont->self;
    }
    return th->fiber;
}

static VALUE
fiber_store(rb_context_t *next_cont)
{
    rb_thread_t *th = GET_THREAD();
    rb_context_t *cont;

    if (th->fiber) {
	GetContPtr(th->fiber, cont);
	cont->saved_thread = *th;
    }
    else {
	/* create current fiber */
	cont = fiber_alloc(rb_cFiber); /* no need to allocate vm stack */
	cont->type = ROOT_FIBER_CONTEXT;
	th->root_fiber = th->fiber = cont->self;
    }

    cont_save_machine_stack(th, cont);

    if (ruby_setjmp(cont->jmpbuf)) {
	/* restored */
	GetContPtr(th->fiber, cont);
	return cont->value;
    }
    else {
	return Qundef;
    }
}

static inline VALUE
fiber_switch(VALUE fib, int argc, VALUE *argv, int is_resume)
{
    VALUE value;
    rb_context_t *cont;
    rb_thread_t *th = GET_THREAD();

    GetContPtr(fib, cont);

    if (cont->saved_thread.self != th->self) {
	rb_raise(rb_eFiberError, "fiber called across threads");
    }
    else if (cont->saved_thread.trap_tag != th->trap_tag) {
	rb_raise(rb_eFiberError, "fiber called across trap");
    }
    else if (!cont->alive) {
	rb_raise(rb_eFiberError, "dead fiber called");
    }

    if (is_resume) {
	cont->prev = rb_fiber_current();
    }

    cont->value = make_passing_arg(argc, argv);

    if ((value = fiber_store(cont)) == Qundef) {
	cont_restore_0(cont, &value);
	rb_bug("rb_fiber_resume: unreachable");
    }

    RUBY_VM_CHECK_INTS();

    return value;
}

VALUE
rb_fiber_transfer(VALUE fib, int argc, VALUE *argv)
{
    return fiber_switch(fib, argc, argv, 0);
}

VALUE
rb_fiber_resume(VALUE fib, int argc, VALUE *argv)
{
    rb_context_t *cont;
    GetContPtr(fib, cont);

    if (cont->prev != Qnil) {
	rb_raise(rb_eFiberError, "double resume");
    }

    return fiber_switch(fib, argc, argv, 1);
}

VALUE
rb_fiber_yield(int argc, VALUE *argv)
{
    return rb_fiber_transfer(return_fiber(), argc, argv);
}

VALUE
rb_fiber_alive_p(VALUE fib)
{
    rb_context_t *cont;
    GetContPtr(fib, cont);
    return cont->alive;
}

static VALUE
rb_fiber_m_resume(int argc, VALUE *argv, VALUE fib)
{
    return rb_fiber_resume(fib, argc, argv);
}

static VALUE
rb_fiber_m_transfer(int argc, VALUE *argv, VALUE fib)
{
    return rb_fiber_transfer(fib, argc, argv);
}

static VALUE
rb_fiber_s_yield(int argc, VALUE *argv, VALUE klass)
{
    return rb_fiber_yield(argc, argv);
}

static VALUE
rb_fiber_s_current(VALUE klass)
{
    return rb_fiber_current();
}

void
Init_Cont(void)
{
    rb_cFiber = rb_define_class("Fiber", rb_cObject);
    rb_undef_alloc_func(rb_cFiber);
    rb_eFiberError = rb_define_class("FiberError", rb_eStandardError);
    rb_define_singleton_method(rb_cFiber, "new", rb_fiber_s_new, 0);
    rb_define_singleton_method(rb_cFiber, "yield", rb_fiber_s_yield, -1);
    rb_define_method(rb_cFiber, "resume", rb_fiber_m_resume, -1);
}

void
Init_Continuation_body(void)
{
    rb_cContinuation = rb_define_class("Continuation", rb_cObject);
    rb_undef_alloc_func(rb_cContinuation);
    rb_undef_method(CLASS_OF(rb_cContinuation), "new");
    rb_define_method(rb_cContinuation, "call", rb_cont_call, -1);
    rb_define_method(rb_cContinuation, "[]", rb_cont_call, -1);
    rb_define_global_function("callcc", rb_callcc, 0);
}

void
Init_Fiber_as_Coroutine(void)
{
    rb_define_method(rb_cFiber, "transfer", rb_fiber_m_transfer, -1);
    rb_define_method(rb_cFiber, "alive?", rb_fiber_alive_p, 0);
    rb_define_singleton_method(rb_cFiber, "current", rb_fiber_s_current, 0);
}
