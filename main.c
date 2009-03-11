/**********************************************************************

  main.c -

  $Author: nobu $
  created at: Fri Aug 19 13:19:58 JST 1994

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#undef RUBY_EXPORT
#include "ruby.h"
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

RUBY_GLOBAL_SETUP

int
main(int argc, char **argv, char **envp)
{
#ifdef RUBY_DEBUG_ENV
    ruby_set_debug_option(getenv("RUBY_DEBUG"));
#endif
#ifdef HAVE_LOCALE_H
    setlocale(LC_CTYPE, "");
#endif

    ruby_sysinit(&argc, &argv);
    {
	ruby_init();
	return ruby_run_node(ruby_options(argc, argv));
    }
}
