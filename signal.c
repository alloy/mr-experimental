/**********************************************************************

  signal.c -

  $Author: mame $
  created at: Tue Dec 20 10:13:44 JST 1994

  Copyright (C) 1993-2007 Yukihiro Matsumoto
  Copyright (C) 2000  Network Applied Communication Laboratory, Inc.
  Copyright (C) 2000  Information-technology Promotion Agency, Japan

**********************************************************************/

#include "ruby/ruby.h"
#include "ruby/signal.h"
#include "ruby/node.h"
#include "id.h"
#include "vm.h"
#include <signal.h>
#include <stdio.h>

#ifdef __BEOS__
#undef SIGBUS
#endif

#if defined HAVE_SIGPROCMASK || defined HAVE_SIGSETMASK
#define USE_TRAP_MASK 1
#else
#define USE_TRAP_MASK 0
#endif

#ifndef NSIG
# ifdef DJGPP
#  define NSIG SIGMAX
# else
#  define NSIG (_SIGMAX + 1)      /* For QNX */
# endif
#endif

static const struct signals {
    const char *signm;
    int  signo;
} siglist [] = {
    {"EXIT", 0},
#ifdef SIGHUP
    {"HUP", SIGHUP},
#endif
    {"INT", SIGINT},
#ifdef SIGQUIT
    {"QUIT", SIGQUIT},
#endif
#ifdef SIGILL
    {"ILL", SIGILL},
#endif
#ifdef SIGTRAP
    {"TRAP", SIGTRAP},
#endif
#ifdef SIGIOT
    {"IOT", SIGIOT},
#endif
#ifdef SIGABRT
    {"ABRT", SIGABRT},
#endif
#ifdef SIGEMT
    {"EMT", SIGEMT},
#endif
#ifdef SIGFPE
    {"FPE", SIGFPE},
#endif
#ifdef SIGKILL
    {"KILL", SIGKILL},
#endif
#ifdef SIGBUS
    {"BUS", SIGBUS},
#endif
#ifdef SIGSEGV
    {"SEGV", SIGSEGV},
#endif
#ifdef SIGSYS
    {"SYS", SIGSYS},
#endif
#ifdef SIGPIPE
    {"PIPE", SIGPIPE},
#endif
#ifdef SIGALRM
    {"ALRM", SIGALRM},
#endif
#ifdef SIGTERM
    {"TERM", SIGTERM},
#endif
#ifdef SIGURG
    {"URG", SIGURG},
#endif
#ifdef SIGSTOP
    {"STOP", SIGSTOP},
#endif
#ifdef SIGTSTP
    {"TSTP", SIGTSTP},
#endif
#ifdef SIGCONT
    {"CONT", SIGCONT},
#endif
#ifdef SIGCHLD
    {"CHLD", SIGCHLD},
#endif
#ifdef SIGCLD
    {"CLD", SIGCLD},
#else
# ifdef SIGCHLD
    {"CLD", SIGCHLD},
# endif
#endif
#ifdef SIGTTIN
    {"TTIN", SIGTTIN},
#endif
#ifdef SIGTTOU
    {"TTOU", SIGTTOU},
#endif
#ifdef SIGIO
    {"IO", SIGIO},
#endif
#ifdef SIGXCPU
    {"XCPU", SIGXCPU},
#endif
#ifdef SIGXFSZ
    {"XFSZ", SIGXFSZ},
#endif
#ifdef SIGVTALRM
    {"VTALRM", SIGVTALRM},
#endif
#ifdef SIGPROF
    {"PROF", SIGPROF},
#endif
#ifdef SIGWINCH
    {"WINCH", SIGWINCH},
#endif
#ifdef SIGUSR1
    {"USR1", SIGUSR1},
#endif
#ifdef SIGUSR2
    {"USR2", SIGUSR2},
#endif
#ifdef SIGLOST
    {"LOST", SIGLOST},
#endif
#ifdef SIGMSG
    {"MSG", SIGMSG},
#endif
#ifdef SIGPWR
    {"PWR", SIGPWR},
#endif
#ifdef SIGPOLL
    {"POLL", SIGPOLL},
#endif
#ifdef SIGDANGER
    {"DANGER", SIGDANGER},
#endif
#ifdef SIGMIGRATE
    {"MIGRATE", SIGMIGRATE},
#endif
#ifdef SIGPRE
    {"PRE", SIGPRE},
#endif
#ifdef SIGGRANT
    {"GRANT", SIGGRANT},
#endif
#ifdef SIGRETRACT
    {"RETRACT", SIGRETRACT},
#endif
#ifdef SIGSOUND
    {"SOUND", SIGSOUND},
#endif
#ifdef SIGINFO
    {"INFO", SIGINFO},
#endif
    {NULL, 0}
};

static int
signm2signo(const char *nm)
{
    const struct signals *sigs;

    for (sigs = siglist; sigs->signm; sigs++)
	if (strcmp(sigs->signm, nm) == 0)
	    return sigs->signo;
    return 0;
}

static const char*
signo2signm(int no)
{
    const struct signals *sigs;

    for (sigs = siglist; sigs->signm; sigs++)
	if (sigs->signo == no)
	    return sigs->signm;
    return 0;
}

const char *
ruby_signal_name(int no)
{
    return signo2signm(no);
}

/*
 * call-seq:
 *    SignalException.new(sig)   =>  signal_exception
 *
 *  Construct a new SignalException object.  +sig+ should be a known
 *  signal name, or a signal number.
 */

static VALUE
esignal_init(VALUE self, SEL sel, int argc, VALUE *argv)
{
    int argnum = 1;
    VALUE sig = Qnil;
    int signo;
    const char *signm;

    if (argc > 0) {
	sig = rb_check_to_integer(argv[0], "to_int");
	if (!NIL_P(sig)) argnum = 2;
	else sig = argv[0];
    }
    if (argc < 1 || argnum < argc) {
	rb_raise(rb_eArgError, "wrong number of arguments (%d for %d)",
		 argc, argnum);
    }
    if (argnum == 2) {
	signo = NUM2INT(sig);
	if (signo < 0 || signo > NSIG) {
	    rb_raise(rb_eArgError, "invalid signal number (%d)", signo);
	}
	if (argc > 1) {
	    sig = argv[1];
	}
	else {
	    signm = signo2signm(signo);
	    if (signm) {
		sig = rb_sprintf("SIG%s", signm);
	    }
	    else {
		sig = rb_sprintf("SIG%u", signo);
	    }
	}
    }
    else {
	signm = SYMBOL_P(sig) ? rb_sym2name(sig) : StringValuePtr(sig);
	if (strncmp(signm, "SIG", 3) == 0) signm += 3;
	signo = signm2signo(signm);
	if (!signo) {
	    rb_raise(rb_eArgError, "unsupported name `SIG%s'", signm);
	}
	sig = rb_sprintf("SIG%s", signm);
    }
    //rb_call_super(1, &sig);
    rb_vm_call(self, selInitialize2, 1, &sig, true);
    rb_iv_set(self, "signo", INT2NUM(signo));

    return self;
}

/*
 * call-seq:
 *    signal_exception.signo   =>  num
 *
 *  Returns a signal number.
 */

static VALUE
esignal_signo(VALUE self, SEL sel)
{
    return rb_iv_get(self, "signo");
}

static VALUE
interrupt_init(VALUE self, SEL sel, int argc, VALUE *argv)
{
    VALUE args[2];

    args[0] = INT2FIX(SIGINT);
    rb_scan_args(argc, argv, "01", &args[1]);
    //return rb_call_super(2, args);
    return rb_vm_call(self, selInitialize2, 2, args, true);
}

void
ruby_default_signal(int sig)
{
#ifndef MACOS_UNUSE_SIGNAL
    signal(sig, SIG_DFL);
    raise(sig);
#endif
}

/*
 *  call-seq:
 *     Process.kill(signal, pid, ...)    => fixnum
 *  
 *  Sends the given signal to the specified process id(s), or to the
 *  current process if _pid_ is zero. _signal_ may be an
 *  integer signal number or a POSIX signal name (either with or without
 *  a +SIG+ prefix). If _signal_ is negative (or starts
 *  with a minus sign), kills process groups instead of
 *  processes. Not all signals are available on all platforms.
 *     
 *     pid = fork do
 *        Signal.trap("HUP") { puts "Ouch!"; exit }
 *        # ... do some work ...
 *     end
 *     # ...
 *     Process.kill("HUP", pid)
 *     Process.wait
 *     
 *  <em>produces:</em>
 *     
 *     Ouch!
 */

VALUE
rb_f_kill(int argc, VALUE *argv)
{
#ifndef HAS_KILLPG
#define killpg(pg, sig) kill(-(pg), sig)
#endif
    int negative = 0;
    int sig;
    int i;
    const char *s;

    rb_secure(2);
    if (argc < 2)
	rb_raise(rb_eArgError, "wrong number of arguments -- kill(sig, pid...)");
    switch (TYPE(argv[0])) {
      case T_FIXNUM:
	sig = FIX2INT(argv[0]);
	break;

      case T_SYMBOL:
	s = rb_sym2name(argv[0]);
	if (!s) rb_raise(rb_eArgError, "bad signal");
	goto str_signal;

      case T_STRING:
	s = RSTRING_PTR(argv[0]);
	if (s[0] == '-') {
	    negative++;
	    s++;
	}
      str_signal:
	if (strncmp("SIG", s, 3) == 0)
	    s += 3;
	if((sig = signm2signo(s)) == 0)
	    rb_raise(rb_eArgError, "unsupported name `SIG%s'", s);

	if (negative)
	    sig = -sig;
	break;

      default:
        {
	    VALUE str;

	    str = rb_check_string_type(argv[0]);
	    if (!NIL_P(str)) {
		s = RSTRING_PTR(str);
		goto str_signal;
	    }
	    rb_raise(rb_eArgError, "bad signal type %s",
		     rb_obj_classname(argv[0]));
	}
	break;
    }

    if (sig < 0) {
	sig = -sig;
	for (i=1; i<argc; i++) {
	    if (killpg(NUM2PIDT(argv[i]), sig) < 0)
		rb_sys_fail(0);
	}
    }
    else {
	for (i=1; i<argc; i++) {
	    if (kill(NUM2PIDT(argv[i]), sig) < 0)
		rb_sys_fail(0);
	}
    }
    rb_thread_polling();
    return INT2FIX(i-1);
}

static struct {
    VALUE cmd;
} trap_list[NSIG];
static rb_atomic_t trap_pending_list[NSIG];
#if 0
static char rb_trap_accept_nativethreads[NSIG];
#endif
rb_atomic_t rb_trap_pending;
rb_atomic_t rb_trap_immediate;
int rb_prohibit_interrupt = 1;

VALUE
rb_get_trap_cmd(int sig)
{
    return trap_list[sig].cmd;
}

void
rb_gc_mark_trap_list(void)
{
#ifndef MACOS_UNUSE_SIGNAL
    int i;

    for (i=0; i<NSIG; i++) {
	if (trap_list[i].cmd)
	    rb_gc_mark(trap_list[i].cmd);
    }
#endif /* MACOS_UNUSE_SIGNAL */
}

#ifdef __dietlibc__
#define sighandler_t sh_t
#endif

typedef RETSIGTYPE (*sighandler_t)(int);

#ifdef POSIX_SIGNAL
static sighandler_t
ruby_signal(int signum, sighandler_t handler)
{
    struct sigaction sigact, old;

#if 0
    rb_trap_accept_nativethreads[signum] = 0;
#endif

    sigemptyset(&sigact.sa_mask);
#ifdef SA_SIGINFO
    sigact.sa_sigaction = (void (*)(int, siginfo_t*, void*))handler;
    sigact.sa_flags = SA_SIGINFO;
#else
    sigact.sa_handler = handler;
    sigact.sa_flags = 0;
#endif

#ifdef SA_NOCLDWAIT
    if (signum == SIGCHLD && handler == SIG_IGN)
	sigact.sa_flags |= SA_NOCLDWAIT;
#endif
    sigaction(signum, &sigact, &old);
    return old.sa_handler;
}

sighandler_t
posix_signal(int signum, sighandler_t handler)
{
    return ruby_signal(signum, handler);
}

#else /* !POSIX_SIGNAL */
#define ruby_signal(sig,handler) (/* rb_trap_accept_nativethreads[sig] = 0,*/ signal((sig),(handler)))
#if 0 /* def HAVE_NATIVETHREAD */
static sighandler_t
ruby_nativethread_signal(int signum, sighandler_t handler)
{
    sighandler_t old;

    old = signal(signum, handler);
    rb_trap_accept_nativethreads[signum] = 1;
    return old;
}
#endif
#endif

static RETSIGTYPE
sighandler(int sig)
{
#if 0
    rb_vm_t *vm = GET_VM(); /* fix me for Multi-VM */
    ATOMIC_INC(vm->signal_buff[sig]);
    ATOMIC_INC(vm->buffered_signal_size);
#endif

#if !defined(BSD_SIGNAL) && !defined(POSIX_SIGNAL)
    ruby_signal(sig, sighandler);
#endif
}

#if USE_TRAP_MASK
# ifdef HAVE_SIGPROCMASK
static sigset_t trap_last_mask;
# else
static int trap_last_mask;
# endif
#endif

#if HAVE_PTHREAD_H
#include <pthread.h>
#endif

void
rb_disable_interrupt(void)
{
#ifndef _WIN32
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGVTALRM);
    sigdelset(&mask, SIGSEGV);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);
#endif
}

void
rb_enable_interrupt(void)
{
#ifndef _WIN32
    sigset_t mask;
    sigemptyset(&mask);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);
#endif
}

#if 0 // XXX unused function
int
rb_get_next_signal(rb_vm_t *vm)
{
    int i, sig = 0;

    for (i=1; i<RUBY_NSIG; i++) {
	if (vm->signal_buff[i] > 0) {
	    rb_disable_interrupt();
	    {
		ATOMIC_DEC(vm->signal_buff[i]);
		ATOMIC_DEC(vm->buffered_signal_size);
	    }
	    rb_enable_interrupt();
	    sig = i;
	    break;
	}
    }
    return sig;
}
#endif

#ifdef SIGBUS
static RETSIGTYPE
sigbus(int sig)
{
    rb_bug("Bus Error");
}
#endif

#ifdef SIGSEGV
static int segv_received = 0;
static RETSIGTYPE
sigsegv(int sig)
{
    if (segv_received) {
	fprintf(stderr, "SEGV recieved in SEGV handler\n");
	exit(1);
    }
    else {
	segv_received = 1;
	rb_bug("Segmentation fault");
    }
}
#endif

#ifdef SIGPIPE
static RETSIGTYPE
sigpipe(int sig)
{
    /* do nothing */
}
#endif

static void
signal_exec(VALUE cmd, int sig)
{
#if 0 // TODO
    rb_proc_t *proc;
    VALUE signum = INT2FIX(sig);
    GetProcPtr(cmd, proc);
    vm_invoke_proc(GET_THREAD(), proc, proc->block.self, 1, &signum, 0);
#endif
}

void
rb_trap_exit(void)
{
#ifndef MACOS_UNUSE_SIGNAL
    if (trap_list[0].cmd) {
	VALUE trap_exit = trap_list[0].cmd;

	trap_list[0].cmd = 0;
	signal_exec(trap_exit, 0);
    }
#endif
}

static void
rb_signal_exec(int sig)
{
    VALUE cmd = rb_get_trap_cmd(sig);

    if (cmd == 0) {
	switch (sig) {
	  case SIGINT:
	    rb_interrupt();
	    break;
#ifdef SIGHUP
	  case SIGHUP:
#endif
#ifdef SIGQUIT
	  case SIGQUIT:
#endif
#ifdef SIGTERM
	  case SIGTERM:
#endif
#ifdef SIGALRM
	  case SIGALRM:
#endif
#ifdef SIGUSR1
	  case SIGUSR1:
#endif
#ifdef SIGUSR2
	  case SIGUSR2:
#endif
	    //rb_thread_signal_raise(th, sig);
	    break;
	}
    }
    else if (cmd == Qundef) {
//	rb_thread_signal_exit(th);
    }
    else {
	signal_exec(cmd, sig);
    }
}

void
rb_trap_exec(void)
{
#ifndef MACOS_UNUSE_SIGNAL
    int i;

    for (i=0; i<NSIG; i++) {
	if (trap_pending_list[i]) {
	    trap_pending_list[i] = 0;
	    rb_signal_exec(i);
	}
    }
#endif /* MACOS_UNUSE_SIGNAL */
    rb_trap_pending = 0;
}

struct trap_arg {
#if USE_TRAP_MASK
# ifdef HAVE_SIGPROCMASK
    sigset_t mask;
# else
    int mask;
# endif
#endif
    int sig;
    sighandler_t func;
    VALUE cmd;
};

static sighandler_t
default_handler(int sig)
{
    sighandler_t func;
    switch (sig) {
      case SIGINT:
#ifdef SIGHUP
      case SIGHUP:
#endif
#ifdef SIGQUIT
      case SIGQUIT:
#endif
#ifdef SIGTERM
      case SIGTERM:
#endif
#ifdef SIGALRM
      case SIGALRM:
#endif
#ifdef SIGUSR1
      case SIGUSR1:
#endif
#ifdef SIGUSR2
      case SIGUSR2:
#endif
        func = sighandler;
        break;
#ifdef SIGBUS
      case SIGBUS:
        func = sigbus;
        break;
#endif
#ifdef SIGSEGV
      case SIGSEGV:
        func = sigsegv;
        break;
#endif
#ifdef SIGPIPE
      case SIGPIPE:
        func = sigpipe;
        break;
#endif
      default:
        func = SIG_DFL;
        break;
    }

    return func;
}

static RETSIGTYPE
wrong_trap(int sig)
{
}

static sighandler_t
trap_handler(VALUE *cmd, int sig)
{
    sighandler_t func = wrong_trap;
    VALUE command;

    if (NIL_P(*cmd)) {
	func = SIG_IGN;
    }
    else {
	command = rb_check_string_type(*cmd);
	if (!NIL_P(command)) {
	    SafeStringValue(command);	/* taint check */
	    switch (RSTRING_LEN(command)) {
	      case 0:
                goto sig_ign;
		break;
              case 14:
		if (strncmp(RSTRING_PTR(command), "SYSTEM_DEFAULT", 14) == 0) {
                    func = SIG_DFL;
                    *cmd = 0;
		}
                break;
	      case 7:
		if (strncmp(RSTRING_PTR(command), "SIG_IGN", 7) == 0) {
sig_ign:
                    func = SIG_IGN;
                    *cmd = 0;
		}
		else if (strncmp(RSTRING_PTR(command), "SIG_DFL", 7) == 0) {
sig_dfl:
                    func = default_handler(sig);
                    *cmd = 0;
		}
		else if (strncmp(RSTRING_PTR(command), "DEFAULT", 7) == 0) {
                    goto sig_dfl;
		}
		break;
	      case 6:
		if (strncmp(RSTRING_PTR(command), "IGNORE", 6) == 0) {
                    goto sig_ign;
		}
		break;
	      case 4:
		if (strncmp(RSTRING_PTR(command), "EXIT", 4) == 0) {
		    func = sighandler;
		    *cmd = Qundef;
		}
		break;
	    }
	    if (func == wrong_trap) {
		rb_raise(rb_eArgError, "wrong trap - %s", RSTRING_PTR(command));
	    }
	}
	else {
#if 0 // TODO
	    rb_proc_t *proc;
	    GetProcPtr(*cmd, proc);
#endif
	    func = sighandler;
	}
    }

    return func;
}

static int
trap_signm(VALUE vsig)
{
    int sig = -1;
    const char *s;

    switch (TYPE(vsig)) {
      case T_FIXNUM:
	sig = FIX2INT(vsig);
	if (sig < 0 || sig >= NSIG) {
	    rb_raise(rb_eArgError, "invalid signal number (%d)", sig);
	}
	break;

      case T_SYMBOL:
	s = rb_sym2name(vsig);
	if (!s) rb_raise(rb_eArgError, "bad signal");
	goto str_signal;

      default:
	s = StringValuePtr(vsig);

      str_signal:
	if (strncmp("SIG", s, 3) == 0)
	    s += 3;
	sig = signm2signo(s);
	if (sig == 0 && strcmp(s, "EXIT") != 0)
	    rb_raise(rb_eArgError, "unsupported signal SIG%s", s);
    }
    return sig;
}

static VALUE
trap(struct trap_arg *arg)
{
    sighandler_t oldfunc, func = arg->func;
    VALUE oldcmd, command = arg->cmd;
    int sig = arg->sig;

    oldfunc = ruby_signal(sig, func);
    oldcmd = trap_list[sig].cmd;
    switch (oldcmd) {
      case 0:
	if (oldfunc == SIG_IGN) oldcmd = rb_str_new2("IGNORE");
	else if (oldfunc == sighandler) oldcmd = rb_str_new2("DEFAULT");
	else oldcmd = Qnil;
	break;
      case Qundef:
	oldcmd = rb_str_new2("EXIT");
	break;
    }

    trap_list[sig].cmd = command;
    /* enable at least specified signal. */
#if USE_TRAP_MASK
#ifdef HAVE_SIGPROCMASK
    sigdelset(&arg->mask, sig);
#else
    arg->mask &= ~sigmask(sig);
#endif
#endif
    return oldcmd;
}

#if USE_TRAP_MASK
static VALUE
trap_ensure(struct trap_arg *arg)
{
    /* enable interrupt */
#ifdef HAVE_SIGPROCMASK
    sigprocmask(SIG_SETMASK, &arg->mask, NULL);
#else
    sigsetmask(arg->mask);
#endif
    trap_last_mask = arg->mask;
    return 0;
}
#endif

void
rb_trap_restore_mask(void)
{
#if USE_TRAP_MASK
# ifdef HAVE_SIGPROCMASK
    sigprocmask(SIG_SETMASK, &trap_last_mask, NULL);
# else
    sigsetmask(trap_last_mask);
# endif
#endif
}

/*
 * call-seq:
 *   Signal.trap( signal, command ) => obj
 *   Signal.trap( signal ) {| | block } => obj
 *
 * Specifies the handling of signals. The first parameter is a signal
 * name (a string such as ``SIGALRM'', ``SIGUSR1'', and so on) or a
 * signal number. The characters ``SIG'' may be omitted from the
 * signal name. The command or block specifies code to be run when the
 * signal is raised.
 * If the command is the string ``IGNORE'' or ``SIG_IGN'', the signal
 * will be ignored.
 * If the command is ``DEFAULT'' or ``SIG_DFL'', the Ruby's default handler
 * will be invoked.
 * If the command is ``EXIT'', the script will be terminated by the signal.
 * If the command is ``SYSTEM_DEFAULT'', the operating system's default
 * handler will be invoked.
 * Otherwise, the given command or block will be run.
 * The special signal name ``EXIT'' or signal number zero will be
 * invoked just prior to program termination.
 * trap returns the previous handler for the given signal.
 *
 *     Signal.trap(0, proc { puts "Terminating: #{$$}" })
 *     Signal.trap("CLD")  { puts "Child died" }
 *     fork && Process.wait
 *
 * produces:
 *     Terminating: 27461
 *     Child died
 *     Terminating: 27460
 */
static VALUE
sig_trap(VALUE rcv, SEL sel, int argc, VALUE *argv)
{
    struct trap_arg arg;

    rb_secure(2);
    if (argc == 0 || argc > 2) {
	rb_raise(rb_eArgError, "wrong number of arguments -- trap(sig, cmd)/trap(sig){...}");
    }

    arg.sig = trap_signm(argv[0]);
    if (argc == 1) {
	arg.cmd = rb_block_proc();
	arg.func = sighandler;
    }
    else if (argc == 2) {
	arg.cmd = argv[1];
	arg.func = trap_handler(&arg.cmd, arg.sig);
    }

    if (OBJ_TAINTED(arg.cmd)) {
	rb_raise(rb_eSecurityError, "Insecure: tainted signal trap");
    }
#if USE_TRAP_MASK
    /* disable interrupt */
# ifdef HAVE_SIGPROCMASK
    sigfillset(&arg.mask);
    sigprocmask(SIG_BLOCK, &arg.mask, &arg.mask);
# else
    arg.mask = sigblock(~0);
# endif

    return rb_ensure(trap, (VALUE)&arg, trap_ensure, (VALUE)&arg);
#else
    return trap(&arg);
#endif
}

/*
 * call-seq:
 *   Signal.list => a_hash
 *
 * Returns a list of signal names mapped to the corresponding
 * underlying signal numbers.
 *
 * Signal.list   #=> {"ABRT"=>6, "ALRM"=>14, "BUS"=>7, "CHLD"=>17, "CLD"=>17, "CONT"=>18, "FPE"=>8, "HUP"=>1, "ILL"=>4, "INT"=>2, "IO"=>29, "IOT"=>6, "KILL"=>9, "PIPE"=>13, "POLL"=>29, "PROF"=>27, "PWR"=>30, "QUIT"=>3, "SEGV"=>11, "STOP"=>19, "SYS"=>31, "TERM"=>15, "TRAP"=>5, "TSTP"=>20, "TTIN"=>21, "TTOU"=>22, "URG"=>23, "USR1"=>10, "USR2"=>12, "VTALRM"=>26, "WINCH"=>28, "XCPU"=>24, "XFSZ"=>25}
 */
static VALUE
sig_list(VALUE rcv, SEL sel)
{
    VALUE h = rb_hash_new();
    const struct signals *sigs;

    for (sigs = siglist; sigs->signm; sigs++) {
	rb_hash_aset(h, rb_str_new2(sigs->signm), INT2FIX(sigs->signo));
    }
    return h;
}

static void
install_sighandler(int signum, sighandler_t handler)
{
    sighandler_t old;

    old = ruby_signal(signum, handler);
    if (old != SIG_DFL) {
	ruby_signal(signum, old);
    }
}

#if defined(SIGCLD) || defined(SIGCHLD)
static void
init_sigchld(int sig)
{
    sighandler_t oldfunc;
#if USE_TRAP_MASK
# ifdef HAVE_SIGPROCMASK
    sigset_t mask;
# else
    int mask;
# endif
#endif

#if USE_TRAP_MASK
    /* disable interrupt */
# ifdef HAVE_SIGPROCMASK
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &mask);
# else
    mask = sigblock(~0);
# endif
#endif

    oldfunc = ruby_signal(sig, SIG_DFL);
    if (oldfunc != SIG_DFL && oldfunc != SIG_IGN) {
	ruby_signal(sig, oldfunc);
    } else {
	trap_list[sig].cmd = 0;
    }

#if USE_TRAP_MASK
#ifdef HAVE_SIGPROCMASK
    sigdelset(&mask, sig);
    sigprocmask(SIG_SETMASK, &mask, NULL);
#else
    mask &= ~sigmask(sig);
    sigsetmask(mask);
#endif
    trap_last_mask = mask;
#endif
}
#endif

void
ruby_sig_finalize()
{
    sighandler_t oldfunc;

    oldfunc = ruby_signal(SIGINT, SIG_IGN);
    if (oldfunc == sighandler) {
	ruby_signal(SIGINT, SIG_DFL);
    }
}


#ifdef RUBY_DEBUG_ENV
int ruby_enable_coredump = 0;
#endif

/*
 * Many operating systems allow signals to be sent to running
 * processes. Some signals have a defined effect on the process, while
 * others may be trapped at the code level and acted upon. For
 * example, your process may trap the USR1 signal and use it to toggle
 * debugging, and may use TERM to initiate a controlled shutdown.
 *
 *     pid = fork do
 *       Signal.trap("USR1") do
 *         $debug = !$debug
 *         puts "Debug now: #$debug"
 *       end
 *       Signal.trap("TERM") do
 *         puts "Terminating..."
 *         shutdown()
 *       end
 *       # . . . do some work . . .
 *     end
 *
 *     Process.detach(pid)
 *
 *     # Controlling program:
 *     Process.kill("USR1", pid)
 *     # ...
 *     Process.kill("USR1", pid)
 *     # ...
 *     Process.kill("TERM", pid)
 *
 * produces:
 *     Debug now: true
 *     Debug now: false
 *    Terminating...
 *
 * The list of available signal names and their interpretation is
 * system dependent. Signal delivery semantics may also vary between
 * systems; in particular signal delivery may not always be reliable.
 */
void
Init_signal(void)
{
#ifndef MACOS_UNUSE_SIGNAL
    VALUE mSignal = rb_define_module("Signal");

    rb_objc_define_method(rb_mKernel, "trap", sig_trap, -1);
    rb_objc_define_method(*(VALUE *)mSignal, "trap", sig_trap, -1);
    rb_objc_define_method(*(VALUE *)mSignal, "list", sig_list, 0);

    rb_objc_define_method(rb_eSignal, "initialize", esignal_init, -1);
    rb_objc_define_method(rb_eSignal, "signo", esignal_signo, 0);
    rb_alias(rb_eSignal, rb_intern("signm"), rb_intern("message"));
    rb_objc_define_method(rb_eInterrupt, "initialize", interrupt_init, -1);

    install_sighandler(SIGINT, sighandler);
#ifdef SIGHUP
    install_sighandler(SIGHUP, sighandler);
#endif
#ifdef SIGQUIT
    install_sighandler(SIGQUIT, sighandler);
#endif
#ifdef SIGTERM
    install_sighandler(SIGTERM, sighandler);
#endif
#ifdef SIGALRM
    install_sighandler(SIGALRM, sighandler);
#endif
#ifdef SIGUSR1
    install_sighandler(SIGUSR1, sighandler);
#endif
#ifdef SIGUSR2
    install_sighandler(SIGUSR2, sighandler);
#endif

#ifdef RUBY_DEBUG_ENV
    if (!ruby_enable_coredump)
#endif
    {
#ifdef SIGBUS
    install_sighandler(SIGBUS, sigbus);
#endif
#ifdef SIGSEGV
    install_sighandler(SIGSEGV, sigsegv);
#endif
    }
#ifdef SIGPIPE
    install_sighandler(SIGPIPE, sigpipe);
#endif

#if defined(SIGCLD)
    init_sigchld(SIGCLD);
#elif defined(SIGCHLD)
    init_sigchld(SIGCHLD);
#endif

#endif /* MACOS_UNUSE_SIGNAL */
}
