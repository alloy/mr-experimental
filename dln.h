/**********************************************************************

  dln.h -

  $Author: nobu $
  created at: Wed Jan 19 16:53:09 JST 1994

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#ifndef DLN_H
#define DLN_H

#ifdef __cplusplus
# ifndef  HAVE_PROTOTYPES
#  define HAVE_PROTOTYPES 1
# endif
# ifndef  HAVE_STDARG_PROTOTYPES
#  define HAVE_STDARG_PROTOTYPES 1
# endif
#endif

#undef _
#ifdef HAVE_PROTOTYPES
# define _(args) args
#else
# define _(args) ()
#endif

char *dln_find_exe(const char*,const char*);
char *dln_find_file(const char*,const char*);
char *dln_find_exe_r(const char*,const char*,char*,int);
char *dln_find_file_r(const char*,const char*,char*,int);

#ifdef USE_DLN_A_OUT
extern char *dln_argv0;
#endif

void *dln_load(const char*);
#endif
