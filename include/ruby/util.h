/**********************************************************************

  util.h -

  $Author: nobu $
  created at: Thu Mar  9 11:55:53 JST 1995

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#ifndef RUBY_UTIL_H
#define RUBY_UTIL_H 1

#if defined(__cplusplus)
extern "C" {
#if 0
} /* satisfy cc-mode */
#endif
#endif

#ifndef _
#ifdef __cplusplus
# ifndef  HAVE_PROTOTYPES
#  define HAVE_PROTOTYPES 1
# endif
# ifndef  HAVE_STDARG_PROTOTYPES
#  define HAVE_STDARG_PROTOTYPES 1
# endif
#endif
#ifdef HAVE_PROTOTYPES
# define _(args) args
#else
# define _(args) ()
#endif
#ifdef HAVE_STDARG_PROTOTYPES
# define __(args) args
#else
# define __(args) ()
#endif
#endif

#define scan_oct ruby_scan_oct
unsigned long ruby_scan_oct(const char *, int, int *);
#define scan_hex ruby_scan_hex
unsigned long ruby_scan_hex(const char *, int, int *);

#if defined(MSDOS) || defined(__CYGWIN32__) || defined(_WIN32)
void ruby_add_suffix(VALUE str, const char *suffix);
#endif

void ruby_qsort(void *, const int, const int,
		int (*)(const void *, const void *, void *), void *);

void ruby_setenv(const char *, const char *);
void ruby_unsetenv(const char *);
#undef setenv
#undef unsetenv
#define setenv(name,val) ruby_setenv(name,val)
#define unsetenv(name,val) ruby_unsetenv(name);

char *ruby_strdup(const char *);
#if !WITH_OBJC
#undef strdup
#define strdup(s) ruby_strdup(s)
#endif

char *ruby_getcwd(void);
#define my_getcwd() ruby_getcwd()

double ruby_strtod(const char *, char **);
#undef strtod
#define strtod(s,e) ruby_strtod(s,e)

void ruby_each_words(const char *, void (*)(const char*, int, void*), void *);

#if defined(__cplusplus)
#if 0
{ /* satisfy cc-mode */
#endif
}  /* extern "C" { */
#endif

#endif /* RUBY_UTIL_H */
