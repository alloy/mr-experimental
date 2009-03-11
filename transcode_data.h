/**********************************************************************

  transcode_data.h -

  $Author: nobu $
  created at: Mon 10 Dec 2007 14:01:47 JST 2007

  Copyright (C) 2007 Martin Duerst

**********************************************************************/

#include "ruby/ruby.h"

#ifndef RUBY_TRANSCODE_DATA_H
#define RUBY_TRANSCODE_DATA_H 1

typedef unsigned char base_element;

typedef struct byte_lookup {
    const base_element *base;
    const struct byte_lookup *const *info;
} BYTE_LOOKUP;

#ifndef PType
/* data file needs to treat this as a pointer, to remove warnings */
#define PType (const BYTE_LOOKUP *)
#endif

#define NOMAP	(PType 0x01)	/* single byte direct map */
#define ONEbt	(0x02)		/* one byte payload */
#define TWObt	(0x03)		/* two bytes payload */
#define THREEbt	(0x05)		/* three bytes payload */
#define FOURbt	(0x06)		/* four bytes payload, UTF-8 only, macros start at getBT0 */
#define INVALID	(PType 0x07)	/* invalid byte sequence */
#define UNDEF	(PType 0x09)	/* legal but undefined */
#define ZERObt	(PType 0x0A)	/* zero bytes of payload, i.e. remove */
#define FUNii	(PType 0x0B)	/* function from info to info */
#define FUNsi	(PType 0x0D)	/* function from start to info */
#define FUNio	(PType 0x0E)	/* function from info to output */
#define FUNso	(PType 0x0F)	/* function from start to output */

#define o1(b1)		(PType((((unsigned char)(b1))<<8)|ONEbt))
#define o2(b1,b2)	(PType((((unsigned char)(b1))<<8)|(((unsigned char)(b2))<<16)|TWObt))
#define o3(b1,b2,b3)	(PType((((unsigned char)(b1))<<8)|(((unsigned char)(b2))<<16)|(((unsigned char)(b3))<<24)|THREEbt))
#define o4(b0,b1,b2,b3)	(PType((((unsigned char)(b1))<< 8)|(((unsigned char)(b2))<<16)|(((unsigned char)(b3))<<24)|((((unsigned char)(b0))&0x07)<<5)|FOURbt))

#define getBT1(a)	(((a)>> 8)&0xFF)
#define getBT2(a)	(((a)>>16)&0xFF)
#define getBT3(a)	(((a)>>24)&0xFF)
#define getBT0(a)	((((a)>> 5)&0x07)|0xF0)   /* for UTF-8 only!!! */

#define o2FUNii(b1,b2)	(PType((((unsigned char)(b1))<<8)|(((unsigned char)(b2))<<16)|FUNii))

/* do we need these??? maybe not, can be done with simple tables */
#define ONETRAIL       /* legal but undefined if one more trailing UTF-8 */
#define TWOTRAIL       /* legal but undefined if two more trailing UTF-8 */
#define THREETRAIL     /* legal but undefined if three more trailing UTF-8 */

/* dynamic structure, one per conversion (similar to iconv_t) */
/* may carry conversion state (e.g. for iso-2022-jp) */
typedef struct rb_transcoding {
    const struct rb_transcoder *transcoder;
    VALUE ruby_string_dest; /* the String used as the conversion destination,
			       or NULL if something else is being converted */
    unsigned char *(*flush_func)(struct rb_transcoding*, int, int);
} rb_transcoding;

/* static structure, one per supported encoding pair */
typedef struct rb_transcoder {
    const char *from_encoding;
    const char *to_encoding;
    const BYTE_LOOKUP *conv_tree_start;
    int max_output;
    int from_utf8;
    void (*preprocessor)(unsigned char**, unsigned char**, unsigned char*, unsigned char*, struct rb_transcoding *);
    void (*postprocessor)(unsigned char**, unsigned char**, unsigned char*, unsigned char*, struct rb_transcoding *);
    VALUE (*func_ii)(VALUE); /* info  -> info   */
    VALUE (*func_si)(const unsigned char *); /* start -> info   */
    int (*func_io)(VALUE, const unsigned char*); /* info  -> output */
    int (*func_so)(const unsigned char*, unsigned char*); /* start -> output */
} rb_transcoder;

void rb_declare_transcoder(const char *enc1, const char *enc2, const char *lib);
void rb_register_transcoder(const rb_transcoder *);

#endif /* RUBY_TRANSCODE_DATA_H */
