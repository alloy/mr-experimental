/**********************************************************************

  encoding.h -

  $Author: matz $
  created at: Thu May 24 11:49:41 JST 2007

  Copyright (C) 2007 Yukihiro Matsumoto

**********************************************************************/

#ifndef RUBY_ENCODING_H
#define RUBY_ENCODING_H 1

#ifdef HAVE_STDARG_PROTOTYPES
# include <stdarg.h>
#else
# include <varargs.h>
#endif

#if WITH_OBJC

#include <wctype.h>

typedef CFStringEncoding rb_encoding;

#else

#include "ruby/oniguruma.h"

#define ENCODING_INLINE_MAX 1023
#define ENCODING_SHIFT (FL_USHIFT+10)
#define ENCODING_MASK (ENCODING_INLINE_MAX<<ENCODING_SHIFT)

#define ENCODING_SET_INLINED(obj,i) do {\
    RBASIC(obj)->flags &= ~ENCODING_MASK;\
    RBASIC(obj)->flags |= (i) << ENCODING_SHIFT;\
} while (0)
#define ENCODING_SET(obj,i) do {\
    VALUE rb_encoding_set_obj = (obj); \
    int encoding_set_enc_index = (i); \
    if (encoding_set_enc_index < ENCODING_INLINE_MAX) \
        ENCODING_SET_INLINED(rb_encoding_set_obj, encoding_set_enc_index); \
    else \
        rb_enc_set_index(rb_encoding_set_obj, encoding_set_enc_index); \
} while (0)

#define ENCODING_GET_INLINED(obj) ((RBASIC(obj)->flags & ENCODING_MASK)>>ENCODING_SHIFT)
#define ENCODING_GET(obj) \
    (ENCODING_GET_INLINED(obj) != ENCODING_INLINE_MAX ? \
     ENCODING_GET_INLINED(obj) : \
     rb_enc_get_index(obj))

#if WITH_OBJC
# define ENCODING_IS_ASCII8BIT(obj) (1)
#else
# define ENCODING_IS_ASCII8BIT(obj) (ENCODING_GET_INLINED(obj) == 0)
#endif

#define ENC_CODERANGE_MASK	(FL_USER8|FL_USER9)
#define ENC_CODERANGE_UNKNOWN	0
#define ENC_CODERANGE_7BIT	FL_USER8
#define ENC_CODERANGE_VALID	FL_USER9
#define ENC_CODERANGE_BROKEN	(FL_USER8|FL_USER9)
#define ENC_CODERANGE(obj) (RBASIC(obj)->flags & ENC_CODERANGE_MASK)
#define ENC_CODERANGE_ASCIIONLY(obj) (ENC_CODERANGE(obj) == ENC_CODERANGE_7BIT)
#define ENC_CODERANGE_SET(obj,cr) (RBASIC(obj)->flags = \
				   (RBASIC(obj)->flags & ~ENC_CODERANGE_MASK) | (cr))
#define ENC_CODERANGE_CLEAR(obj) ENC_CODERANGE_SET(obj,0)

/* assumed ASCII compatiblity */
#define ENC_CODERANGE_AND(a, b) \
    (a == ENC_CODERANGE_7BIT ? b : \
     a == ENC_CODERANGE_VALID ? (b == ENC_CODERANGE_7BIT ? ENC_CODERANGE_VALID : b) : \
     ENC_CODERANGE_UNKNOWN)

#define ENCODING_CODERANGE_SET(obj, encindex, cr) \
    do { \
        VALUE rb_encoding_coderange_obj = (obj); \
        ENCODING_SET(rb_encoding_coderange_obj, (encindex)); \
        ENC_CODERANGE_SET(rb_encoding_coderange_obj, (cr)); \
    } while (0)

typedef OnigEncodingType rb_encoding;
#endif

#define ENCODING_MAXNAMELEN 42

int rb_enc_replicate(const char *, rb_encoding *);
int rb_define_dummy_encoding(const char *);
#define rb_enc_to_index(enc) ((enc) ? ((enc)->ruby_encoding_index) : 0)
int rb_enc_get_index(VALUE obj);
void rb_enc_set_index(VALUE obj, int encindex);
int rb_enc_find_index(const char *name);
int rb_to_encoding_index(VALUE);
rb_encoding* rb_to_encoding(VALUE);
rb_encoding* rb_enc_get(VALUE);
rb_encoding* rb_enc_compatible(VALUE,VALUE);
rb_encoding* rb_enc_check(VALUE,VALUE);
VALUE rb_enc_associate_index(VALUE, int);
VALUE rb_enc_associate(VALUE, rb_encoding*);
void rb_enc_copy(VALUE dst, VALUE src);

VALUE rb_enc_str_new(const char*, long, rb_encoding*);
VALUE rb_enc_reg_new(const char*, long, rb_encoding*, int);
PRINTF_ARGS(VALUE rb_enc_sprintf(rb_encoding *, const char*, ...), 2, 3);
VALUE rb_enc_vsprintf(rb_encoding *, const char*, va_list);
long rb_enc_strlen(const char*, const char*, rb_encoding*);
char* rb_enc_nth(const char*, const char*, int, rb_encoding*);
VALUE rb_obj_encoding(VALUE, SEL);
VALUE rb_enc_str_buf_cat(VALUE str, const char *ptr, long len, rb_encoding *enc);

/* index -> rb_encoding */
rb_encoding* rb_enc_from_index(int idx);

/* name -> rb_encoding */
rb_encoding * rb_enc_find(const char *name);

#if WITH_OBJC
rb_encoding * rb_enc_find2(VALUE name);
#endif

/* encoding -> name */
#if WITH_OBJC
const char *rb_enc_name(rb_encoding *);
VALUE rb_enc_name2(rb_encoding *);
#else
#define rb_enc_name(enc) (enc)->name
#endif

/* encoding -> minlen/maxlen */
#if WITH_OBJC
long rb_enc_mbminlen(rb_encoding *);
long rb_enc_mbmaxlen(rb_encoding *);
#else
#define rb_enc_mbminlen(enc) (enc)->min_enc_len
#define rb_enc_mbmaxlen(enc) (enc)->max_enc_len
#endif

/* -> mbclen (no error notification: 0 < ret <= e-p, no exception) */
int rb_enc_mbclen(const char *p, const char *e, rb_encoding *enc);

/* -> chlen, invalid or needmore */
int rb_enc_precise_mbclen(const char *p, const char *e, rb_encoding *enc);
#define MBCLEN_CHARFOUND_P(ret)     ONIGENC_MBCLEN_CHARFOUND_P(ret)
#define MBCLEN_CHARFOUND_LEN(ret)     ONIGENC_MBCLEN_CHARFOUND_LEN(ret)
#define MBCLEN_INVALID_P(ret)       ONIGENC_MBCLEN_INVALID_P(ret)
#define MBCLEN_NEEDMORE_P(ret)      ONIGENC_MBCLEN_NEEDMORE_P(ret)
#define MBCLEN_NEEDMORE_LEN(ret)      ONIGENC_MBCLEN_NEEDMORE_LEN(ret)

/* -> 0x00..0x7f, -1 */
int rb_enc_ascget(const char *p, const char *e, int *len, rb_encoding *enc);

/* -> code or raise exception */
int rb_enc_codepoint(const char *p, const char *e, rb_encoding *enc);
#define rb_enc_mbc_to_codepoint(p, e, enc) ONIGENC_MBC_TO_CODE(enc,(UChar*)(p),(UChar*)(e))

/* -> codelen>0 or raise exception */
int rb_enc_codelen(int code, rb_encoding *enc);

/* code,ptr,encoding -> write buf */
#define rb_enc_mbcput(c,buf,enc) ONIGENC_CODE_TO_MBC(enc,c,(UChar*)(buf))

/* ptr, ptr, encoding -> prev_char */
#define rb_enc_prev_char(s,p,enc) (char *)onigenc_get_prev_char_head(enc,(UChar*)(s),(UChar*)(p))
/* ptr, ptr, encoding -> next_char */
#define rb_enc_left_char_head(s,p,enc) (char *)onigenc_get_left_adjust_char_head(enc,(UChar*)(s),(UChar*)(p))
#define rb_enc_right_char_head(s,p,enc) (char *)onigenc_get_right_adjust_char_head(enc,(UChar*)(s),(UChar*)(p))

/* ptr, ptr, encoding -> newline_or_not */
#define rb_enc_is_newline(p,end,enc)  ONIGENC_IS_MBC_NEWLINE(enc,(UChar*)(p),(UChar*)(end))

#if WITH_OBJC
#define rb_enc_isctype(c,t,enc)	(iswctype(c,t))
#define rb_enc_isascii(c,enc)	(iswascii(c))
#define rb_enc_isalpha(c,enc)	(iswalpha(c))
#define rb_enc_islower(c,enc)	(iswlower(c))
#define rb_enc_isupper(c,enc)	(iswupper(c))
#define rb_enc_isalnum(c,enc)	(iswalnum(c))
#define rb_enc_isprint(c,enc)	(iswprint(c))
#define rb_enc_isspace(c,enc)	(iswspace(c))
#define rb_enc_isdigit(c,enc)	(iswdigit(c))
#else
#define rb_enc_isctype(c,t,enc) ONIGENC_IS_CODE_CTYPE(enc,c,t)
#define rb_enc_isascii(c,enc) ONIGENC_IS_CODE_ASCII(c)
#define rb_enc_isalpha(c,enc) ONIGENC_IS_CODE_ALPHA(enc,c)
#define rb_enc_islower(c,enc) ONIGENC_IS_CODE_LOWER(enc,c)
#define rb_enc_isupper(c,enc) ONIGENC_IS_CODE_UPPER(enc,c)
#define rb_enc_isalnum(c,enc) ONIGENC_IS_CODE_ALNUM(enc,c)
#define rb_enc_isprint(c,enc) ONIGENC_IS_CODE_PRINT(enc,c)
#define rb_enc_isspace(c,enc) ONIGENC_IS_CODE_SPACE(enc,c)
#define rb_enc_isdigit(c,enc) ONIGENC_IS_CODE_DIGIT(enc,c)
#endif

#define rb_enc_asciicompat(enc) (rb_enc_mbminlen(enc)==1 && !rb_enc_dummy_p(enc))

int rb_enc_casefold(char *to, const char *p, const char *e, rb_encoding *enc);
int rb_enc_toupper(int c, rb_encoding *enc);
int rb_enc_tolower(int c, rb_encoding *enc);
ID rb_intern3(const char*, long, rb_encoding*);
ID rb_interned_id_p(const char *, long, rb_encoding *);
int rb_enc_symname_p(const char*, rb_encoding*);
int rb_enc_str_coderange(VALUE);
long rb_str_coderange_scan_restartable(const char*, const char*, rb_encoding*, int*);
int rb_enc_str_asciionly_p(VALUE);
#define rb_enc_str_asciicompat_p(str) rb_enc_asciicompat(rb_enc_get(str))
VALUE rb_enc_from_encoding(rb_encoding *enc);
rb_encoding *rb_ascii8bit_encoding(void);
rb_encoding *rb_utf8_encoding(void);
rb_encoding *rb_usascii_encoding(void);
rb_encoding *rb_locale_encoding(void);
rb_encoding *rb_default_external_encoding(void);
int rb_usascii_encindex(void);
int rb_ascii8bit_encindex(void);
VALUE rb_enc_default_external(void);
void rb_enc_set_default_external(VALUE encoding);
//VALUE rb_locale_charmap(VALUE klass);
long rb_memsearch(const void*,long,const void*,long,rb_encoding*);

RUBY_EXTERN VALUE rb_cEncoding;

#define ENC_UNINITIALIZED (&rb_cEncoding)
#define enc_initialized_p(enc) ((enc)->auxiliary_data != &rb_cEncoding)
#define ENC_FROM_ENCODING(enc) ((VALUE)(enc)->auxiliary_data)

#define ENC_DUMMY_FLAG FL_USER2
#define ENC_DUMMY_P(enc) (RBASIC(enc)->flags & ENC_DUMMY_FLAG)
#define ENC_SET_DUMMY(enc) (RBASIC(enc)->flags |= ENC_DUMMY_FLAG)

#if WITH_OBJC
# define rb_enc_dummy_p(x) (Qfalse)
#else
static inline int
rb_enc_dummy_p(rb_encoding *enc)
{
    if (!enc_initialized_p(enc)) return Qfalse;
    return ENC_DUMMY_P(ENC_FROM_ENCODING(enc));
}
#endif

VALUE rb_str_transcode(VALUE str, VALUE to);

#endif /* RUBY_ENCODING_H */
