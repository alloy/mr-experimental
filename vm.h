/*
 * MacRuby VM.
 *
 * This file is covered by the Ruby license. See COPYING for more details.
 * 
 * Copyright (C) 2008-2009, Apple Inc. All rights reserved.
 */

#ifndef __VM_H_
#define __VM_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
    short min;		// min number of args that we accept
    short max;		// max number of args that we accept (-1 if rest)
    short left_req;	// number of args required on the left side
    short real;		// number of args of the low level function
} rb_vm_arity_t;

typedef struct rb_vm_local {
    ID name;
    VALUE *value;
    struct rb_vm_local *next;
} rb_vm_local_t;

#define VM_BLOCK_PROC	0x0001	// block is a Proc object
#define VM_BLOCK_LAMBDA 0x0002	// block is a lambda
#define VM_BLOCK_ACTIVE 0x0004	// block is active (being executed)
#define VM_BLOCK_METHOD 0x0008	// block is created from Method

typedef struct rb_vm_block {
    VALUE self;
    NODE *node;
    rb_vm_arity_t arity;
    IMP imp;
    int flags;
    rb_vm_local_t *locals;
    struct rb_vm_var_uses **parent_var_uses;
    struct rb_vm_block *parent_block;
    int dvars_size;
    VALUE *dvars[1];
} rb_vm_block_t;

typedef struct {
    VALUE self;
    rb_vm_local_t *locals;
} rb_vm_binding_t;

#define VM_METHOD_EMPTY	1000

typedef struct {
    rb_vm_arity_t arity;
    SEL sel;
    IMP objc_imp;
    IMP ruby_imp;
    int flags;
} rb_vm_method_node_t;

typedef struct {
    VALUE oclass;
    VALUE rclass;
    VALUE recv;
    SEL sel;
    int arity;
    rb_vm_method_node_t *node;	// NULL in case the method is ObjC
    void *cache;
} rb_vm_method_t;

typedef struct rb_vm_outer {
    Class klass;
    struct rb_vm_outer *outer;
} rb_vm_outer_t;

typedef struct {
    jmp_buf buf;
    VALUE throw_value;
    int nested;
} rb_vm_catch_t;

static inline rb_vm_arity_t
rb_vm_arity(int argc)
{
    rb_vm_arity_t arity;
    arity.left_req = arity.min = arity.max = arity.real = argc;
    return arity;
}

static inline rb_vm_arity_t
rb_vm_node_arity(NODE *node)
{
    const int type = nd_type(node);
    rb_vm_arity_t arity;

    if (type == NODE_SCOPE) {
	NODE *n = node->nd_args;
	short opt_args = 0, req_args = 0;
	bool has_rest = false;
	if (n == NULL) {
	    arity.left_req = 0;
	}
	else {
	    req_args = n->nd_frml;
	    arity.left_req = req_args;
	    NODE *n_opt = n->nd_opt;
	    if (n_opt != NULL) {
		NODE *ni = n_opt;
		while (ni != NULL) {
		    opt_args++;
		    ni = ni->nd_next;
		}
	    }
	    if (n->nd_next != NULL) {
		NODE *rest_node = n->nd_next;
		if (rest_node->nd_rest) {
		    has_rest = true;
		}
		if (rest_node->nd_next) {
		    req_args += rest_node->nd_next->nd_frml;
		}
	    }
	}
	arity.min = req_args;
	if (has_rest) {
	    arity.max = -1;
	    arity.real = req_args + opt_args + 1;
	}
	else {
	    arity.max = arity.real = req_args + opt_args;
	}
	return arity;
    }

    if (type == NODE_FBODY) {
	assert(node->nd_body != NULL);
	assert(node->nd_body->nd_body != NULL);
	int argc = node->nd_body->nd_body->nd_argc;
	if (argc >= 0) {
	    arity.left_req = arity.real = arity.min = arity.max = argc;
	}
	else {
	    arity.left_req = arity.min = 0;
	    arity.max = -1;
	    if (argc == -1) {
		arity.real = 2;
	    }
	    else if (argc == -2) {
		arity.real = 1;
	    }
	    else {
		printf("invalid FBODY arity: %d\n", argc);
		abort();
	    }
	}
	return arity; 
    }

    printf("invalid node %p type %d\n", node, type);
    abort();
}

static inline int
rb_vm_node_flags(NODE *node)
{
    int flags = nd_type(node);
    if (node->nd_body == NULL) {
	flags |= VM_METHOD_EMPTY;
    }
    return flags;
}

static inline int
rb_vm_method_node_type(rb_vm_method_node_t *node)
{
    return node->flags & VM_METHOD_EMPTY
	? node->flags ^ VM_METHOD_EMPTY : node->flags; 
}

static inline bool
rb_vm_method_node_empty(rb_vm_method_node_t *node)
{
    return node->flags & VM_METHOD_EMPTY;
}

static inline int
rb_vm_method_node_noex(rb_vm_method_node_t *node)
{
    // TODO
    return 0;
}

VALUE rb_vm_run(const char *fname, NODE *node, rb_vm_binding_t *binding,
		bool try_interpreter);
VALUE rb_vm_run_under(VALUE klass, VALUE self, const char *fname, NODE *node,
		      rb_vm_binding_t *binding, bool try_interpreter);
void rb_vm_aot_compile(NODE *node);

bool rb_vm_running(void);
void rb_vm_set_running(bool flag);
bool rb_vm_parse_in_eval(void);
void rb_vm_set_parse_in_eval(bool flag);
VALUE rb_vm_load_path(void);
VALUE rb_vm_loaded_features(void);
int rb_vm_safe_level(void);
void rb_vm_set_safe_level(int level);
VALUE rb_vm_top_self(void);
void rb_vm_const_is_defined(ID path);
VALUE rb_vm_resolve_const_value(VALUE val, VALUE klass, ID name);
bool rb_vm_lookup_method(Class klass, SEL sel, IMP *pimp,
	rb_vm_method_node_t **pnode);
bool rb_vm_lookup_method2(Class klass, ID mid, SEL *psel, IMP *pimp,
	rb_vm_method_node_t **pnode);
rb_vm_method_node_t *rb_vm_get_method_node(IMP imp);
void rb_vm_define_method(Class klass, SEL sel, IMP imp, NODE *node,
	bool direct);
void rb_vm_define_method2(Class klass, SEL sel, rb_vm_method_node_t *node,
	bool direct);
void rb_vm_define_attr(Class klass, const char *name, bool read, bool write,
	int noex);
void rb_vm_alias(VALUE klass, ID name, ID def);
void rb_vm_copy_methods(Class from_class, Class to_class);
VALUE rb_vm_call(VALUE self, SEL sel, int argc, const VALUE *args, bool super);
VALUE rb_vm_call_with_cache(void *cache, VALUE self, SEL sel, int argc,
	const VALUE *argv);
VALUE rb_vm_call_with_cache2(void *cache, rb_vm_block_t *block, VALUE self,
	VALUE klass, SEL sel, int argc, const VALUE *argv);
void *rb_vm_get_call_cache(SEL sel);
VALUE rb_vm_yield(int argc, const VALUE *argv);
VALUE rb_vm_yield_under(VALUE klass, VALUE self, int argc, const VALUE *argv);
bool rb_vm_respond_to(VALUE obj, SEL sel, bool priv);
VALUE rb_vm_method_missing(VALUE obj, int argc, const VALUE *argv);
void rb_vm_push_methods(VALUE ary, VALUE mod, bool include_objc_methods,
	int (*filter) (VALUE, ID, VALUE));
int rb_vm_find_class_ivar_slot(VALUE klass, ID name);
void rb_vm_set_outer(VALUE klass, VALUE under);
VALUE rb_vm_catch(VALUE tag);
VALUE rb_vm_throw(VALUE tag, VALUE value);

static inline void
rb_vm_regrow_robject_slots(struct RObject *obj, unsigned int new_num_slot)
{
    unsigned int i;
    VALUE *new_slots = (VALUE *)xmalloc(sizeof(VALUE) * (new_num_slot + 1));
    for (i = 0; i <= obj->num_slots; i++) {
	GC_WB(&new_slots[i], obj->slots[i]);
    }
    GC_WB(&obj->slots, new_slots);
    for (i = obj->num_slots + 1; i < new_num_slot; i++) {
	obj->slots[i] = Qundef;
    }
    obj->num_slots = new_num_slot;
}

static inline VALUE
rb_vm_get_ivar_from_slot(VALUE obj, int slot) 
{
    struct RObject *robj = (struct RObject *)obj;
    assert(slot >= 0);
    if (robj->num_slots < (unsigned int)slot) {
	return Qnil;
    }
    return robj->slots[slot];
}

static inline void
rb_vm_set_ivar_from_slot(VALUE obj, VALUE val, int slot) 
{
    struct RObject *robj = (struct RObject *)obj;
    assert(slot >= 0);
    if (robj->num_slots < (unsigned int)slot) {
	rb_vm_regrow_robject_slots(robj, (unsigned int)slot);
    }
    GC_WB(&robj->slots[slot], val);
}

rb_vm_method_t *rb_vm_get_method(VALUE klass, VALUE obj, ID mid, int scope);
rb_vm_block_t *rb_vm_create_block_from_method(rb_vm_method_t *method);

static inline rb_vm_block_t *
rb_proc_get_block(VALUE proc)
{
   return (rb_vm_block_t *)DATA_PTR(proc);
}

void rb_vm_add_var_use(rb_vm_block_t *proc);
rb_vm_block_t *rb_vm_prepare_block(void *llvm_function, NODE *node, VALUE self,
       struct rb_vm_var_uses **parent_lvar_uses,
       rb_vm_block_t *parent_block,
       int dvars_size, ...);
rb_vm_block_t *rb_vm_current_block(void);
rb_vm_block_t *rb_vm_first_block(void);
bool rb_vm_block_saved(void);
VALUE rb_vm_block_eval(rb_vm_block_t *block, int argc, const VALUE *argv);

rb_vm_binding_t *rb_vm_current_binding(void);
void rb_vm_add_binding(rb_vm_binding_t *binding);
void rb_vm_pop_binding();

static inline VALUE
rb_robject_allocate_instance(VALUE klass)
{
    struct RObject *obj;
    int num_slots = 10;

    obj = (struct RObject *)xmalloc(sizeof(struct RObject));
    GC_WB(&obj->slots, xmalloc(num_slots * sizeof(VALUE)));

    OBJSETUP(obj, klass, T_OBJECT);

    ROBJECT(obj)->tbl = NULL;
    ROBJECT(obj)->num_slots = num_slots;

    int i;
    for (i = 0; i < num_slots; i++) {
	ROBJECT(obj)->slots[i] = Qundef;
    }

    return (VALUE)obj;
}

void rb_vm_raise(VALUE exception);
void rb_vm_raise_current_exception(void);
VALUE rb_vm_current_exception(void);
void rb_vm_set_current_exception(VALUE exception);
VALUE rb_vm_backtrace(int level);

VALUE rb_vm_pop_broken_value(void);
#define RETURN_IF_BROKEN() \
    do { \
	VALUE __v = rb_vm_pop_broken_value(); \
	if (__v != Qundef) { \
	    return __v; \
	} \
    } \
    while (0)

void rb_vm_finalize(void);

void rb_vm_load_bridge_support(const char *path, const char *framework_path,
	int options);

VALUE rb_iseq_compile(VALUE src, VALUE file, VALUE line);
VALUE rb_iseq_eval(VALUE iseq);
VALUE rb_iseq_new(NODE *node, VALUE filename);

#if 0 // TODO
#if ENABLE_DEBUG_LOGGING 
# include <libgen.h>
extern bool ruby_dlog_enabled;
extern FILE *ruby_dlog_file;
# define DLOG(mod, fmt, args...)                                          \
    if (UNLIKELY(ruby_dlog_enabled)) {                                    \
        fprintf(ruby_dlog_file, "%s:%d %s ",                              \
                basename((char *)rb_sourcefile()), rb_sourceline(), mod); \
        fprintf(ruby_dlog_file, fmt, ##args);                             \
        fprintf(ruby_dlog_file, "\n");                                    \
    }
# endif
#endif
#define DLOG(mod, fmt, args...)

#if defined(__cplusplus)
}

#include "bridgesupport.h"

typedef struct {
    Function *func;
    NODE *node;
} rb_vm_method_source_t;

typedef VALUE rb_vm_objc_stub_t(IMP imp, id self, SEL sel, int argc,
				const VALUE *argv);

typedef VALUE rb_vm_c_stub_t(IMP imp, int argc, const VALUE *argv);

struct mcache {
#define MCACHE_RCALL 0x1 // Ruby call
#define MCACHE_OCALL 0x2 // Objective-C call
#define MCACHE_FCALL 0x4 // C call
    uint8_t flag;
    union {
	struct {
	    Class klass;
	    rb_vm_method_node_t *node;
	} rcall;
	struct {
	    Class klass;
	    IMP imp;
	    bs_element_method_t *bs_method;	
	    rb_vm_objc_stub_t *stub;
	} ocall;
	struct {
	    IMP imp;
	    bs_element_function_t *bs_function;
	    rb_vm_c_stub_t *stub;
	} fcall;
    } as;
#define rcache cache->as.rcall
#define ocache cache->as.ocall
#define fcache cache->as.fcall
};

struct ccache {
    VALUE outer;
    VALUE val;
};

class RoxorCompiler;
class RoxorJITManager;

class RoxorVM {
    private:
	ExistingModuleProvider *emp;
	RoxorJITManager *jmm;
	ExecutionEngine *ee;
	ExecutionEngine *iee;
	FunctionPassManager *fpm;
	bool running;

	std::map<IMP, rb_vm_method_node_t *> ruby_imps;
	std::map<SEL, struct mcache *> mcache;
	std::map<ID, struct ccache *> ccache;
	std::map<Class, std::map<ID, int> *> ivar_slots;
	std::map<SEL, GlobalVariable *> redefined_ops_gvars;
	std::map<Class, struct rb_vm_outer *> outers;
	std::map<std::string, void *> c_stubs, objc_stubs,
	    to_rval_convertors, to_ocval_convertors;

	std::vector<rb_vm_block_t *> current_blocks;
	std::vector<VALUE> current_exceptions;

    public:
	static RoxorVM *current;

	Class current_class;
	VALUE current_top_object;
	VALUE loaded_features;
	VALUE load_path;
	VALUE backref;
	VALUE broken_with;
	VALUE last_status;
	VALUE errinfo;
	int safe_level;
	std::vector<rb_vm_binding_t *> bindings;
	std::map<NODE *, rb_vm_block_t *> blocks;
	std::map<double, struct rb_float_cache *> float_cache;
	unsigned char method_missing_reason;
	bool parse_in_eval;

	std::string debug_blocks(void);

	bool is_block_current(rb_vm_block_t *b) {
	    return b == NULL
		? false
		: current_blocks.empty()
		? false
		: current_blocks.back() == b;
	}

	void add_current_block(rb_vm_block_t *b) {
	    current_blocks.push_back(b);
	}

	void pop_current_block(void) {
	    assert(!current_blocks.empty());
	    current_blocks.pop_back();
	}

	rb_vm_block_t *current_block(void) {
	    return current_blocks.empty() ? NULL : current_blocks.back();
	}

	rb_vm_block_t *previous_block(void) {
	    if (current_blocks.size() > 1) {
		return current_blocks[current_blocks.size() - 2];
	    }
	    return NULL;
	}

	rb_vm_block_t *first_block(void) {
	    rb_vm_block_t *b = current_block();
	    if (b == NULL) {
		b = previous_block();
	    }
	    return b;
	}

	std::string debug_exceptions(void);

	VALUE current_exception(void) {
	    return current_exceptions.empty()
		? Qnil : current_exceptions.back();
	}

	void push_current_exception(VALUE exc) {
	    assert(!NIL_P(exc));
	    rb_objc_retain((void *)exc);
	    current_exceptions.push_back(exc);
	}

	VALUE pop_current_exception(void) {
	    assert(!current_exceptions.empty());
	    VALUE exc = current_exceptions.back();
	    rb_objc_release((void *)exc);
	    current_exceptions.pop_back();
	    return exc;
	}

	std::map<VALUE, rb_vm_catch_t *> catch_jmp_bufs;
	std::vector<jmp_buf *> return_from_block_jmp_bufs;

	bs_parser_t *bs_parser;
	std::map<std::string, rb_vm_bs_boxed_t *> bs_boxed;
	std::map<std::string, bs_element_function_t *> bs_funcs;
	std::map<ID, bs_element_constant_t *> bs_consts;
	std::map<std::string, std::map<SEL, bs_element_method_t *> *>
	    bs_classes_class_methods, bs_classes_instance_methods;
	std::map<std::string, bs_element_cftype_t *> bs_cftypes;

	bs_element_method_t *find_bs_method(Class klass, SEL sel);
	rb_vm_bs_boxed_t *find_bs_boxed(std::string type);
	rb_vm_bs_boxed_t *find_bs_struct(std::string type);
	rb_vm_bs_boxed_t *find_bs_opaque(std::string type);

	void *gen_stub(std::string types, int argc, bool is_objc);
	void *gen_to_rval_convertor(std::string type);
	void *gen_to_ocval_convertor(std::string type);

	void insert_stub(const char *types, void *stub, bool is_objc) {
	    std::map<std::string, void *> &m =
		is_objc ? objc_stubs : c_stubs;
	    m.insert(std::make_pair(types, stub));
	}

	std::map<SEL, std::map<Class, rb_vm_method_source_t *> *>
	    method_sources;
	std::multimap<Class, SEL> method_source_sels;

	std::map<Class, rb_vm_method_source_t *> *
	method_sources_for_sel(SEL sel, bool create)
	{
	    std::map<SEL, std::map<Class, rb_vm_method_source_t *> *>::iterator
		iter = method_sources.find(sel);
		
	    std::map<Class, rb_vm_method_source_t *> *map = NULL;
	    if (iter == method_sources.end()) {
		if (!create) {
		    return NULL;
		}
		map = new std::map<Class, rb_vm_method_source_t *>();
		method_sources[sel] = map;
	    }
	    else {
		map = iter->second;
	    }
	    return map;
	}

	std::map<Function *, IMP> objc_to_ruby_stubs;

#if ROXOR_VM_DEBUG
	long functions_compiled;
#endif

	RoxorVM(void);

	void optimize(Function *func);
	IMP compile(Function *func);
	VALUE interpret(Function *func);

	bool symbolize_call_address(void *addr, void **startp,
		unsigned long *ln, char *name, size_t name_len);

	bool is_running(void) { return running; }
	void set_running(bool flag) { running = flag; }

	struct mcache *method_cache_get(SEL sel, bool super);
	rb_vm_method_node_t *method_node_get(IMP imp);
	void add_method(Class klass, SEL sel, IMP imp, IMP ruby_imp,
		const rb_vm_arity_t &arity, int flags, const char *types);

	GlobalVariable *redefined_op_gvar(SEL sel, bool create);
	bool should_invalidate_inline_op(SEL sel, Class klass);

	struct ccache *constant_cache_get(ID path);
	void const_defined(ID path);
	
	std::map<ID, int> *get_ivar_slots(Class klass) {
	    std::map<Class, std::map<ID, int> *>::iterator iter = 
		ivar_slots.find(klass);
	    if (iter == ivar_slots.end()) {
		std::map<ID, int> *map = new std::map<ID, int>;
		ivar_slots[klass] = map;
		return map;
	    }
	    return iter->second;
	}
	int find_ivar_slot(VALUE klass, ID name, bool create);
	bool class_can_have_ivar_slots(VALUE klass);

	struct rb_vm_outer *get_outer(Class klass) {
	    std::map<Class, struct rb_vm_outer *>::iterator iter =
		outers.find(klass);
	    return iter == outers.end() ? NULL : iter->second;
	}

	void set_outer(Class klass, Class mod) {
	    struct rb_vm_outer *mod_outer = get_outer(mod);
	    struct rb_vm_outer *class_outer = get_outer(klass);
	    if (class_outer == NULL || class_outer->outer != mod_outer) {
		if (class_outer != NULL) {
		    free(class_outer);
		}
		class_outer = (struct rb_vm_outer *)
		    malloc(sizeof(struct rb_vm_outer));
		class_outer->klass = klass;
		class_outer->outer = mod_outer;
		outers[klass] = class_outer;
	    }
	}

	VALUE *get_binding_lvar(ID name) {
	    if (!bindings.empty()) {
		rb_vm_binding_t *b = bindings.back();
		for (rb_vm_local_t *l = b->locals; l != NULL; l = l->next) {
		    if (l->name == name) {
			return l->value;
		    }
		}
	    }
	    return NULL;
	}

	size_t get_sizeof(const Type *type);
	size_t get_sizeof(const char *type);
	bool is_large_struct_type(const Type *type);
};

#define GET_VM() (RoxorVM::current)

#endif /* __cplusplus */

#endif /* __VM_H_ */