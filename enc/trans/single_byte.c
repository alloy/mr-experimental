#include "transcode_data.h"

static const unsigned char
from_US_ASCII_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
from_US_ASCII_infos[2] = {
     NOMAP, UNDEF,
};
static const BYTE_LOOKUP
from_US_ASCII = {
  /* used from from_US_ASCII */
  /* used from to_US_ASCII */
  /* used from to_ASCII_8BIT */
  /* used from from_ASCII_8BIT */
    from_US_ASCII_offsets,
    from_US_ASCII_infos
};

static const rb_transcoder
rb_from_US_ASCII = {
    "US-ASCII", "UTF-8", &from_US_ASCII, 1, 0,
    NULL, NULL,
};

static const rb_transcoder
rb_to_US_ASCII = {
    "UTF-8", "US-ASCII", &from_US_ASCII, 1, 1,
    NULL, NULL,
};

static const rb_transcoder
rb_from_ASCII_8BIT = {
    "ASCII-8BIT", "UTF-8", &from_US_ASCII, 1, 0,
    NULL, NULL,
};

static const rb_transcoder
rb_to_ASCII_8BIT = {
    "UTF-8", "ASCII-8BIT", &from_US_ASCII, 1, 1,
    NULL, NULL,
};

static const unsigned char
from_ISO_8859_1_offsets[256] = {
  /* used from from_ISO_8859_1 */
  /* used from from_ISO_8859_2 */
  /* used from from_ISO_8859_4 */
  /* used from from_ISO_8859_5 */
  /* used from from_ISO_8859_9 */
  /* used from from_ISO_8859_10 */
  /* used from from_ISO_8859_13 */
  /* used from from_ISO_8859_14 */
  /* used from from_ISO_8859_15 */
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      1,  2,  3,  4,  5,  6,  7,  8,    9, 10, 11, 12, 13, 14, 15, 16,
     17, 18, 19, 20, 21, 22, 23, 24,   25, 26, 27, 28, 29, 30, 31, 32,
     33, 34, 35, 36, 37, 38, 39, 40,   41, 42, 43, 44, 45, 46, 47, 48,
     49, 50, 51, 52, 53, 54, 55, 56,   57, 58, 59, 60, 61, 62, 63, 64,
     65, 66, 67, 68, 69, 70, 71, 72,   73, 74, 75, 76, 77, 78, 79, 80,
     81, 82, 83, 84, 85, 86, 87, 88,   89, 90, 91, 92, 93, 94, 95, 96,
     97, 98, 99,100,101,102,103,104,  105,106,107,108,109,110,111,112,
    113,114,115,116,117,118,119,120,  121,122,123,124,125,126,127,128,
};
static const struct byte_lookup* const
from_ISO_8859_1_infos[129] = {
             NOMAP, o2(0xC2,0x80), o2(0xC2,0x81), o2(0xC2,0x82),
     o2(0xC2,0x83), o2(0xC2,0x84), o2(0xC2,0x85), o2(0xC2,0x86),
     o2(0xC2,0x87), o2(0xC2,0x88), o2(0xC2,0x89), o2(0xC2,0x8A),
     o2(0xC2,0x8B), o2(0xC2,0x8C), o2(0xC2,0x8D), o2(0xC2,0x8E),
     o2(0xC2,0x8F), o2(0xC2,0x90), o2(0xC2,0x91), o2(0xC2,0x92),
     o2(0xC2,0x93), o2(0xC2,0x94), o2(0xC2,0x95), o2(0xC2,0x96),
     o2(0xC2,0x97), o2(0xC2,0x98), o2(0xC2,0x99), o2(0xC2,0x9A),
     o2(0xC2,0x9B), o2(0xC2,0x9C), o2(0xC2,0x9D), o2(0xC2,0x9E),
     o2(0xC2,0x9F), o2(0xC2,0xA0), o2(0xC2,0xA1), o2(0xC2,0xA2),
     o2(0xC2,0xA3), o2(0xC2,0xA4), o2(0xC2,0xA5), o2(0xC2,0xA6),
     o2(0xC2,0xA7), o2(0xC2,0xA8), o2(0xC2,0xA9), o2(0xC2,0xAA),
     o2(0xC2,0xAB), o2(0xC2,0xAC), o2(0xC2,0xAD), o2(0xC2,0xAE),
     o2(0xC2,0xAF), o2(0xC2,0xB0), o2(0xC2,0xB1), o2(0xC2,0xB2),
     o2(0xC2,0xB3), o2(0xC2,0xB4), o2(0xC2,0xB5), o2(0xC2,0xB6),
     o2(0xC2,0xB7), o2(0xC2,0xB8), o2(0xC2,0xB9), o2(0xC2,0xBA),
     o2(0xC2,0xBB), o2(0xC2,0xBC), o2(0xC2,0xBD), o2(0xC2,0xBE),
     o2(0xC2,0xBF), o2(0xC3,0x80), o2(0xC3,0x81), o2(0xC3,0x82),
     o2(0xC3,0x83), o2(0xC3,0x84), o2(0xC3,0x85), o2(0xC3,0x86),
     o2(0xC3,0x87), o2(0xC3,0x88), o2(0xC3,0x89), o2(0xC3,0x8A),
     o2(0xC3,0x8B), o2(0xC3,0x8C), o2(0xC3,0x8D), o2(0xC3,0x8E),
     o2(0xC3,0x8F), o2(0xC3,0x90), o2(0xC3,0x91), o2(0xC3,0x92),
     o2(0xC3,0x93), o2(0xC3,0x94), o2(0xC3,0x95), o2(0xC3,0x96),
     o2(0xC3,0x97), o2(0xC3,0x98), o2(0xC3,0x99), o2(0xC3,0x9A),
     o2(0xC3,0x9B), o2(0xC3,0x9C), o2(0xC3,0x9D), o2(0xC3,0x9E),
     o2(0xC3,0x9F), o2(0xC3,0xA0), o2(0xC3,0xA1), o2(0xC3,0xA2),
     o2(0xC3,0xA3), o2(0xC3,0xA4), o2(0xC3,0xA5), o2(0xC3,0xA6),
     o2(0xC3,0xA7), o2(0xC3,0xA8), o2(0xC3,0xA9), o2(0xC3,0xAA),
     o2(0xC3,0xAB), o2(0xC3,0xAC), o2(0xC3,0xAD), o2(0xC3,0xAE),
     o2(0xC3,0xAF), o2(0xC3,0xB0), o2(0xC3,0xB1), o2(0xC3,0xB2),
     o2(0xC3,0xB3), o2(0xC3,0xB4), o2(0xC3,0xB5), o2(0xC3,0xB6),
     o2(0xC3,0xB7), o2(0xC3,0xB8), o2(0xC3,0xB9), o2(0xC3,0xBA),
     o2(0xC3,0xBB), o2(0xC3,0xBC), o2(0xC3,0xBD), o2(0xC3,0xBE),
     o2(0xC3,0xBF),
};
static const BYTE_LOOKUP
from_ISO_8859_1 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_1_infos
};

static const rb_transcoder
rb_from_ISO_8859_1 = {
    "ISO-8859-1", "UTF-8", &from_ISO_8859_1, 2, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_1_C2_offsets[64] = {
  /* used from to_ISO_8859_1_C2 */
  /* used from to_ISO_8859_1_C3 */
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 34, 35, 36, 37, 38, 39,   40, 41, 42, 43, 44, 45, 46, 47,
     48, 49, 50, 51, 52, 53, 54, 55,   56, 57, 58, 59, 60, 61, 62, 63,
};
static const struct byte_lookup* const
to_ISO_8859_1_C2_infos[64] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA1), o1(0xA2), o1(0xA3),
     o1(0xA4), o1(0xA5), o1(0xA6), o1(0xA7),
     o1(0xA8), o1(0xA9), o1(0xAA), o1(0xAB),
     o1(0xAC), o1(0xAD), o1(0xAE), o1(0xAF),
     o1(0xB0), o1(0xB1), o1(0xB2), o1(0xB3),
     o1(0xB4), o1(0xB5), o1(0xB6), o1(0xB7),
     o1(0xB8), o1(0xB9), o1(0xBA), o1(0xBB),
     o1(0xBC), o1(0xBD), o1(0xBE), o1(0xBF),
};
static const BYTE_LOOKUP
to_ISO_8859_1_C2 = {
  /* used from to_ISO_8859_1 */
  /* used from to_ISO_8859_9 */
    to_ISO_8859_1_C2_offsets,
    to_ISO_8859_1_C2_infos
};

static const struct byte_lookup* const
to_ISO_8859_1_C3_infos[64] = {
     o1(0xC0), o1(0xC1), o1(0xC2), o1(0xC3),
     o1(0xC4), o1(0xC5), o1(0xC6), o1(0xC7),
     o1(0xC8), o1(0xC9), o1(0xCA), o1(0xCB),
     o1(0xCC), o1(0xCD), o1(0xCE), o1(0xCF),
     o1(0xD0), o1(0xD1), o1(0xD2), o1(0xD3),
     o1(0xD4), o1(0xD5), o1(0xD6), o1(0xD7),
     o1(0xD8), o1(0xD9), o1(0xDA), o1(0xDB),
     o1(0xDC), o1(0xDD), o1(0xDE), o1(0xDF),
     o1(0xE0), o1(0xE1), o1(0xE2), o1(0xE3),
     o1(0xE4), o1(0xE5), o1(0xE6), o1(0xE7),
     o1(0xE8), o1(0xE9), o1(0xEA), o1(0xEB),
     o1(0xEC), o1(0xED), o1(0xEE), o1(0xEF),
     o1(0xF0), o1(0xF1), o1(0xF2), o1(0xF3),
     o1(0xF4), o1(0xF5), o1(0xF6), o1(0xF7),
     o1(0xF8), o1(0xF9), o1(0xFA), o1(0xFB),
     o1(0xFC), o1(0xFD), o1(0xFE), o1(0xFF),
};
static const BYTE_LOOKUP
to_ISO_8859_1_C3 = {
  /* used from to_ISO_8859_1 */
  /* used from to_ISO_8859_15 */
    to_ISO_8859_1_C2_offsets,
    to_ISO_8859_1_C3_infos
};

static const unsigned char
to_ISO_8859_1_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  1,  2,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
};
static const struct byte_lookup* const
to_ISO_8859_1_infos[4] = {
                 NOMAP, &to_ISO_8859_1_C2,
     &to_ISO_8859_1_C3,             UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_1 = {
    to_ISO_8859_1_offsets,
    to_ISO_8859_1_infos
};

static const rb_transcoder
rb_to_ISO_8859_1 = {
    "UTF-8", "ISO-8859-1", &to_ISO_8859_1, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_2_infos[129] = {
             NOMAP, o2(0xC2,0x80), o2(0xC2,0x81), o2(0xC2,0x82),
     o2(0xC2,0x83), o2(0xC2,0x84), o2(0xC2,0x85), o2(0xC2,0x86),
     o2(0xC2,0x87), o2(0xC2,0x88), o2(0xC2,0x89), o2(0xC2,0x8A),
     o2(0xC2,0x8B), o2(0xC2,0x8C), o2(0xC2,0x8D), o2(0xC2,0x8E),
     o2(0xC2,0x8F), o2(0xC2,0x90), o2(0xC2,0x91), o2(0xC2,0x92),
     o2(0xC2,0x93), o2(0xC2,0x94), o2(0xC2,0x95), o2(0xC2,0x96),
     o2(0xC2,0x97), o2(0xC2,0x98), o2(0xC2,0x99), o2(0xC2,0x9A),
     o2(0xC2,0x9B), o2(0xC2,0x9C), o2(0xC2,0x9D), o2(0xC2,0x9E),
     o2(0xC2,0x9F), o2(0xC2,0xA0), o2(0xC4,0x84), o2(0xCB,0x98),
     o2(0xC5,0x81), o2(0xC2,0xA4), o2(0xC4,0xBD), o2(0xC5,0x9A),
     o2(0xC2,0xA7), o2(0xC2,0xA8), o2(0xC5,0xA0), o2(0xC5,0x9E),
     o2(0xC5,0xA4), o2(0xC5,0xB9), o2(0xC2,0xAD), o2(0xC5,0xBD),
     o2(0xC5,0xBB), o2(0xC2,0xB0), o2(0xC4,0x85), o2(0xCB,0x9B),
     o2(0xC5,0x82), o2(0xC2,0xB4), o2(0xC4,0xBE), o2(0xC5,0x9B),
     o2(0xCB,0x87), o2(0xC2,0xB8), o2(0xC5,0xA1), o2(0xC5,0x9F),
     o2(0xC5,0xA5), o2(0xC5,0xBA), o2(0xCB,0x9D), o2(0xC5,0xBE),
     o2(0xC5,0xBC), o2(0xC5,0x94), o2(0xC3,0x81), o2(0xC3,0x82),
     o2(0xC4,0x82), o2(0xC3,0x84), o2(0xC4,0xB9), o2(0xC4,0x86),
     o2(0xC3,0x87), o2(0xC4,0x8C), o2(0xC3,0x89), o2(0xC4,0x98),
     o2(0xC3,0x8B), o2(0xC4,0x9A), o2(0xC3,0x8D), o2(0xC3,0x8E),
     o2(0xC4,0x8E), o2(0xC4,0x90), o2(0xC5,0x83), o2(0xC5,0x87),
     o2(0xC3,0x93), o2(0xC3,0x94), o2(0xC5,0x90), o2(0xC3,0x96),
     o2(0xC3,0x97), o2(0xC5,0x98), o2(0xC5,0xAE), o2(0xC3,0x9A),
     o2(0xC5,0xB0), o2(0xC3,0x9C), o2(0xC3,0x9D), o2(0xC5,0xA2),
     o2(0xC3,0x9F), o2(0xC5,0x95), o2(0xC3,0xA1), o2(0xC3,0xA2),
     o2(0xC4,0x83), o2(0xC3,0xA4), o2(0xC4,0xBA), o2(0xC4,0x87),
     o2(0xC3,0xA7), o2(0xC4,0x8D), o2(0xC3,0xA9), o2(0xC4,0x99),
     o2(0xC3,0xAB), o2(0xC4,0x9B), o2(0xC3,0xAD), o2(0xC3,0xAE),
     o2(0xC4,0x8F), o2(0xC4,0x91), o2(0xC5,0x84), o2(0xC5,0x88),
     o2(0xC3,0xB3), o2(0xC3,0xB4), o2(0xC5,0x91), o2(0xC3,0xB6),
     o2(0xC3,0xB7), o2(0xC5,0x99), o2(0xC5,0xAF), o2(0xC3,0xBA),
     o2(0xC5,0xB1), o2(0xC3,0xBC), o2(0xC3,0xBD), o2(0xC5,0xA3),
     o2(0xCB,0x99),
};
static const BYTE_LOOKUP
from_ISO_8859_2 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_2_infos
};

static const rb_transcoder
rb_from_ISO_8859_2 = {
    "ISO-8859-2", "UTF-8", &from_ISO_8859_2, 2, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_2_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 40, 40, 40, 33, 40, 40, 34,   35, 40, 40, 40, 40, 36, 40, 40,
     37, 40, 40, 40, 38, 40, 40, 40,   39, 40, 40, 40, 40, 40, 40, 40,
};
static const struct byte_lookup* const
to_ISO_8859_2_C2_infos[41] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA4), o1(0xA7), o1(0xA8),
     o1(0xAD), o1(0xB0), o1(0xB4), o1(0xB8),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_2_C2 = {
    to_ISO_8859_2_C2_offsets,
    to_ISO_8859_2_C2_infos
};

static const unsigned char
to_ISO_8859_2_C3_offsets[64] = {
     31,  0,  1, 31,  2, 31, 31,  3,   31,  4, 31,  5, 31,  6,  7, 31,
     31, 31, 31,  8,  9, 31, 10, 11,   31, 31, 12, 31, 13, 14, 31, 15,
     31, 16, 17, 31, 18, 31, 31, 19,   31, 20, 31, 21, 31, 22, 23, 31,
     31, 31, 31, 24, 25, 31, 26, 27,   31, 31, 28, 31, 29, 30, 31, 31,
};
static const struct byte_lookup* const
to_ISO_8859_2_C3_infos[32] = {
     o1(0xC1), o1(0xC2), o1(0xC4), o1(0xC7),
     o1(0xC9), o1(0xCB), o1(0xCD), o1(0xCE),
     o1(0xD3), o1(0xD4), o1(0xD6), o1(0xD7),
     o1(0xDA), o1(0xDC), o1(0xDD), o1(0xDF),
     o1(0xE1), o1(0xE2), o1(0xE4), o1(0xE7),
     o1(0xE9), o1(0xEB), o1(0xED), o1(0xEE),
     o1(0xF3), o1(0xF4), o1(0xF6), o1(0xF7),
     o1(0xFA), o1(0xFC), o1(0xFD),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_2_C3 = {
    to_ISO_8859_2_C3_offsets,
    to_ISO_8859_2_C3_infos
};

static const unsigned char
to_ISO_8859_2_C4_offsets[64] = {
     20, 20,  0,  1,  2,  3,  4,  5,   20, 20, 20, 20,  6,  7,  8,  9,
     10, 11, 20, 20, 20, 20, 20, 20,   12, 13, 14, 15, 20, 20, 20, 20,
     20, 20, 20, 20, 20, 20, 20, 20,   20, 20, 20, 20, 20, 20, 20, 20,
     20, 20, 20, 20, 20, 20, 20, 20,   20, 16, 17, 20, 20, 18, 19, 20,
};
static const struct byte_lookup* const
to_ISO_8859_2_C4_infos[21] = {
     o1(0xC3), o1(0xE3), o1(0xA1), o1(0xB1),
     o1(0xC6), o1(0xE6), o1(0xC8), o1(0xE8),
     o1(0xCF), o1(0xEF), o1(0xD0), o1(0xF0),
     o1(0xCA), o1(0xEA), o1(0xCC), o1(0xEC),
     o1(0xC5), o1(0xE5), o1(0xA5), o1(0xB5),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_2_C4 = {
    to_ISO_8859_2_C4_offsets,
    to_ISO_8859_2_C4_infos
};

static const unsigned char
to_ISO_8859_2_C5_offsets[64] = {
     32,  0,  1,  2,  3, 32, 32,  4,    5, 32, 32, 32, 32, 32, 32, 32,
      6,  7, 32, 32,  8,  9, 32, 32,   10, 11, 12, 13, 32, 32, 14, 15,
     16, 17, 18, 19, 20, 21, 32, 32,   32, 32, 32, 32, 32, 32, 22, 23,
     24, 25, 32, 32, 32, 32, 32, 32,   32, 26, 27, 28, 29, 30, 31, 32,
};
static const struct byte_lookup* const
to_ISO_8859_2_C5_infos[33] = {
     o1(0xA3), o1(0xB3), o1(0xD1), o1(0xF1),
     o1(0xD2), o1(0xF2), o1(0xD5), o1(0xF5),
     o1(0xC0), o1(0xE0), o1(0xD8), o1(0xF8),
     o1(0xA6), o1(0xB6), o1(0xAA), o1(0xBA),
     o1(0xA9), o1(0xB9), o1(0xDE), o1(0xFE),
     o1(0xAB), o1(0xBB), o1(0xD9), o1(0xF9),
     o1(0xDB), o1(0xFB), o1(0xAC), o1(0xBC),
     o1(0xAF), o1(0xBF), o1(0xAE), o1(0xBE),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_2_C5 = {
    to_ISO_8859_2_C5_offsets,
    to_ISO_8859_2_C5_infos
};

static const unsigned char
to_ISO_8859_2_CB_offsets[64] = {
      5,  5,  5,  5,  5,  5,  5,  0,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    1,  2,  5,  3,  5,  4,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
};
static const struct byte_lookup* const
to_ISO_8859_2_CB_infos[6] = {
     o1(0xB7), o1(0xA2), o1(0xFF), o1(0xB2),
     o1(0xBD),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_2_CB = {
    to_ISO_8859_2_CB_offsets,
    to_ISO_8859_2_CB_infos
};

static const unsigned char
to_ISO_8859_2_offsets[256] = {
  /* used from to_ISO_8859_2 */
  /* used from to_ISO_8859_3 */
  /* used from to_ISO_8859_4 */
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  1,  2,  3,  4,  6,  6,    6,  6,  6,  5,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
};
static const struct byte_lookup* const
to_ISO_8859_2_infos[7] = {
                 NOMAP, &to_ISO_8859_2_C2,
     &to_ISO_8859_2_C3, &to_ISO_8859_2_C4,
     &to_ISO_8859_2_C5, &to_ISO_8859_2_CB,
                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_2 = {
    to_ISO_8859_2_offsets,
    to_ISO_8859_2_infos
};

static const rb_transcoder
rb_to_ISO_8859_2 = {
    "UTF-8", "ISO-8859-2", &to_ISO_8859_2, 1, 1,
    NULL, NULL,
};

static const unsigned char
from_ISO_8859_3_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      1,  2,  3,  4,  5,  6,  7,  8,    9, 10, 11, 12, 13, 14, 15, 16,
     17, 18, 19, 20, 21, 22, 23, 24,   25, 26, 27, 28, 29, 30, 31, 32,
     33, 34, 35, 36, 37,122, 38, 39,   40, 41, 42, 43, 44, 45,122, 46,
     47, 48, 49, 50, 51, 52, 53, 54,   55, 56, 57, 58, 59, 60,122, 61,
     62, 63, 64,122, 65, 66, 67, 68,   69, 70, 71, 72, 73, 74, 75, 76,
    122, 77, 78, 79, 80, 81, 82, 83,   84, 85, 86, 87, 88, 89, 90, 91,
     92, 93, 94,122, 95, 96, 97, 98,   99,100,101,102,103,104,105,106,
    122,107,108,109,110,111,112,113,  114,115,116,117,118,119,120,121,
};
static const struct byte_lookup* const
from_ISO_8859_3_infos[123] = {
             NOMAP, o2(0xC2,0x80), o2(0xC2,0x81), o2(0xC2,0x82),
     o2(0xC2,0x83), o2(0xC2,0x84), o2(0xC2,0x85), o2(0xC2,0x86),
     o2(0xC2,0x87), o2(0xC2,0x88), o2(0xC2,0x89), o2(0xC2,0x8A),
     o2(0xC2,0x8B), o2(0xC2,0x8C), o2(0xC2,0x8D), o2(0xC2,0x8E),
     o2(0xC2,0x8F), o2(0xC2,0x90), o2(0xC2,0x91), o2(0xC2,0x92),
     o2(0xC2,0x93), o2(0xC2,0x94), o2(0xC2,0x95), o2(0xC2,0x96),
     o2(0xC2,0x97), o2(0xC2,0x98), o2(0xC2,0x99), o2(0xC2,0x9A),
     o2(0xC2,0x9B), o2(0xC2,0x9C), o2(0xC2,0x9D), o2(0xC2,0x9E),
     o2(0xC2,0x9F), o2(0xC2,0xA0), o2(0xC4,0xA6), o2(0xCB,0x98),
     o2(0xC2,0xA3), o2(0xC2,0xA4), o2(0xC4,0xA4), o2(0xC2,0xA7),
     o2(0xC2,0xA8), o2(0xC4,0xB0), o2(0xC5,0x9E), o2(0xC4,0x9E),
     o2(0xC4,0xB4), o2(0xC2,0xAD), o2(0xC5,0xBB), o2(0xC2,0xB0),
     o2(0xC4,0xA7), o2(0xC2,0xB2), o2(0xC2,0xB3), o2(0xC2,0xB4),
     o2(0xC2,0xB5), o2(0xC4,0xA5), o2(0xC2,0xB7), o2(0xC2,0xB8),
     o2(0xC4,0xB1), o2(0xC5,0x9F), o2(0xC4,0x9F), o2(0xC4,0xB5),
     o2(0xC2,0xBD), o2(0xC5,0xBC), o2(0xC3,0x80), o2(0xC3,0x81),
     o2(0xC3,0x82), o2(0xC3,0x84), o2(0xC4,0x8A), o2(0xC4,0x88),
     o2(0xC3,0x87), o2(0xC3,0x88), o2(0xC3,0x89), o2(0xC3,0x8A),
     o2(0xC3,0x8B), o2(0xC3,0x8C), o2(0xC3,0x8D), o2(0xC3,0x8E),
     o2(0xC3,0x8F), o2(0xC3,0x91), o2(0xC3,0x92), o2(0xC3,0x93),
     o2(0xC3,0x94), o2(0xC4,0xA0), o2(0xC3,0x96), o2(0xC3,0x97),
     o2(0xC4,0x9C), o2(0xC3,0x99), o2(0xC3,0x9A), o2(0xC3,0x9B),
     o2(0xC3,0x9C), o2(0xC5,0xAC), o2(0xC5,0x9C), o2(0xC3,0x9F),
     o2(0xC3,0xA0), o2(0xC3,0xA1), o2(0xC3,0xA2), o2(0xC3,0xA4),
     o2(0xC4,0x8B), o2(0xC4,0x89), o2(0xC3,0xA7), o2(0xC3,0xA8),
     o2(0xC3,0xA9), o2(0xC3,0xAA), o2(0xC3,0xAB), o2(0xC3,0xAC),
     o2(0xC3,0xAD), o2(0xC3,0xAE), o2(0xC3,0xAF), o2(0xC3,0xB1),
     o2(0xC3,0xB2), o2(0xC3,0xB3), o2(0xC3,0xB4), o2(0xC4,0xA1),
     o2(0xC3,0xB6), o2(0xC3,0xB7), o2(0xC4,0x9D), o2(0xC3,0xB9),
     o2(0xC3,0xBA), o2(0xC3,0xBB), o2(0xC3,0xBC), o2(0xC5,0xAD),
     o2(0xC5,0x9D), o2(0xCB,0x99),         UNDEF,
};
static const BYTE_LOOKUP
from_ISO_8859_3 = {
    from_ISO_8859_3_offsets,
    from_ISO_8859_3_infos
};

static const rb_transcoder
rb_from_ISO_8859_3 = {
    "ISO-8859-3", "UTF-8", &from_ISO_8859_3, 2, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_3_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 46, 46, 33, 34, 46, 46, 35,   36, 46, 46, 46, 46, 37, 46, 46,
     38, 46, 39, 40, 41, 42, 46, 43,   44, 46, 46, 46, 46, 45, 46, 46,
};
static const struct byte_lookup* const
to_ISO_8859_3_C2_infos[47] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA3), o1(0xA4), o1(0xA7),
     o1(0xA8), o1(0xAD), o1(0xB0), o1(0xB2),
     o1(0xB3), o1(0xB4), o1(0xB5), o1(0xB7),
     o1(0xB8), o1(0xBD),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_3_C2 = {
    to_ISO_8859_3_C2_offsets,
    to_ISO_8859_3_C2_infos
};

static const unsigned char
to_ISO_8859_3_C3_offsets[64] = {
      0,  1,  2, 47,  3, 47, 47,  4,    5,  6,  7,  8,  9, 10, 11, 12,
     47, 13, 14, 15, 16, 47, 17, 18,   47, 19, 20, 21, 22, 47, 47, 23,
     24, 25, 26, 47, 27, 47, 47, 28,   29, 30, 31, 32, 33, 34, 35, 36,
     47, 37, 38, 39, 40, 47, 41, 42,   47, 43, 44, 45, 46, 47, 47, 47,
};
static const struct byte_lookup* const
to_ISO_8859_3_C3_infos[48] = {
     o1(0xC0), o1(0xC1), o1(0xC2), o1(0xC4),
     o1(0xC7), o1(0xC8), o1(0xC9), o1(0xCA),
     o1(0xCB), o1(0xCC), o1(0xCD), o1(0xCE),
     o1(0xCF), o1(0xD1), o1(0xD2), o1(0xD3),
     o1(0xD4), o1(0xD6), o1(0xD7), o1(0xD9),
     o1(0xDA), o1(0xDB), o1(0xDC), o1(0xDF),
     o1(0xE0), o1(0xE1), o1(0xE2), o1(0xE4),
     o1(0xE7), o1(0xE8), o1(0xE9), o1(0xEA),
     o1(0xEB), o1(0xEC), o1(0xED), o1(0xEE),
     o1(0xEF), o1(0xF1), o1(0xF2), o1(0xF3),
     o1(0xF4), o1(0xF6), o1(0xF7), o1(0xF9),
     o1(0xFA), o1(0xFB), o1(0xFC),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_3_C3 = {
    to_ISO_8859_3_C3_offsets,
    to_ISO_8859_3_C3_infos
};

static const unsigned char
to_ISO_8859_3_C4_offsets[64] = {
     18, 18, 18, 18, 18, 18, 18, 18,    0,  1,  2,  3, 18, 18, 18, 18,
     18, 18, 18, 18, 18, 18, 18, 18,   18, 18, 18, 18,  4,  5,  6,  7,
      8,  9, 18, 18, 10, 11, 12, 13,   18, 18, 18, 18, 18, 18, 18, 18,
     14, 15, 18, 18, 16, 17, 18, 18,   18, 18, 18, 18, 18, 18, 18, 18,
};
static const struct byte_lookup* const
to_ISO_8859_3_C4_infos[19] = {
     o1(0xC6), o1(0xE6), o1(0xC5), o1(0xE5),
     o1(0xD8), o1(0xF8), o1(0xAB), o1(0xBB),
     o1(0xD5), o1(0xF5), o1(0xA6), o1(0xB6),
     o1(0xA1), o1(0xB1), o1(0xA9), o1(0xB9),
     o1(0xAC), o1(0xBC),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_3_C4 = {
    to_ISO_8859_3_C4_offsets,
    to_ISO_8859_3_C4_infos
};

static const unsigned char
to_ISO_8859_3_C5_offsets[64] = {
      8,  8,  8,  8,  8,  8,  8,  8,    8,  8,  8,  8,  8,  8,  8,  8,
      8,  8,  8,  8,  8,  8,  8,  8,    8,  8,  8,  8,  0,  1,  2,  3,
      8,  8,  8,  8,  8,  8,  8,  8,    8,  8,  8,  8,  4,  5,  8,  8,
      8,  8,  8,  8,  8,  8,  8,  8,    8,  8,  8,  6,  7,  8,  8,  8,
};
static const struct byte_lookup* const
to_ISO_8859_3_C5_infos[9] = {
     o1(0xDE), o1(0xFE), o1(0xAA), o1(0xBA),
     o1(0xDD), o1(0xFD), o1(0xAF), o1(0xBF),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_3_C5 = {
    to_ISO_8859_3_C5_offsets,
    to_ISO_8859_3_C5_infos
};

static const unsigned char
to_ISO_8859_3_CB_offsets[64] = {
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    0,  1,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
};
static const struct byte_lookup* const
to_ISO_8859_3_CB_infos[3] = {
     o1(0xA2), o1(0xFF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_3_CB = {
    to_ISO_8859_3_CB_offsets,
    to_ISO_8859_3_CB_infos
};

static const struct byte_lookup* const
to_ISO_8859_3_infos[7] = {
                 NOMAP, &to_ISO_8859_3_C2,
     &to_ISO_8859_3_C3, &to_ISO_8859_3_C4,
     &to_ISO_8859_3_C5, &to_ISO_8859_3_CB,
                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_3 = {
    to_ISO_8859_2_offsets,
    to_ISO_8859_3_infos
};

static const rb_transcoder
rb_to_ISO_8859_3 = {
    "UTF-8", "ISO-8859-3", &to_ISO_8859_3, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_4_infos[129] = {
             NOMAP, o2(0xC2,0x80), o2(0xC2,0x81), o2(0xC2,0x82),
     o2(0xC2,0x83), o2(0xC2,0x84), o2(0xC2,0x85), o2(0xC2,0x86),
     o2(0xC2,0x87), o2(0xC2,0x88), o2(0xC2,0x89), o2(0xC2,0x8A),
     o2(0xC2,0x8B), o2(0xC2,0x8C), o2(0xC2,0x8D), o2(0xC2,0x8E),
     o2(0xC2,0x8F), o2(0xC2,0x90), o2(0xC2,0x91), o2(0xC2,0x92),
     o2(0xC2,0x93), o2(0xC2,0x94), o2(0xC2,0x95), o2(0xC2,0x96),
     o2(0xC2,0x97), o2(0xC2,0x98), o2(0xC2,0x99), o2(0xC2,0x9A),
     o2(0xC2,0x9B), o2(0xC2,0x9C), o2(0xC2,0x9D), o2(0xC2,0x9E),
     o2(0xC2,0x9F), o2(0xC2,0xA0), o2(0xC4,0x84), o2(0xC4,0xB8),
     o2(0xC5,0x96), o2(0xC2,0xA4), o2(0xC4,0xA8), o2(0xC4,0xBB),
     o2(0xC2,0xA7), o2(0xC2,0xA8), o2(0xC5,0xA0), o2(0xC4,0x92),
     o2(0xC4,0xA2), o2(0xC5,0xA6), o2(0xC2,0xAD), o2(0xC5,0xBD),
     o2(0xC2,0xAF), o2(0xC2,0xB0), o2(0xC4,0x85), o2(0xCB,0x9B),
     o2(0xC5,0x97), o2(0xC2,0xB4), o2(0xC4,0xA9), o2(0xC4,0xBC),
     o2(0xCB,0x87), o2(0xC2,0xB8), o2(0xC5,0xA1), o2(0xC4,0x93),
     o2(0xC4,0xA3), o2(0xC5,0xA7), o2(0xC5,0x8A), o2(0xC5,0xBE),
     o2(0xC5,0x8B), o2(0xC4,0x80), o2(0xC3,0x81), o2(0xC3,0x82),
     o2(0xC3,0x83), o2(0xC3,0x84), o2(0xC3,0x85), o2(0xC3,0x86),
     o2(0xC4,0xAE), o2(0xC4,0x8C), o2(0xC3,0x89), o2(0xC4,0x98),
     o2(0xC3,0x8B), o2(0xC4,0x96), o2(0xC3,0x8D), o2(0xC3,0x8E),
     o2(0xC4,0xAA), o2(0xC4,0x90), o2(0xC5,0x85), o2(0xC5,0x8C),
     o2(0xC4,0xB6), o2(0xC3,0x94), o2(0xC3,0x95), o2(0xC3,0x96),
     o2(0xC3,0x97), o2(0xC3,0x98), o2(0xC5,0xB2), o2(0xC3,0x9A),
     o2(0xC3,0x9B), o2(0xC3,0x9C), o2(0xC5,0xA8), o2(0xC5,0xAA),
     o2(0xC3,0x9F), o2(0xC4,0x81), o2(0xC3,0xA1), o2(0xC3,0xA2),
     o2(0xC3,0xA3), o2(0xC3,0xA4), o2(0xC3,0xA5), o2(0xC3,0xA6),
     o2(0xC4,0xAF), o2(0xC4,0x8D), o2(0xC3,0xA9), o2(0xC4,0x99),
     o2(0xC3,0xAB), o2(0xC4,0x97), o2(0xC3,0xAD), o2(0xC3,0xAE),
     o2(0xC4,0xAB), o2(0xC4,0x91), o2(0xC5,0x86), o2(0xC5,0x8D),
     o2(0xC4,0xB7), o2(0xC3,0xB4), o2(0xC3,0xB5), o2(0xC3,0xB6),
     o2(0xC3,0xB7), o2(0xC3,0xB8), o2(0xC5,0xB3), o2(0xC3,0xBA),
     o2(0xC3,0xBB), o2(0xC3,0xBC), o2(0xC5,0xA9), o2(0xC5,0xAB),
     o2(0xCB,0x99),
};
static const BYTE_LOOKUP
from_ISO_8859_4 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_4_infos
};

static const rb_transcoder
rb_from_ISO_8859_4 = {
    "ISO-8859-4", "UTF-8", &from_ISO_8859_4, 2, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_4_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 41, 41, 41, 33, 41, 41, 34,   35, 41, 41, 41, 41, 36, 41, 37,
     38, 41, 41, 41, 39, 41, 41, 41,   40, 41, 41, 41, 41, 41, 41, 41,
};
static const struct byte_lookup* const
to_ISO_8859_4_C2_infos[42] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA4), o1(0xA7), o1(0xA8),
     o1(0xAD), o1(0xAF), o1(0xB0), o1(0xB4),
     o1(0xB8),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_4_C2 = {
    to_ISO_8859_4_C2_offsets,
    to_ISO_8859_4_C2_infos
};

static const unsigned char
to_ISO_8859_4_C3_offsets[64] = {
     37,  0,  1,  2,  3,  4,  5, 37,   37,  6, 37,  7, 37,  8,  9, 37,
     37, 37, 37, 37, 10, 11, 12, 13,   14, 37, 15, 16, 17, 37, 37, 18,
     37, 19, 20, 21, 22, 23, 24, 37,   37, 25, 37, 26, 37, 27, 28, 37,
     37, 37, 37, 37, 29, 30, 31, 32,   33, 37, 34, 35, 36, 37, 37, 37,
};
static const struct byte_lookup* const
to_ISO_8859_4_C3_infos[38] = {
     o1(0xC1), o1(0xC2), o1(0xC3), o1(0xC4),
     o1(0xC5), o1(0xC6), o1(0xC9), o1(0xCB),
     o1(0xCD), o1(0xCE), o1(0xD4), o1(0xD5),
     o1(0xD6), o1(0xD7), o1(0xD8), o1(0xDA),
     o1(0xDB), o1(0xDC), o1(0xDF), o1(0xE1),
     o1(0xE2), o1(0xE3), o1(0xE4), o1(0xE5),
     o1(0xE6), o1(0xE9), o1(0xEB), o1(0xED),
     o1(0xEE), o1(0xF4), o1(0xF5), o1(0xF6),
     o1(0xF7), o1(0xF8), o1(0xFA), o1(0xFB),
     o1(0xFC),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_4_C3 = {
    to_ISO_8859_4_C3_offsets,
    to_ISO_8859_4_C3_infos
};

static const unsigned char
to_ISO_8859_4_C4_offsets[64] = {
  /* used from to_ISO_8859_4_C4 */
  /* used from to_ISO_8859_10_C4 */
      0,  1, 27, 27,  2,  3, 27, 27,   27, 27, 27, 27,  4,  5, 27, 27,
      6,  7,  8,  9, 27, 27, 10, 11,   12, 13, 27, 27, 27, 27, 27, 27,
     27, 27, 14, 15, 27, 27, 27, 27,   16, 17, 18, 19, 27, 27, 20, 21,
     27, 27, 27, 27, 27, 27, 22, 23,   24, 27, 27, 25, 26, 27, 27, 27,
};
static const struct byte_lookup* const
to_ISO_8859_4_C4_infos[28] = {
     o1(0xC0), o1(0xE0), o1(0xA1), o1(0xB1),
     o1(0xC8), o1(0xE8), o1(0xD0), o1(0xF0),
     o1(0xAA), o1(0xBA), o1(0xCC), o1(0xEC),
     o1(0xCA), o1(0xEA), o1(0xAB), o1(0xBB),
     o1(0xA5), o1(0xB5), o1(0xCF), o1(0xEF),
     o1(0xC7), o1(0xE7), o1(0xD3), o1(0xF3),
     o1(0xA2), o1(0xA6), o1(0xB6),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_4_C4 = {
    to_ISO_8859_4_C4_offsets,
    to_ISO_8859_4_C4_infos
};

static const unsigned char
to_ISO_8859_4_C5_offsets[64] = {
     20, 20, 20, 20, 20,  0,  1, 20,   20, 20,  2,  3,  4,  5, 20, 20,
     20, 20, 20, 20, 20, 20,  6,  7,   20, 20, 20, 20, 20, 20, 20, 20,
      8,  9, 20, 20, 20, 20, 10, 11,   12, 13, 14, 15, 20, 20, 20, 20,
     20, 20, 16, 17, 20, 20, 20, 20,   20, 20, 20, 20, 20, 18, 19, 20,
};
static const struct byte_lookup* const
to_ISO_8859_4_C5_infos[21] = {
     o1(0xD1), o1(0xF1), o1(0xBD), o1(0xBF),
     o1(0xD2), o1(0xF2), o1(0xA3), o1(0xB3),
     o1(0xA9), o1(0xB9), o1(0xAC), o1(0xBC),
     o1(0xDD), o1(0xFD), o1(0xDE), o1(0xFE),
     o1(0xD9), o1(0xF9), o1(0xAE), o1(0xBE),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_4_C5 = {
    to_ISO_8859_4_C5_offsets,
    to_ISO_8859_4_C5_infos
};

static const unsigned char
to_ISO_8859_4_CB_offsets[64] = {
      3,  3,  3,  3,  3,  3,  3,  0,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  1,  3,  2,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
};
static const struct byte_lookup* const
to_ISO_8859_4_CB_infos[4] = {
     o1(0xB7), o1(0xFF), o1(0xB2),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_4_CB = {
    to_ISO_8859_4_CB_offsets,
    to_ISO_8859_4_CB_infos
};

static const struct byte_lookup* const
to_ISO_8859_4_infos[7] = {
                 NOMAP, &to_ISO_8859_4_C2,
     &to_ISO_8859_4_C3, &to_ISO_8859_4_C4,
     &to_ISO_8859_4_C5, &to_ISO_8859_4_CB,
                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_4 = {
    to_ISO_8859_2_offsets,
    to_ISO_8859_4_infos
};

static const rb_transcoder
rb_to_ISO_8859_4 = {
    "UTF-8", "ISO-8859-4", &to_ISO_8859_4, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_5_infos[129] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
          o2(0xD0,0x81),      o2(0xD0,0x82),
          o2(0xD0,0x83),      o2(0xD0,0x84),
          o2(0xD0,0x85),      o2(0xD0,0x86),
          o2(0xD0,0x87),      o2(0xD0,0x88),
          o2(0xD0,0x89),      o2(0xD0,0x8A),
          o2(0xD0,0x8B),      o2(0xD0,0x8C),
          o2(0xC2,0xAD),      o2(0xD0,0x8E),
          o2(0xD0,0x8F),      o2(0xD0,0x90),
          o2(0xD0,0x91),      o2(0xD0,0x92),
          o2(0xD0,0x93),      o2(0xD0,0x94),
          o2(0xD0,0x95),      o2(0xD0,0x96),
          o2(0xD0,0x97),      o2(0xD0,0x98),
          o2(0xD0,0x99),      o2(0xD0,0x9A),
          o2(0xD0,0x9B),      o2(0xD0,0x9C),
          o2(0xD0,0x9D),      o2(0xD0,0x9E),
          o2(0xD0,0x9F),      o2(0xD0,0xA0),
          o2(0xD0,0xA1),      o2(0xD0,0xA2),
          o2(0xD0,0xA3),      o2(0xD0,0xA4),
          o2(0xD0,0xA5),      o2(0xD0,0xA6),
          o2(0xD0,0xA7),      o2(0xD0,0xA8),
          o2(0xD0,0xA9),      o2(0xD0,0xAA),
          o2(0xD0,0xAB),      o2(0xD0,0xAC),
          o2(0xD0,0xAD),      o2(0xD0,0xAE),
          o2(0xD0,0xAF),      o2(0xD0,0xB0),
          o2(0xD0,0xB1),      o2(0xD0,0xB2),
          o2(0xD0,0xB3),      o2(0xD0,0xB4),
          o2(0xD0,0xB5),      o2(0xD0,0xB6),
          o2(0xD0,0xB7),      o2(0xD0,0xB8),
          o2(0xD0,0xB9),      o2(0xD0,0xBA),
          o2(0xD0,0xBB),      o2(0xD0,0xBC),
          o2(0xD0,0xBD),      o2(0xD0,0xBE),
          o2(0xD0,0xBF),      o2(0xD1,0x80),
          o2(0xD1,0x81),      o2(0xD1,0x82),
          o2(0xD1,0x83),      o2(0xD1,0x84),
          o2(0xD1,0x85),      o2(0xD1,0x86),
          o2(0xD1,0x87),      o2(0xD1,0x88),
          o2(0xD1,0x89),      o2(0xD1,0x8A),
          o2(0xD1,0x8B),      o2(0xD1,0x8C),
          o2(0xD1,0x8D),      o2(0xD1,0x8E),
          o2(0xD1,0x8F), o3(0xE2,0x84,0x96),
          o2(0xD1,0x91),      o2(0xD1,0x92),
          o2(0xD1,0x93),      o2(0xD1,0x94),
          o2(0xD1,0x95),      o2(0xD1,0x96),
          o2(0xD1,0x97),      o2(0xD1,0x98),
          o2(0xD1,0x99),      o2(0xD1,0x9A),
          o2(0xD1,0x9B),      o2(0xD1,0x9C),
          o2(0xC2,0xA7),      o2(0xD1,0x9E),
          o2(0xD1,0x9F),
};
static const BYTE_LOOKUP
from_ISO_8859_5 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_5_infos
};

static const rb_transcoder
rb_from_ISO_8859_5 = {
    "ISO-8859-5", "UTF-8", &from_ISO_8859_5, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_5_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 35, 35, 35, 35, 35, 35, 33,   35, 35, 35, 35, 35, 34, 35, 35,
     35, 35, 35, 35, 35, 35, 35, 35,   35, 35, 35, 35, 35, 35, 35, 35,
};
static const struct byte_lookup* const
to_ISO_8859_5_C2_infos[36] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xFD), o1(0xAD),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_5_C2 = {
    to_ISO_8859_5_C2_offsets,
    to_ISO_8859_5_C2_infos
};

static const unsigned char
to_ISO_8859_5_D0_offsets[64] = {
     62,  0,  1,  2,  3,  4,  5,  6,    7,  8,  9, 10, 11, 62, 12, 13,
     14, 15, 16, 17, 18, 19, 20, 21,   22, 23, 24, 25, 26, 27, 28, 29,
     30, 31, 32, 33, 34, 35, 36, 37,   38, 39, 40, 41, 42, 43, 44, 45,
     46, 47, 48, 49, 50, 51, 52, 53,   54, 55, 56, 57, 58, 59, 60, 61,
};
static const struct byte_lookup* const
to_ISO_8859_5_D0_infos[63] = {
     o1(0xA1), o1(0xA2), o1(0xA3), o1(0xA4),
     o1(0xA5), o1(0xA6), o1(0xA7), o1(0xA8),
     o1(0xA9), o1(0xAA), o1(0xAB), o1(0xAC),
     o1(0xAE), o1(0xAF), o1(0xB0), o1(0xB1),
     o1(0xB2), o1(0xB3), o1(0xB4), o1(0xB5),
     o1(0xB6), o1(0xB7), o1(0xB8), o1(0xB9),
     o1(0xBA), o1(0xBB), o1(0xBC), o1(0xBD),
     o1(0xBE), o1(0xBF), o1(0xC0), o1(0xC1),
     o1(0xC2), o1(0xC3), o1(0xC4), o1(0xC5),
     o1(0xC6), o1(0xC7), o1(0xC8), o1(0xC9),
     o1(0xCA), o1(0xCB), o1(0xCC), o1(0xCD),
     o1(0xCE), o1(0xCF), o1(0xD0), o1(0xD1),
     o1(0xD2), o1(0xD3), o1(0xD4), o1(0xD5),
     o1(0xD6), o1(0xD7), o1(0xD8), o1(0xD9),
     o1(0xDA), o1(0xDB), o1(0xDC), o1(0xDD),
     o1(0xDE), o1(0xDF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_5_D0 = {
    to_ISO_8859_5_D0_offsets,
    to_ISO_8859_5_D0_infos
};

static const unsigned char
to_ISO_8859_5_D1_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     30, 16, 17, 18, 19, 20, 21, 22,   23, 24, 25, 26, 27, 30, 28, 29,
     30, 30, 30, 30, 30, 30, 30, 30,   30, 30, 30, 30, 30, 30, 30, 30,
     30, 30, 30, 30, 30, 30, 30, 30,   30, 30, 30, 30, 30, 30, 30, 30,
};
static const struct byte_lookup* const
to_ISO_8859_5_D1_infos[31] = {
     o1(0xE0), o1(0xE1), o1(0xE2), o1(0xE3),
     o1(0xE4), o1(0xE5), o1(0xE6), o1(0xE7),
     o1(0xE8), o1(0xE9), o1(0xEA), o1(0xEB),
     o1(0xEC), o1(0xED), o1(0xEE), o1(0xEF),
     o1(0xF1), o1(0xF2), o1(0xF3), o1(0xF4),
     o1(0xF5), o1(0xF6), o1(0xF7), o1(0xF8),
     o1(0xF9), o1(0xFA), o1(0xFB), o1(0xFC),
     o1(0xFE), o1(0xFF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_5_D1 = {
    to_ISO_8859_5_D1_offsets,
    to_ISO_8859_5_D1_infos
};

static const unsigned char
to_ISO_8859_5_E2_84_offsets[64] = {
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  0,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
to_ISO_8859_5_E2_84_infos[2] = {
     o1(0xF0),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_5_E2_84 = {
    to_ISO_8859_5_E2_84_offsets,
    to_ISO_8859_5_E2_84_infos
};

static const unsigned char
to_ISO_8859_5_E2_offsets[64] = {
      1,  1,  1,  1,  0,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
to_ISO_8859_5_E2_infos[2] = {
     &to_ISO_8859_5_E2_84,                UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_5_E2 = {
    to_ISO_8859_5_E2_offsets,
    to_ISO_8859_5_E2_infos
};

static const unsigned char
to_ISO_8859_5_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  1,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      2,  3,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  4,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
};
static const struct byte_lookup* const
to_ISO_8859_5_infos[6] = {
                 NOMAP, &to_ISO_8859_5_C2,
     &to_ISO_8859_5_D0, &to_ISO_8859_5_D1,
     &to_ISO_8859_5_E2,             UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_5 = {
    to_ISO_8859_5_offsets,
    to_ISO_8859_5_infos
};

static const rb_transcoder
rb_to_ISO_8859_5 = {
    "UTF-8", "ISO-8859-5", &to_ISO_8859_5, 1, 1,
    NULL, NULL,
};

static const unsigned char
from_ISO_8859_6_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      1,  2,  3,  4,  5,  6,  7,  8,    9, 10, 11, 12, 13, 14, 15, 16,
     17, 18, 19, 20, 21, 22, 23, 24,   25, 26, 27, 28, 29, 30, 31, 32,
     33, 84, 84, 84, 34, 84, 84, 84,   84, 84, 84, 84, 35, 36, 84, 84,
     84, 84, 84, 84, 84, 84, 84, 84,   84, 84, 84, 37, 84, 84, 84, 38,
     84, 39, 40, 41, 42, 43, 44, 45,   46, 47, 48, 49, 50, 51, 52, 53,
     54, 55, 56, 57, 58, 59, 60, 61,   62, 63, 64, 84, 84, 84, 84, 84,
     65, 66, 67, 68, 69, 70, 71, 72,   73, 74, 75, 76, 77, 78, 79, 80,
     81, 82, 83, 84, 84, 84, 84, 84,   84, 84, 84, 84, 84, 84, 84, 84,
};
static const struct byte_lookup* const
from_ISO_8859_6_infos[85] = {
             NOMAP, o2(0xC2,0x80), o2(0xC2,0x81), o2(0xC2,0x82),
     o2(0xC2,0x83), o2(0xC2,0x84), o2(0xC2,0x85), o2(0xC2,0x86),
     o2(0xC2,0x87), o2(0xC2,0x88), o2(0xC2,0x89), o2(0xC2,0x8A),
     o2(0xC2,0x8B), o2(0xC2,0x8C), o2(0xC2,0x8D), o2(0xC2,0x8E),
     o2(0xC2,0x8F), o2(0xC2,0x90), o2(0xC2,0x91), o2(0xC2,0x92),
     o2(0xC2,0x93), o2(0xC2,0x94), o2(0xC2,0x95), o2(0xC2,0x96),
     o2(0xC2,0x97), o2(0xC2,0x98), o2(0xC2,0x99), o2(0xC2,0x9A),
     o2(0xC2,0x9B), o2(0xC2,0x9C), o2(0xC2,0x9D), o2(0xC2,0x9E),
     o2(0xC2,0x9F), o2(0xC2,0xA0), o2(0xC2,0xA4), o2(0xD8,0x8C),
     o2(0xC2,0xAD), o2(0xD8,0x9B), o2(0xD8,0x9F), o2(0xD8,0xA1),
     o2(0xD8,0xA2), o2(0xD8,0xA3), o2(0xD8,0xA4), o2(0xD8,0xA5),
     o2(0xD8,0xA6), o2(0xD8,0xA7), o2(0xD8,0xA8), o2(0xD8,0xA9),
     o2(0xD8,0xAA), o2(0xD8,0xAB), o2(0xD8,0xAC), o2(0xD8,0xAD),
     o2(0xD8,0xAE), o2(0xD8,0xAF), o2(0xD8,0xB0), o2(0xD8,0xB1),
     o2(0xD8,0xB2), o2(0xD8,0xB3), o2(0xD8,0xB4), o2(0xD8,0xB5),
     o2(0xD8,0xB6), o2(0xD8,0xB7), o2(0xD8,0xB8), o2(0xD8,0xB9),
     o2(0xD8,0xBA), o2(0xD9,0x80), o2(0xD9,0x81), o2(0xD9,0x82),
     o2(0xD9,0x83), o2(0xD9,0x84), o2(0xD9,0x85), o2(0xD9,0x86),
     o2(0xD9,0x87), o2(0xD9,0x88), o2(0xD9,0x89), o2(0xD9,0x8A),
     o2(0xD9,0x8B), o2(0xD9,0x8C), o2(0xD9,0x8D), o2(0xD9,0x8E),
     o2(0xD9,0x8F), o2(0xD9,0x90), o2(0xD9,0x91), o2(0xD9,0x92),
             UNDEF,
};
static const BYTE_LOOKUP
from_ISO_8859_6 = {
    from_ISO_8859_6_offsets,
    from_ISO_8859_6_infos
};

static const rb_transcoder
rb_from_ISO_8859_6 = {
    "ISO-8859-6", "UTF-8", &from_ISO_8859_6, 2, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_6_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 35, 35, 35, 33, 35, 35, 35,   35, 35, 35, 35, 35, 34, 35, 35,
     35, 35, 35, 35, 35, 35, 35, 35,   35, 35, 35, 35, 35, 35, 35, 35,
};
static const struct byte_lookup* const
to_ISO_8859_6_C2_infos[36] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA4), o1(0xAD),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_6_C2 = {
    to_ISO_8859_6_C2_offsets,
    to_ISO_8859_6_C2_infos
};

static const unsigned char
to_ISO_8859_6_D8_offsets[64] = {
     29, 29, 29, 29, 29, 29, 29, 29,   29, 29, 29, 29,  0, 29, 29, 29,
     29, 29, 29, 29, 29, 29, 29, 29,   29, 29, 29,  1, 29, 29, 29,  2,
     29,  3,  4,  5,  6,  7,  8,  9,   10, 11, 12, 13, 14, 15, 16, 17,
     18, 19, 20, 21, 22, 23, 24, 25,   26, 27, 28, 29, 29, 29, 29, 29,
};
static const struct byte_lookup* const
to_ISO_8859_6_D8_infos[30] = {
     o1(0xAC), o1(0xBB), o1(0xBF), o1(0xC1),
     o1(0xC2), o1(0xC3), o1(0xC4), o1(0xC5),
     o1(0xC6), o1(0xC7), o1(0xC8), o1(0xC9),
     o1(0xCA), o1(0xCB), o1(0xCC), o1(0xCD),
     o1(0xCE), o1(0xCF), o1(0xD0), o1(0xD1),
     o1(0xD2), o1(0xD3), o1(0xD4), o1(0xD5),
     o1(0xD6), o1(0xD7), o1(0xD8), o1(0xD9),
     o1(0xDA),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_6_D8 = {
    to_ISO_8859_6_D8_offsets,
    to_ISO_8859_6_D8_infos
};

static const unsigned char
to_ISO_8859_6_D9_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 19, 19, 19, 19,   19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19,   19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19,   19, 19, 19, 19, 19, 19, 19, 19,
};
static const struct byte_lookup* const
to_ISO_8859_6_D9_infos[20] = {
     o1(0xE0), o1(0xE1), o1(0xE2), o1(0xE3),
     o1(0xE4), o1(0xE5), o1(0xE6), o1(0xE7),
     o1(0xE8), o1(0xE9), o1(0xEA), o1(0xEB),
     o1(0xEC), o1(0xED), o1(0xEE), o1(0xEF),
     o1(0xF0), o1(0xF1), o1(0xF2),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_6_D9 = {
    to_ISO_8859_6_D9_offsets,
    to_ISO_8859_6_D9_infos
};

static const unsigned char
to_ISO_8859_6_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  1,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    2,  3,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
};
static const struct byte_lookup* const
to_ISO_8859_6_infos[5] = {
                 NOMAP, &to_ISO_8859_6_C2,
     &to_ISO_8859_6_D8, &to_ISO_8859_6_D9,
                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_6 = {
    to_ISO_8859_6_offsets,
    to_ISO_8859_6_infos
};

static const rb_transcoder
rb_to_ISO_8859_6 = {
    "UTF-8", "ISO-8859-6", &to_ISO_8859_6, 1, 1,
    NULL, NULL,
};

static const unsigned char
from_ISO_8859_7_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      1,  2,  3,  4,  5,  6,  7,  8,    9, 10, 11, 12, 13, 14, 15, 16,
     17, 18, 19, 20, 21, 22, 23, 24,   25, 26, 27, 28, 29, 30, 31, 32,
     33, 34, 35, 36, 37, 38, 39, 40,   41, 42, 43, 44, 45, 46,126, 47,
     48, 49, 50, 51, 52, 53, 54, 55,   56, 57, 58, 59, 60, 61, 62, 63,
     64, 65, 66, 67, 68, 69, 70, 71,   72, 73, 74, 75, 76, 77, 78, 79,
     80, 81,126, 82, 83, 84, 85, 86,   87, 88, 89, 90, 91, 92, 93, 94,
     95, 96, 97, 98, 99,100,101,102,  103,104,105,106,107,108,109,110,
    111,112,113,114,115,116,117,118,  119,120,121,122,123,124,125,126,
};
static const struct byte_lookup* const
from_ISO_8859_7_infos[127] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
     o3(0xE2,0x80,0x98), o3(0xE2,0x80,0x99),
          o2(0xC2,0xA3), o3(0xE2,0x82,0xAC),
     o3(0xE2,0x82,0xAF),      o2(0xC2,0xA6),
          o2(0xC2,0xA7),      o2(0xC2,0xA8),
          o2(0xC2,0xA9),      o2(0xCD,0xBA),
          o2(0xC2,0xAB),      o2(0xC2,0xAC),
          o2(0xC2,0xAD), o3(0xE2,0x80,0x95),
          o2(0xC2,0xB0),      o2(0xC2,0xB1),
          o2(0xC2,0xB2),      o2(0xC2,0xB3),
          o2(0xCE,0x84),      o2(0xCE,0x85),
          o2(0xCE,0x86),      o2(0xC2,0xB7),
          o2(0xCE,0x88),      o2(0xCE,0x89),
          o2(0xCE,0x8A),      o2(0xC2,0xBB),
          o2(0xCE,0x8C),      o2(0xC2,0xBD),
          o2(0xCE,0x8E),      o2(0xCE,0x8F),
          o2(0xCE,0x90),      o2(0xCE,0x91),
          o2(0xCE,0x92),      o2(0xCE,0x93),
          o2(0xCE,0x94),      o2(0xCE,0x95),
          o2(0xCE,0x96),      o2(0xCE,0x97),
          o2(0xCE,0x98),      o2(0xCE,0x99),
          o2(0xCE,0x9A),      o2(0xCE,0x9B),
          o2(0xCE,0x9C),      o2(0xCE,0x9D),
          o2(0xCE,0x9E),      o2(0xCE,0x9F),
          o2(0xCE,0xA0),      o2(0xCE,0xA1),
          o2(0xCE,0xA3),      o2(0xCE,0xA4),
          o2(0xCE,0xA5),      o2(0xCE,0xA6),
          o2(0xCE,0xA7),      o2(0xCE,0xA8),
          o2(0xCE,0xA9),      o2(0xCE,0xAA),
          o2(0xCE,0xAB),      o2(0xCE,0xAC),
          o2(0xCE,0xAD),      o2(0xCE,0xAE),
          o2(0xCE,0xAF),      o2(0xCE,0xB0),
          o2(0xCE,0xB1),      o2(0xCE,0xB2),
          o2(0xCE,0xB3),      o2(0xCE,0xB4),
          o2(0xCE,0xB5),      o2(0xCE,0xB6),
          o2(0xCE,0xB7),      o2(0xCE,0xB8),
          o2(0xCE,0xB9),      o2(0xCE,0xBA),
          o2(0xCE,0xBB),      o2(0xCE,0xBC),
          o2(0xCE,0xBD),      o2(0xCE,0xBE),
          o2(0xCE,0xBF),      o2(0xCF,0x80),
          o2(0xCF,0x81),      o2(0xCF,0x82),
          o2(0xCF,0x83),      o2(0xCF,0x84),
          o2(0xCF,0x85),      o2(0xCF,0x86),
          o2(0xCF,0x87),      o2(0xCF,0x88),
          o2(0xCF,0x89),      o2(0xCF,0x8A),
          o2(0xCF,0x8B),      o2(0xCF,0x8C),
          o2(0xCF,0x8D),      o2(0xCF,0x8E),
                  UNDEF,
};
static const BYTE_LOOKUP
from_ISO_8859_7 = {
    from_ISO_8859_7_offsets,
    from_ISO_8859_7_infos
};

static const rb_transcoder
rb_from_ISO_8859_7 = {
    "ISO-8859-7", "UTF-8", &from_ISO_8859_7, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_7_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 48, 48, 33, 48, 48, 34, 35,   36, 37, 48, 38, 39, 40, 48, 48,
     41, 42, 43, 44, 48, 48, 48, 45,   48, 48, 48, 46, 48, 47, 48, 48,
};
static const struct byte_lookup* const
to_ISO_8859_7_C2_infos[49] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA3), o1(0xA6), o1(0xA7),
     o1(0xA8), o1(0xA9), o1(0xAB), o1(0xAC),
     o1(0xAD), o1(0xB0), o1(0xB1), o1(0xB2),
     o1(0xB3), o1(0xB7), o1(0xBB), o1(0xBD),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7_C2 = {
    to_ISO_8859_7_C2_offsets,
    to_ISO_8859_7_C2_infos
};

static const unsigned char
to_ISO_8859_7_CD_offsets[64] = {
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  0,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
to_ISO_8859_7_CD_infos[2] = {
     o1(0xAA),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7_CD = {
    to_ISO_8859_7_CD_offsets,
    to_ISO_8859_7_CD_infos
};

static const unsigned char
to_ISO_8859_7_CE_offsets[64] = {
     56, 56, 56, 56,  0,  1,  2, 56,    3,  4,  5, 56,  6, 56,  7,  8,
      9, 10, 11, 12, 13, 14, 15, 16,   17, 18, 19, 20, 21, 22, 23, 24,
     25, 26, 56, 27, 28, 29, 30, 31,   32, 33, 34, 35, 36, 37, 38, 39,
     40, 41, 42, 43, 44, 45, 46, 47,   48, 49, 50, 51, 52, 53, 54, 55,
};
static const struct byte_lookup* const
to_ISO_8859_7_CE_infos[57] = {
     o1(0xB4), o1(0xB5), o1(0xB6), o1(0xB8),
     o1(0xB9), o1(0xBA), o1(0xBC), o1(0xBE),
     o1(0xBF), o1(0xC0), o1(0xC1), o1(0xC2),
     o1(0xC3), o1(0xC4), o1(0xC5), o1(0xC6),
     o1(0xC7), o1(0xC8), o1(0xC9), o1(0xCA),
     o1(0xCB), o1(0xCC), o1(0xCD), o1(0xCE),
     o1(0xCF), o1(0xD0), o1(0xD1), o1(0xD3),
     o1(0xD4), o1(0xD5), o1(0xD6), o1(0xD7),
     o1(0xD8), o1(0xD9), o1(0xDA), o1(0xDB),
     o1(0xDC), o1(0xDD), o1(0xDE), o1(0xDF),
     o1(0xE0), o1(0xE1), o1(0xE2), o1(0xE3),
     o1(0xE4), o1(0xE5), o1(0xE6), o1(0xE7),
     o1(0xE8), o1(0xE9), o1(0xEA), o1(0xEB),
     o1(0xEC), o1(0xED), o1(0xEE), o1(0xEF),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7_CE = {
    to_ISO_8859_7_CE_offsets,
    to_ISO_8859_7_CE_infos
};

static const unsigned char
to_ISO_8859_7_CF_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     15, 15, 15, 15, 15, 15, 15, 15,   15, 15, 15, 15, 15, 15, 15, 15,
     15, 15, 15, 15, 15, 15, 15, 15,   15, 15, 15, 15, 15, 15, 15, 15,
     15, 15, 15, 15, 15, 15, 15, 15,   15, 15, 15, 15, 15, 15, 15, 15,
};
static const struct byte_lookup* const
to_ISO_8859_7_CF_infos[16] = {
     o1(0xF0), o1(0xF1), o1(0xF2), o1(0xF3),
     o1(0xF4), o1(0xF5), o1(0xF6), o1(0xF7),
     o1(0xF8), o1(0xF9), o1(0xFA), o1(0xFB),
     o1(0xFC), o1(0xFD), o1(0xFE),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7_CF = {
    to_ISO_8859_7_CF_offsets,
    to_ISO_8859_7_CF_infos
};

static const unsigned char
to_ISO_8859_7_E2_80_offsets[64] = {
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  0,  3,  3,    1,  2,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
};
static const struct byte_lookup* const
to_ISO_8859_7_E2_80_infos[4] = {
     o1(0xAF), o1(0xA1), o1(0xA2),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7_E2_80 = {
    to_ISO_8859_7_E2_80_offsets,
    to_ISO_8859_7_E2_80_infos
};

static const unsigned char
to_ISO_8859_7_E2_82_offsets[64] = {
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  0,  2,  2,  1,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
};
static const struct byte_lookup* const
to_ISO_8859_7_E2_82_infos[3] = {
     o1(0xA4), o1(0xA5),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7_E2_82 = {
    to_ISO_8859_7_E2_82_offsets,
    to_ISO_8859_7_E2_82_infos
};

static const unsigned char
to_ISO_8859_7_E2_offsets[64] = {
      0,  2,  1,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
};
static const struct byte_lookup* const
to_ISO_8859_7_E2_infos[3] = {
     &to_ISO_8859_7_E2_80, &to_ISO_8859_7_E2_82,
                    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7_E2 = {
    to_ISO_8859_7_E2_offsets,
    to_ISO_8859_7_E2_infos
};

static const unsigned char
to_ISO_8859_7_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  1,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  2,  3,  4,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  5,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
};
static const struct byte_lookup* const
to_ISO_8859_7_infos[7] = {
                 NOMAP, &to_ISO_8859_7_C2,
     &to_ISO_8859_7_CD, &to_ISO_8859_7_CE,
     &to_ISO_8859_7_CF, &to_ISO_8859_7_E2,
                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_7 = {
    to_ISO_8859_7_offsets,
    to_ISO_8859_7_infos
};

static const rb_transcoder
rb_to_ISO_8859_7 = {
    "UTF-8", "ISO-8859-7", &to_ISO_8859_7, 1, 1,
    NULL, NULL,
};

static const unsigned char
from_ISO_8859_8_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      1,  2,  3,  4,  5,  6,  7,  8,    9, 10, 11, 12, 13, 14, 15, 16,
     17, 18, 19, 20, 21, 22, 23, 24,   25, 26, 27, 28, 29, 30, 31, 32,
     33, 93, 34, 35, 36, 37, 38, 39,   40, 41, 42, 43, 44, 45, 46, 47,
     48, 49, 50, 51, 52, 53, 54, 55,   56, 57, 58, 59, 60, 61, 62, 93,
     93, 93, 93, 93, 93, 93, 93, 93,   93, 93, 93, 93, 93, 93, 93, 93,
     93, 93, 93, 93, 93, 93, 93, 93,   93, 93, 93, 93, 93, 93, 93, 63,
     64, 65, 66, 67, 68, 69, 70, 71,   72, 73, 74, 75, 76, 77, 78, 79,
     80, 81, 82, 83, 84, 85, 86, 87,   88, 89, 90, 93, 93, 91, 92, 93,
};
static const struct byte_lookup* const
from_ISO_8859_8_infos[94] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
          o2(0xC2,0xA2),      o2(0xC2,0xA3),
          o2(0xC2,0xA4),      o2(0xC2,0xA5),
          o2(0xC2,0xA6),      o2(0xC2,0xA7),
          o2(0xC2,0xA8),      o2(0xC2,0xA9),
          o2(0xC3,0x97),      o2(0xC2,0xAB),
          o2(0xC2,0xAC),      o2(0xC2,0xAD),
          o2(0xC2,0xAE),      o2(0xC2,0xAF),
          o2(0xC2,0xB0),      o2(0xC2,0xB1),
          o2(0xC2,0xB2),      o2(0xC2,0xB3),
          o2(0xC2,0xB4),      o2(0xC2,0xB5),
          o2(0xC2,0xB6),      o2(0xC2,0xB7),
          o2(0xC2,0xB8),      o2(0xC2,0xB9),
          o2(0xC3,0xB7),      o2(0xC2,0xBB),
          o2(0xC2,0xBC),      o2(0xC2,0xBD),
          o2(0xC2,0xBE), o3(0xE2,0x80,0x97),
          o2(0xD7,0x90),      o2(0xD7,0x91),
          o2(0xD7,0x92),      o2(0xD7,0x93),
          o2(0xD7,0x94),      o2(0xD7,0x95),
          o2(0xD7,0x96),      o2(0xD7,0x97),
          o2(0xD7,0x98),      o2(0xD7,0x99),
          o2(0xD7,0x9A),      o2(0xD7,0x9B),
          o2(0xD7,0x9C),      o2(0xD7,0x9D),
          o2(0xD7,0x9E),      o2(0xD7,0x9F),
          o2(0xD7,0xA0),      o2(0xD7,0xA1),
          o2(0xD7,0xA2),      o2(0xD7,0xA3),
          o2(0xD7,0xA4),      o2(0xD7,0xA5),
          o2(0xD7,0xA6),      o2(0xD7,0xA7),
          o2(0xD7,0xA8),      o2(0xD7,0xA9),
          o2(0xD7,0xAA), o3(0xE2,0x80,0x8E),
     o3(0xE2,0x80,0x8F),              UNDEF,
};
static const BYTE_LOOKUP
from_ISO_8859_8 = {
    from_ISO_8859_8_offsets,
    from_ISO_8859_8_infos
};

static const rb_transcoder
rb_from_ISO_8859_8 = {
    "ISO-8859-8", "UTF-8", &from_ISO_8859_8, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_8_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 60, 33, 34, 35, 36, 37, 38,   39, 40, 60, 41, 42, 43, 44, 45,
     46, 47, 48, 49, 50, 51, 52, 53,   54, 55, 60, 56, 57, 58, 59, 60,
};
static const struct byte_lookup* const
to_ISO_8859_8_C2_infos[61] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA2), o1(0xA3), o1(0xA4),
     o1(0xA5), o1(0xA6), o1(0xA7), o1(0xA8),
     o1(0xA9), o1(0xAB), o1(0xAC), o1(0xAD),
     o1(0xAE), o1(0xAF), o1(0xB0), o1(0xB1),
     o1(0xB2), o1(0xB3), o1(0xB4), o1(0xB5),
     o1(0xB6), o1(0xB7), o1(0xB8), o1(0xB9),
     o1(0xBB), o1(0xBC), o1(0xBD), o1(0xBE),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_8_C2 = {
    to_ISO_8859_8_C2_offsets,
    to_ISO_8859_8_C2_infos
};

static const unsigned char
to_ISO_8859_8_C3_offsets[64] = {
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  0,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  1,    2,  2,  2,  2,  2,  2,  2,  2,
};
static const struct byte_lookup* const
to_ISO_8859_8_C3_infos[3] = {
     o1(0xAA), o1(0xBA),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_8_C3 = {
    to_ISO_8859_8_C3_offsets,
    to_ISO_8859_8_C3_infos
};

static const unsigned char
to_ISO_8859_8_D7_offsets[64] = {
     27, 27, 27, 27, 27, 27, 27, 27,   27, 27, 27, 27, 27, 27, 27, 27,
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 27, 27, 27, 27,
     27, 27, 27, 27, 27, 27, 27, 27,   27, 27, 27, 27, 27, 27, 27, 27,
};
static const struct byte_lookup* const
to_ISO_8859_8_D7_infos[28] = {
     o1(0xE0), o1(0xE1), o1(0xE2), o1(0xE3),
     o1(0xE4), o1(0xE5), o1(0xE6), o1(0xE7),
     o1(0xE8), o1(0xE9), o1(0xEA), o1(0xEB),
     o1(0xEC), o1(0xED), o1(0xEE), o1(0xEF),
     o1(0xF0), o1(0xF1), o1(0xF2), o1(0xF3),
     o1(0xF4), o1(0xF5), o1(0xF6), o1(0xF7),
     o1(0xF8), o1(0xF9), o1(0xFA),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_8_D7 = {
    to_ISO_8859_8_D7_offsets,
    to_ISO_8859_8_D7_infos
};

static const unsigned char
to_ISO_8859_8_E2_80_offsets[64] = {
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  0,  1,
      3,  3,  3,  3,  3,  3,  3,  2,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
};
static const struct byte_lookup* const
to_ISO_8859_8_E2_80_infos[4] = {
     o1(0xFD), o1(0xFE), o1(0xDF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_8_E2_80 = {
    to_ISO_8859_8_E2_80_offsets,
    to_ISO_8859_8_E2_80_infos
};

static const unsigned char
to_ISO_8859_8_E2_offsets[64] = {
  /* used from to_ISO_8859_8_E2 */
  /* used from to_ISO_8859_10_E2 */
  /* used from to_ISO_8859_13_E2 */
      0,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
to_ISO_8859_8_E2_infos[2] = {
     &to_ISO_8859_8_E2_80,                UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_8_E2 = {
    to_ISO_8859_8_E2_offsets,
    to_ISO_8859_8_E2_infos
};

static const unsigned char
to_ISO_8859_8_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  1,  2,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  3,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  4,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
};
static const struct byte_lookup* const
to_ISO_8859_8_infos[6] = {
                 NOMAP, &to_ISO_8859_8_C2,
     &to_ISO_8859_8_C3, &to_ISO_8859_8_D7,
     &to_ISO_8859_8_E2,             UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_8 = {
    to_ISO_8859_8_offsets,
    to_ISO_8859_8_infos
};

static const rb_transcoder
rb_to_ISO_8859_8 = {
    "UTF-8", "ISO-8859-8", &to_ISO_8859_8, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_9_infos[129] = {
             NOMAP, o2(0xC2,0x80), o2(0xC2,0x81), o2(0xC2,0x82),
     o2(0xC2,0x83), o2(0xC2,0x84), o2(0xC2,0x85), o2(0xC2,0x86),
     o2(0xC2,0x87), o2(0xC2,0x88), o2(0xC2,0x89), o2(0xC2,0x8A),
     o2(0xC2,0x8B), o2(0xC2,0x8C), o2(0xC2,0x8D), o2(0xC2,0x8E),
     o2(0xC2,0x8F), o2(0xC2,0x90), o2(0xC2,0x91), o2(0xC2,0x92),
     o2(0xC2,0x93), o2(0xC2,0x94), o2(0xC2,0x95), o2(0xC2,0x96),
     o2(0xC2,0x97), o2(0xC2,0x98), o2(0xC2,0x99), o2(0xC2,0x9A),
     o2(0xC2,0x9B), o2(0xC2,0x9C), o2(0xC2,0x9D), o2(0xC2,0x9E),
     o2(0xC2,0x9F), o2(0xC2,0xA0), o2(0xC2,0xA1), o2(0xC2,0xA2),
     o2(0xC2,0xA3), o2(0xC2,0xA4), o2(0xC2,0xA5), o2(0xC2,0xA6),
     o2(0xC2,0xA7), o2(0xC2,0xA8), o2(0xC2,0xA9), o2(0xC2,0xAA),
     o2(0xC2,0xAB), o2(0xC2,0xAC), o2(0xC2,0xAD), o2(0xC2,0xAE),
     o2(0xC2,0xAF), o2(0xC2,0xB0), o2(0xC2,0xB1), o2(0xC2,0xB2),
     o2(0xC2,0xB3), o2(0xC2,0xB4), o2(0xC2,0xB5), o2(0xC2,0xB6),
     o2(0xC2,0xB7), o2(0xC2,0xB8), o2(0xC2,0xB9), o2(0xC2,0xBA),
     o2(0xC2,0xBB), o2(0xC2,0xBC), o2(0xC2,0xBD), o2(0xC2,0xBE),
     o2(0xC2,0xBF), o2(0xC3,0x80), o2(0xC3,0x81), o2(0xC3,0x82),
     o2(0xC3,0x83), o2(0xC3,0x84), o2(0xC3,0x85), o2(0xC3,0x86),
     o2(0xC3,0x87), o2(0xC3,0x88), o2(0xC3,0x89), o2(0xC3,0x8A),
     o2(0xC3,0x8B), o2(0xC3,0x8C), o2(0xC3,0x8D), o2(0xC3,0x8E),
     o2(0xC3,0x8F), o2(0xC4,0x9E), o2(0xC3,0x91), o2(0xC3,0x92),
     o2(0xC3,0x93), o2(0xC3,0x94), o2(0xC3,0x95), o2(0xC3,0x96),
     o2(0xC3,0x97), o2(0xC3,0x98), o2(0xC3,0x99), o2(0xC3,0x9A),
     o2(0xC3,0x9B), o2(0xC3,0x9C), o2(0xC4,0xB0), o2(0xC5,0x9E),
     o2(0xC3,0x9F), o2(0xC3,0xA0), o2(0xC3,0xA1), o2(0xC3,0xA2),
     o2(0xC3,0xA3), o2(0xC3,0xA4), o2(0xC3,0xA5), o2(0xC3,0xA6),
     o2(0xC3,0xA7), o2(0xC3,0xA8), o2(0xC3,0xA9), o2(0xC3,0xAA),
     o2(0xC3,0xAB), o2(0xC3,0xAC), o2(0xC3,0xAD), o2(0xC3,0xAE),
     o2(0xC3,0xAF), o2(0xC4,0x9F), o2(0xC3,0xB1), o2(0xC3,0xB2),
     o2(0xC3,0xB3), o2(0xC3,0xB4), o2(0xC3,0xB5), o2(0xC3,0xB6),
     o2(0xC3,0xB7), o2(0xC3,0xB8), o2(0xC3,0xB9), o2(0xC3,0xBA),
     o2(0xC3,0xBB), o2(0xC3,0xBC), o2(0xC4,0xB1), o2(0xC5,0x9F),
     o2(0xC3,0xBF),
};
static const BYTE_LOOKUP
from_ISO_8859_9 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_9_infos
};

static const rb_transcoder
rb_from_ISO_8859_9 = {
    "ISO-8859-9", "UTF-8", &from_ISO_8859_9, 2, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_9_C3_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     58, 16, 17, 18, 19, 20, 21, 22,   23, 24, 25, 26, 27, 58, 58, 28,
     29, 30, 31, 32, 33, 34, 35, 36,   37, 38, 39, 40, 41, 42, 43, 44,
     58, 45, 46, 47, 48, 49, 50, 51,   52, 53, 54, 55, 56, 58, 58, 57,
};
static const struct byte_lookup* const
to_ISO_8859_9_C3_infos[59] = {
     o1(0xC0), o1(0xC1), o1(0xC2), o1(0xC3),
     o1(0xC4), o1(0xC5), o1(0xC6), o1(0xC7),
     o1(0xC8), o1(0xC9), o1(0xCA), o1(0xCB),
     o1(0xCC), o1(0xCD), o1(0xCE), o1(0xCF),
     o1(0xD1), o1(0xD2), o1(0xD3), o1(0xD4),
     o1(0xD5), o1(0xD6), o1(0xD7), o1(0xD8),
     o1(0xD9), o1(0xDA), o1(0xDB), o1(0xDC),
     o1(0xDF), o1(0xE0), o1(0xE1), o1(0xE2),
     o1(0xE3), o1(0xE4), o1(0xE5), o1(0xE6),
     o1(0xE7), o1(0xE8), o1(0xE9), o1(0xEA),
     o1(0xEB), o1(0xEC), o1(0xED), o1(0xEE),
     o1(0xEF), o1(0xF1), o1(0xF2), o1(0xF3),
     o1(0xF4), o1(0xF5), o1(0xF6), o1(0xF7),
     o1(0xF8), o1(0xF9), o1(0xFA), o1(0xFB),
     o1(0xFC), o1(0xFF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_9_C3 = {
    to_ISO_8859_9_C3_offsets,
    to_ISO_8859_9_C3_infos
};

static const unsigned char
to_ISO_8859_9_C4_offsets[64] = {
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  0,  1,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      2,  3,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
};
static const struct byte_lookup* const
to_ISO_8859_9_C4_infos[5] = {
     o1(0xD0), o1(0xF0), o1(0xDD), o1(0xFD),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_9_C4 = {
    to_ISO_8859_9_C4_offsets,
    to_ISO_8859_9_C4_infos
};

static const unsigned char
to_ISO_8859_9_C5_offsets[64] = {
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  0,  1,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
};
static const struct byte_lookup* const
to_ISO_8859_9_C5_infos[3] = {
     o1(0xDE), o1(0xFE),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_9_C5 = {
    to_ISO_8859_9_C5_offsets,
    to_ISO_8859_9_C5_infos
};

static const unsigned char
to_ISO_8859_9_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  1,  2,  3,  4,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
};
static const struct byte_lookup* const
to_ISO_8859_9_infos[6] = {
                 NOMAP, &to_ISO_8859_1_C2,
     &to_ISO_8859_9_C3, &to_ISO_8859_9_C4,
     &to_ISO_8859_9_C5,             UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_9 = {
    to_ISO_8859_9_offsets,
    to_ISO_8859_9_infos
};

static const rb_transcoder
rb_to_ISO_8859_9 = {
    "UTF-8", "ISO-8859-9", &to_ISO_8859_9, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_10_infos[129] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
          o2(0xC4,0x84),      o2(0xC4,0x92),
          o2(0xC4,0xA2),      o2(0xC4,0xAA),
          o2(0xC4,0xA8),      o2(0xC4,0xB6),
          o2(0xC2,0xA7),      o2(0xC4,0xBB),
          o2(0xC4,0x90),      o2(0xC5,0xA0),
          o2(0xC5,0xA6),      o2(0xC5,0xBD),
          o2(0xC2,0xAD),      o2(0xC5,0xAA),
          o2(0xC5,0x8A),      o2(0xC2,0xB0),
          o2(0xC4,0x85),      o2(0xC4,0x93),
          o2(0xC4,0xA3),      o2(0xC4,0xAB),
          o2(0xC4,0xA9),      o2(0xC4,0xB7),
          o2(0xC2,0xB7),      o2(0xC4,0xBC),
          o2(0xC4,0x91),      o2(0xC5,0xA1),
          o2(0xC5,0xA7),      o2(0xC5,0xBE),
     o3(0xE2,0x80,0x95),      o2(0xC5,0xAB),
          o2(0xC5,0x8B),      o2(0xC4,0x80),
          o2(0xC3,0x81),      o2(0xC3,0x82),
          o2(0xC3,0x83),      o2(0xC3,0x84),
          o2(0xC3,0x85),      o2(0xC3,0x86),
          o2(0xC4,0xAE),      o2(0xC4,0x8C),
          o2(0xC3,0x89),      o2(0xC4,0x98),
          o2(0xC3,0x8B),      o2(0xC4,0x96),
          o2(0xC3,0x8D),      o2(0xC3,0x8E),
          o2(0xC3,0x8F),      o2(0xC3,0x90),
          o2(0xC5,0x85),      o2(0xC5,0x8C),
          o2(0xC3,0x93),      o2(0xC3,0x94),
          o2(0xC3,0x95),      o2(0xC3,0x96),
          o2(0xC5,0xA8),      o2(0xC3,0x98),
          o2(0xC5,0xB2),      o2(0xC3,0x9A),
          o2(0xC3,0x9B),      o2(0xC3,0x9C),
          o2(0xC3,0x9D),      o2(0xC3,0x9E),
          o2(0xC3,0x9F),      o2(0xC4,0x81),
          o2(0xC3,0xA1),      o2(0xC3,0xA2),
          o2(0xC3,0xA3),      o2(0xC3,0xA4),
          o2(0xC3,0xA5),      o2(0xC3,0xA6),
          o2(0xC4,0xAF),      o2(0xC4,0x8D),
          o2(0xC3,0xA9),      o2(0xC4,0x99),
          o2(0xC3,0xAB),      o2(0xC4,0x97),
          o2(0xC3,0xAD),      o2(0xC3,0xAE),
          o2(0xC3,0xAF),      o2(0xC3,0xB0),
          o2(0xC5,0x86),      o2(0xC5,0x8D),
          o2(0xC3,0xB3),      o2(0xC3,0xB4),
          o2(0xC3,0xB5),      o2(0xC3,0xB6),
          o2(0xC5,0xA9),      o2(0xC3,0xB8),
          o2(0xC5,0xB3),      o2(0xC3,0xBA),
          o2(0xC3,0xBB),      o2(0xC3,0xBC),
          o2(0xC3,0xBD),      o2(0xC3,0xBE),
          o2(0xC4,0xB8),
};
static const BYTE_LOOKUP
from_ISO_8859_10 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_10_infos
};

static const rb_transcoder
rb_from_ISO_8859_10 = {
    "ISO-8859-10", "UTF-8", &from_ISO_8859_10, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_10_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 37, 37, 37, 37, 37, 37, 33,   37, 37, 37, 37, 37, 34, 37, 37,
     35, 37, 37, 37, 37, 37, 37, 36,   37, 37, 37, 37, 37, 37, 37, 37,
};
static const struct byte_lookup* const
to_ISO_8859_10_C2_infos[38] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA7), o1(0xAD), o1(0xB0),
     o1(0xB7),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_10_C2 = {
    to_ISO_8859_10_C2_offsets,
    to_ISO_8859_10_C2_infos
};

static const unsigned char
to_ISO_8859_10_C3_offsets[64] = {
     45,  0,  1,  2,  3,  4,  5, 45,   45,  6, 45,  7, 45,  8,  9, 10,
     11, 45, 45, 12, 13, 14, 15, 45,   16, 45, 17, 18, 19, 20, 21, 22,
     45, 23, 24, 25, 26, 27, 28, 45,   45, 29, 45, 30, 45, 31, 32, 33,
     34, 45, 45, 35, 36, 37, 38, 45,   39, 45, 40, 41, 42, 43, 44, 45,
};
static const struct byte_lookup* const
to_ISO_8859_10_C3_infos[46] = {
     o1(0xC1), o1(0xC2), o1(0xC3), o1(0xC4),
     o1(0xC5), o1(0xC6), o1(0xC9), o1(0xCB),
     o1(0xCD), o1(0xCE), o1(0xCF), o1(0xD0),
     o1(0xD3), o1(0xD4), o1(0xD5), o1(0xD6),
     o1(0xD8), o1(0xDA), o1(0xDB), o1(0xDC),
     o1(0xDD), o1(0xDE), o1(0xDF), o1(0xE1),
     o1(0xE2), o1(0xE3), o1(0xE4), o1(0xE5),
     o1(0xE6), o1(0xE9), o1(0xEB), o1(0xED),
     o1(0xEE), o1(0xEF), o1(0xF0), o1(0xF3),
     o1(0xF4), o1(0xF5), o1(0xF6), o1(0xF8),
     o1(0xFA), o1(0xFB), o1(0xFC), o1(0xFD),
     o1(0xFE),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_10_C3 = {
    to_ISO_8859_10_C3_offsets,
    to_ISO_8859_10_C3_infos
};

static const struct byte_lookup* const
to_ISO_8859_10_C4_infos[28] = {
     o1(0xC0), o1(0xE0), o1(0xA1), o1(0xB1),
     o1(0xC8), o1(0xE8), o1(0xA9), o1(0xB9),
     o1(0xA2), o1(0xB2), o1(0xCC), o1(0xEC),
     o1(0xCA), o1(0xEA), o1(0xA3), o1(0xB3),
     o1(0xA5), o1(0xB5), o1(0xA4), o1(0xB4),
     o1(0xC7), o1(0xE7), o1(0xA6), o1(0xB6),
     o1(0xFF), o1(0xA8), o1(0xB8),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_10_C4 = {
    to_ISO_8859_4_C4_offsets,
    to_ISO_8859_10_C4_infos
};

static const unsigned char
to_ISO_8859_10_C5_offsets[64] = {
     18, 18, 18, 18, 18,  0,  1, 18,   18, 18,  2,  3,  4,  5, 18, 18,
     18, 18, 18, 18, 18, 18, 18, 18,   18, 18, 18, 18, 18, 18, 18, 18,
      6,  7, 18, 18, 18, 18,  8,  9,   10, 11, 12, 13, 18, 18, 18, 18,
     18, 18, 14, 15, 18, 18, 18, 18,   18, 18, 18, 18, 18, 16, 17, 18,
};
static const struct byte_lookup* const
to_ISO_8859_10_C5_infos[19] = {
     o1(0xD1), o1(0xF1), o1(0xAF), o1(0xBF),
     o1(0xD2), o1(0xF2), o1(0xAA), o1(0xBA),
     o1(0xAB), o1(0xBB), o1(0xD7), o1(0xF7),
     o1(0xAE), o1(0xBE), o1(0xD9), o1(0xF9),
     o1(0xAC), o1(0xBC),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_10_C5 = {
    to_ISO_8859_10_C5_offsets,
    to_ISO_8859_10_C5_infos
};

static const unsigned char
to_ISO_8859_10_E2_80_offsets[64] = {
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  0,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
to_ISO_8859_10_E2_80_infos[2] = {
     o1(0xBD),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_10_E2_80 = {
    to_ISO_8859_10_E2_80_offsets,
    to_ISO_8859_10_E2_80_infos
};

static const struct byte_lookup* const
to_ISO_8859_10_E2_infos[2] = {
     &to_ISO_8859_10_E2_80,                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_10_E2 = {
    to_ISO_8859_8_E2_offsets,
    to_ISO_8859_10_E2_infos
};

static const unsigned char
to_ISO_8859_10_offsets[256] = {
  /* used from to_ISO_8859_10 */
  /* used from to_ISO_8859_13 */
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  1,  2,  3,  4,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  5,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
};
static const struct byte_lookup* const
to_ISO_8859_10_infos[7] = {
                  NOMAP, &to_ISO_8859_10_C2,
     &to_ISO_8859_10_C3, &to_ISO_8859_10_C4,
     &to_ISO_8859_10_C5, &to_ISO_8859_10_E2,
                  UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_10 = {
    to_ISO_8859_10_offsets,
    to_ISO_8859_10_infos
};

static const rb_transcoder
rb_to_ISO_8859_10 = {
    "UTF-8", "ISO-8859-10", &to_ISO_8859_10, 1, 1,
    NULL, NULL,
};

static const unsigned char
from_ISO_8859_11_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      1,  2,  3,  4,  5,  6,  7,  8,    9, 10, 11, 12, 13, 14, 15, 16,
     17, 18, 19, 20, 21, 22, 23, 24,   25, 26, 27, 28, 29, 30, 31, 32,
     33, 34, 35, 36, 37, 38, 39, 40,   41, 42, 43, 44, 45, 46, 47, 48,
     49, 50, 51, 52, 53, 54, 55, 56,   57, 58, 59, 60, 61, 62, 63, 64,
     65, 66, 67, 68, 69, 70, 71, 72,   73, 74, 75, 76, 77, 78, 79, 80,
     81, 82, 83, 84, 85, 86, 87, 88,   89, 90, 91,121,121,121,121, 92,
     93, 94, 95, 96, 97, 98, 99,100,  101,102,103,104,105,106,107,108,
    109,110,111,112,113,114,115,116,  117,118,119,120,121,121,121,121,
};
static const struct byte_lookup* const
from_ISO_8859_11_infos[122] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
     o3(0xE0,0xB8,0x81), o3(0xE0,0xB8,0x82),
     o3(0xE0,0xB8,0x83), o3(0xE0,0xB8,0x84),
     o3(0xE0,0xB8,0x85), o3(0xE0,0xB8,0x86),
     o3(0xE0,0xB8,0x87), o3(0xE0,0xB8,0x88),
     o3(0xE0,0xB8,0x89), o3(0xE0,0xB8,0x8A),
     o3(0xE0,0xB8,0x8B), o3(0xE0,0xB8,0x8C),
     o3(0xE0,0xB8,0x8D), o3(0xE0,0xB8,0x8E),
     o3(0xE0,0xB8,0x8F), o3(0xE0,0xB8,0x90),
     o3(0xE0,0xB8,0x91), o3(0xE0,0xB8,0x92),
     o3(0xE0,0xB8,0x93), o3(0xE0,0xB8,0x94),
     o3(0xE0,0xB8,0x95), o3(0xE0,0xB8,0x96),
     o3(0xE0,0xB8,0x97), o3(0xE0,0xB8,0x98),
     o3(0xE0,0xB8,0x99), o3(0xE0,0xB8,0x9A),
     o3(0xE0,0xB8,0x9B), o3(0xE0,0xB8,0x9C),
     o3(0xE0,0xB8,0x9D), o3(0xE0,0xB8,0x9E),
     o3(0xE0,0xB8,0x9F), o3(0xE0,0xB8,0xA0),
     o3(0xE0,0xB8,0xA1), o3(0xE0,0xB8,0xA2),
     o3(0xE0,0xB8,0xA3), o3(0xE0,0xB8,0xA4),
     o3(0xE0,0xB8,0xA5), o3(0xE0,0xB8,0xA6),
     o3(0xE0,0xB8,0xA7), o3(0xE0,0xB8,0xA8),
     o3(0xE0,0xB8,0xA9), o3(0xE0,0xB8,0xAA),
     o3(0xE0,0xB8,0xAB), o3(0xE0,0xB8,0xAC),
     o3(0xE0,0xB8,0xAD), o3(0xE0,0xB8,0xAE),
     o3(0xE0,0xB8,0xAF), o3(0xE0,0xB8,0xB0),
     o3(0xE0,0xB8,0xB1), o3(0xE0,0xB8,0xB2),
     o3(0xE0,0xB8,0xB3), o3(0xE0,0xB8,0xB4),
     o3(0xE0,0xB8,0xB5), o3(0xE0,0xB8,0xB6),
     o3(0xE0,0xB8,0xB7), o3(0xE0,0xB8,0xB8),
     o3(0xE0,0xB8,0xB9), o3(0xE0,0xB8,0xBA),
     o3(0xE0,0xB8,0xBF), o3(0xE0,0xB9,0x80),
     o3(0xE0,0xB9,0x81), o3(0xE0,0xB9,0x82),
     o3(0xE0,0xB9,0x83), o3(0xE0,0xB9,0x84),
     o3(0xE0,0xB9,0x85), o3(0xE0,0xB9,0x86),
     o3(0xE0,0xB9,0x87), o3(0xE0,0xB9,0x88),
     o3(0xE0,0xB9,0x89), o3(0xE0,0xB9,0x8A),
     o3(0xE0,0xB9,0x8B), o3(0xE0,0xB9,0x8C),
     o3(0xE0,0xB9,0x8D), o3(0xE0,0xB9,0x8E),
     o3(0xE0,0xB9,0x8F), o3(0xE0,0xB9,0x90),
     o3(0xE0,0xB9,0x91), o3(0xE0,0xB9,0x92),
     o3(0xE0,0xB9,0x93), o3(0xE0,0xB9,0x94),
     o3(0xE0,0xB9,0x95), o3(0xE0,0xB9,0x96),
     o3(0xE0,0xB9,0x97), o3(0xE0,0xB9,0x98),
     o3(0xE0,0xB9,0x99), o3(0xE0,0xB9,0x9A),
     o3(0xE0,0xB9,0x9B),              UNDEF,
};
static const BYTE_LOOKUP
from_ISO_8859_11 = {
    from_ISO_8859_11_offsets,
    from_ISO_8859_11_infos
};

static const rb_transcoder
rb_from_ISO_8859_11 = {
    "ISO-8859-11", "UTF-8", &from_ISO_8859_11, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_11_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 33, 33, 33, 33, 33, 33,   33, 33, 33, 33, 33, 33, 33, 33,
     33, 33, 33, 33, 33, 33, 33, 33,   33, 33, 33, 33, 33, 33, 33, 33,
};
static const struct byte_lookup* const
to_ISO_8859_11_C2_infos[34] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_11_C2 = {
    to_ISO_8859_11_C2_offsets,
    to_ISO_8859_11_C2_infos
};

static const unsigned char
to_ISO_8859_11_E0_B8_offsets[64] = {
     59,  0,  1,  2,  3,  4,  5,  6,    7,  8,  9, 10, 11, 12, 13, 14,
     15, 16, 17, 18, 19, 20, 21, 22,   23, 24, 25, 26, 27, 28, 29, 30,
     31, 32, 33, 34, 35, 36, 37, 38,   39, 40, 41, 42, 43, 44, 45, 46,
     47, 48, 49, 50, 51, 52, 53, 54,   55, 56, 57, 59, 59, 59, 59, 58,
};
static const struct byte_lookup* const
to_ISO_8859_11_E0_B8_infos[60] = {
     o1(0xA1), o1(0xA2), o1(0xA3), o1(0xA4),
     o1(0xA5), o1(0xA6), o1(0xA7), o1(0xA8),
     o1(0xA9), o1(0xAA), o1(0xAB), o1(0xAC),
     o1(0xAD), o1(0xAE), o1(0xAF), o1(0xB0),
     o1(0xB1), o1(0xB2), o1(0xB3), o1(0xB4),
     o1(0xB5), o1(0xB6), o1(0xB7), o1(0xB8),
     o1(0xB9), o1(0xBA), o1(0xBB), o1(0xBC),
     o1(0xBD), o1(0xBE), o1(0xBF), o1(0xC0),
     o1(0xC1), o1(0xC2), o1(0xC3), o1(0xC4),
     o1(0xC5), o1(0xC6), o1(0xC7), o1(0xC8),
     o1(0xC9), o1(0xCA), o1(0xCB), o1(0xCC),
     o1(0xCD), o1(0xCE), o1(0xCF), o1(0xD0),
     o1(0xD1), o1(0xD2), o1(0xD3), o1(0xD4),
     o1(0xD5), o1(0xD6), o1(0xD7), o1(0xD8),
     o1(0xD9), o1(0xDA), o1(0xDF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_11_E0_B8 = {
    to_ISO_8859_11_E0_B8_offsets,
    to_ISO_8859_11_E0_B8_infos
};

static const unsigned char
to_ISO_8859_11_E0_B9_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 28, 28, 28,
     28, 28, 28, 28, 28, 28, 28, 28,   28, 28, 28, 28, 28, 28, 28, 28,
     28, 28, 28, 28, 28, 28, 28, 28,   28, 28, 28, 28, 28, 28, 28, 28,
};
static const struct byte_lookup* const
to_ISO_8859_11_E0_B9_infos[29] = {
     o1(0xE0), o1(0xE1), o1(0xE2), o1(0xE3),
     o1(0xE4), o1(0xE5), o1(0xE6), o1(0xE7),
     o1(0xE8), o1(0xE9), o1(0xEA), o1(0xEB),
     o1(0xEC), o1(0xED), o1(0xEE), o1(0xEF),
     o1(0xF0), o1(0xF1), o1(0xF2), o1(0xF3),
     o1(0xF4), o1(0xF5), o1(0xF6), o1(0xF7),
     o1(0xF8), o1(0xF9), o1(0xFA), o1(0xFB),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_11_E0_B9 = {
    to_ISO_8859_11_E0_B9_offsets,
    to_ISO_8859_11_E0_B9_infos
};

static const unsigned char
to_ISO_8859_11_E0_offsets[64] = {
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    0,  1,  2,  2,  2,  2,  2,  2,
};
static const struct byte_lookup* const
to_ISO_8859_11_E0_infos[3] = {
     &to_ISO_8859_11_E0_B8, &to_ISO_8859_11_E0_B9,
                     UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_11_E0 = {
    to_ISO_8859_11_E0_offsets,
    to_ISO_8859_11_E0_infos
};

static const unsigned char
to_ISO_8859_11_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  1,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      2,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
      3,  3,  3,  3,  3,  3,  3,  3,    3,  3,  3,  3,  3,  3,  3,  3,
};
static const struct byte_lookup* const
to_ISO_8859_11_infos[4] = {
                  NOMAP, &to_ISO_8859_11_C2,
     &to_ISO_8859_11_E0,              UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_11 = {
    to_ISO_8859_11_offsets,
    to_ISO_8859_11_infos
};

static const rb_transcoder
rb_to_ISO_8859_11 = {
    "UTF-8", "ISO-8859-11", &to_ISO_8859_11, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_13_infos[129] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
     o3(0xE2,0x80,0x9D),      o2(0xC2,0xA2),
          o2(0xC2,0xA3),      o2(0xC2,0xA4),
     o3(0xE2,0x80,0x9E),      o2(0xC2,0xA6),
          o2(0xC2,0xA7),      o2(0xC3,0x98),
          o2(0xC2,0xA9),      o2(0xC5,0x96),
          o2(0xC2,0xAB),      o2(0xC2,0xAC),
          o2(0xC2,0xAD),      o2(0xC2,0xAE),
          o2(0xC3,0x86),      o2(0xC2,0xB0),
          o2(0xC2,0xB1),      o2(0xC2,0xB2),
          o2(0xC2,0xB3), o3(0xE2,0x80,0x9C),
          o2(0xC2,0xB5),      o2(0xC2,0xB6),
          o2(0xC2,0xB7),      o2(0xC3,0xB8),
          o2(0xC2,0xB9),      o2(0xC5,0x97),
          o2(0xC2,0xBB),      o2(0xC2,0xBC),
          o2(0xC2,0xBD),      o2(0xC2,0xBE),
          o2(0xC3,0xA6),      o2(0xC4,0x84),
          o2(0xC4,0xAE),      o2(0xC4,0x80),
          o2(0xC4,0x86),      o2(0xC3,0x84),
          o2(0xC3,0x85),      o2(0xC4,0x98),
          o2(0xC4,0x92),      o2(0xC4,0x8C),
          o2(0xC3,0x89),      o2(0xC5,0xB9),
          o2(0xC4,0x96),      o2(0xC4,0xA2),
          o2(0xC4,0xB6),      o2(0xC4,0xAA),
          o2(0xC4,0xBB),      o2(0xC5,0xA0),
          o2(0xC5,0x83),      o2(0xC5,0x85),
          o2(0xC3,0x93),      o2(0xC5,0x8C),
          o2(0xC3,0x95),      o2(0xC3,0x96),
          o2(0xC3,0x97),      o2(0xC5,0xB2),
          o2(0xC5,0x81),      o2(0xC5,0x9A),
          o2(0xC5,0xAA),      o2(0xC3,0x9C),
          o2(0xC5,0xBB),      o2(0xC5,0xBD),
          o2(0xC3,0x9F),      o2(0xC4,0x85),
          o2(0xC4,0xAF),      o2(0xC4,0x81),
          o2(0xC4,0x87),      o2(0xC3,0xA4),
          o2(0xC3,0xA5),      o2(0xC4,0x99),
          o2(0xC4,0x93),      o2(0xC4,0x8D),
          o2(0xC3,0xA9),      o2(0xC5,0xBA),
          o2(0xC4,0x97),      o2(0xC4,0xA3),
          o2(0xC4,0xB7),      o2(0xC4,0xAB),
          o2(0xC4,0xBC),      o2(0xC5,0xA1),
          o2(0xC5,0x84),      o2(0xC5,0x86),
          o2(0xC3,0xB3),      o2(0xC5,0x8D),
          o2(0xC3,0xB5),      o2(0xC3,0xB6),
          o2(0xC3,0xB7),      o2(0xC5,0xB3),
          o2(0xC5,0x82),      o2(0xC5,0x9B),
          o2(0xC5,0xAB),      o2(0xC3,0xBC),
          o2(0xC5,0xBC),      o2(0xC5,0xBE),
     o3(0xE2,0x80,0x99),
};
static const BYTE_LOOKUP
from_ISO_8859_13 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_13_infos
};

static const rb_transcoder
rb_from_ISO_8859_13 = {
    "ISO-8859-13", "UTF-8", &from_ISO_8859_13, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_13_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 55, 33, 34, 35, 55, 36, 37,   55, 38, 55, 39, 40, 41, 42, 55,
     43, 44, 45, 46, 55, 47, 48, 49,   55, 50, 55, 51, 52, 53, 54, 55,
};
static const struct byte_lookup* const
to_ISO_8859_13_C2_infos[56] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA2), o1(0xA3), o1(0xA4),
     o1(0xA6), o1(0xA7), o1(0xA9), o1(0xAB),
     o1(0xAC), o1(0xAD), o1(0xAE), o1(0xB0),
     o1(0xB1), o1(0xB2), o1(0xB3), o1(0xB5),
     o1(0xB6), o1(0xB7), o1(0xB9), o1(0xBB),
     o1(0xBC), o1(0xBD), o1(0xBE),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_13_C2 = {
    to_ISO_8859_13_C2_offsets,
    to_ISO_8859_13_C2_infos
};

static const unsigned char
to_ISO_8859_13_C3_offsets[64] = {
     21, 21, 21, 21,  0,  1,  2, 21,   21,  3, 21, 21, 21, 21, 21, 21,
     21, 21, 21,  4, 21,  5,  6,  7,    8, 21, 21, 21,  9, 21, 21, 10,
     21, 21, 21, 21, 11, 12, 13, 21,   21, 14, 21, 21, 21, 21, 21, 21,
     21, 21, 21, 15, 21, 16, 17, 18,   19, 21, 21, 21, 20, 21, 21, 21,
};
static const struct byte_lookup* const
to_ISO_8859_13_C3_infos[22] = {
     o1(0xC4), o1(0xC5), o1(0xAF), o1(0xC9),
     o1(0xD3), o1(0xD5), o1(0xD6), o1(0xD7),
     o1(0xA8), o1(0xDC), o1(0xDF), o1(0xE4),
     o1(0xE5), o1(0xBF), o1(0xE9), o1(0xF3),
     o1(0xF5), o1(0xF6), o1(0xF7), o1(0xB8),
     o1(0xFC),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_13_C3 = {
    to_ISO_8859_13_C3_offsets,
    to_ISO_8859_13_C3_infos
};

static const unsigned char
to_ISO_8859_13_C4_offsets[64] = {
      0,  1, 24, 24,  2,  3,  4,  5,   24, 24, 24, 24,  6,  7, 24, 24,
     24, 24,  8,  9, 24, 24, 10, 11,   12, 13, 24, 24, 24, 24, 24, 24,
     24, 24, 14, 15, 24, 24, 24, 24,   24, 24, 16, 17, 24, 24, 18, 19,
     24, 24, 24, 24, 24, 24, 20, 21,   24, 24, 24, 22, 23, 24, 24, 24,
};
static const struct byte_lookup* const
to_ISO_8859_13_C4_infos[25] = {
     o1(0xC2), o1(0xE2), o1(0xC0), o1(0xE0),
     o1(0xC3), o1(0xE3), o1(0xC8), o1(0xE8),
     o1(0xC7), o1(0xE7), o1(0xCB), o1(0xEB),
     o1(0xC6), o1(0xE6), o1(0xCC), o1(0xEC),
     o1(0xCE), o1(0xEE), o1(0xC1), o1(0xE1),
     o1(0xCD), o1(0xED), o1(0xCF), o1(0xEF),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_13_C4 = {
    to_ISO_8859_13_C4_offsets,
    to_ISO_8859_13_C4_infos
};

static const unsigned char
to_ISO_8859_13_C5_offsets[64] = {
     24,  0,  1,  2,  3,  4,  5, 24,   24, 24, 24, 24,  6,  7, 24, 24,
     24, 24, 24, 24, 24, 24,  8,  9,   24, 24, 10, 11, 24, 24, 24, 24,
     12, 13, 24, 24, 24, 24, 24, 24,   24, 24, 14, 15, 24, 24, 24, 24,
     24, 24, 16, 17, 24, 24, 24, 24,   24, 18, 19, 20, 21, 22, 23, 24,
};
static const struct byte_lookup* const
to_ISO_8859_13_C5_infos[25] = {
     o1(0xD9), o1(0xF9), o1(0xD1), o1(0xF1),
     o1(0xD2), o1(0xF2), o1(0xD4), o1(0xF4),
     o1(0xAA), o1(0xBA), o1(0xDA), o1(0xFA),
     o1(0xD0), o1(0xF0), o1(0xDB), o1(0xFB),
     o1(0xD8), o1(0xF8), o1(0xCA), o1(0xEA),
     o1(0xDD), o1(0xFD), o1(0xDE), o1(0xFE),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_13_C5 = {
    to_ISO_8859_13_C5_offsets,
    to_ISO_8859_13_C5_infos
};

static const unsigned char
to_ISO_8859_13_E2_80_offsets[64] = {
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  0,  4,  4,  1,  2,  3,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
};
static const struct byte_lookup* const
to_ISO_8859_13_E2_80_infos[5] = {
     o1(0xFF), o1(0xB4), o1(0xA1), o1(0xA5),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_13_E2_80 = {
    to_ISO_8859_13_E2_80_offsets,
    to_ISO_8859_13_E2_80_infos
};

static const struct byte_lookup* const
to_ISO_8859_13_E2_infos[2] = {
     &to_ISO_8859_13_E2_80,                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_13_E2 = {
    to_ISO_8859_8_E2_offsets,
    to_ISO_8859_13_E2_infos
};

static const struct byte_lookup* const
to_ISO_8859_13_infos[7] = {
                  NOMAP, &to_ISO_8859_13_C2,
     &to_ISO_8859_13_C3, &to_ISO_8859_13_C4,
     &to_ISO_8859_13_C5, &to_ISO_8859_13_E2,
                  UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_13 = {
    to_ISO_8859_10_offsets,
    to_ISO_8859_13_infos
};

static const rb_transcoder
rb_to_ISO_8859_13 = {
    "UTF-8", "ISO-8859-13", &to_ISO_8859_13, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_14_infos[129] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
     o3(0xE1,0xB8,0x82), o3(0xE1,0xB8,0x83),
          o2(0xC2,0xA3),      o2(0xC4,0x8A),
          o2(0xC4,0x8B), o3(0xE1,0xB8,0x8A),
          o2(0xC2,0xA7), o3(0xE1,0xBA,0x80),
          o2(0xC2,0xA9), o3(0xE1,0xBA,0x82),
     o3(0xE1,0xB8,0x8B), o3(0xE1,0xBB,0xB2),
          o2(0xC2,0xAD),      o2(0xC2,0xAE),
          o2(0xC5,0xB8), o3(0xE1,0xB8,0x9E),
     o3(0xE1,0xB8,0x9F),      o2(0xC4,0xA0),
          o2(0xC4,0xA1), o3(0xE1,0xB9,0x80),
     o3(0xE1,0xB9,0x81),      o2(0xC2,0xB6),
     o3(0xE1,0xB9,0x96), o3(0xE1,0xBA,0x81),
     o3(0xE1,0xB9,0x97), o3(0xE1,0xBA,0x83),
     o3(0xE1,0xB9,0xA0), o3(0xE1,0xBB,0xB3),
     o3(0xE1,0xBA,0x84), o3(0xE1,0xBA,0x85),
     o3(0xE1,0xB9,0xA1),      o2(0xC3,0x80),
          o2(0xC3,0x81),      o2(0xC3,0x82),
          o2(0xC3,0x83),      o2(0xC3,0x84),
          o2(0xC3,0x85),      o2(0xC3,0x86),
          o2(0xC3,0x87),      o2(0xC3,0x88),
          o2(0xC3,0x89),      o2(0xC3,0x8A),
          o2(0xC3,0x8B),      o2(0xC3,0x8C),
          o2(0xC3,0x8D),      o2(0xC3,0x8E),
          o2(0xC3,0x8F),      o2(0xC5,0xB4),
          o2(0xC3,0x91),      o2(0xC3,0x92),
          o2(0xC3,0x93),      o2(0xC3,0x94),
          o2(0xC3,0x95),      o2(0xC3,0x96),
     o3(0xE1,0xB9,0xAA),      o2(0xC3,0x98),
          o2(0xC3,0x99),      o2(0xC3,0x9A),
          o2(0xC3,0x9B),      o2(0xC3,0x9C),
          o2(0xC3,0x9D),      o2(0xC5,0xB6),
          o2(0xC3,0x9F),      o2(0xC3,0xA0),
          o2(0xC3,0xA1),      o2(0xC3,0xA2),
          o2(0xC3,0xA3),      o2(0xC3,0xA4),
          o2(0xC3,0xA5),      o2(0xC3,0xA6),
          o2(0xC3,0xA7),      o2(0xC3,0xA8),
          o2(0xC3,0xA9),      o2(0xC3,0xAA),
          o2(0xC3,0xAB),      o2(0xC3,0xAC),
          o2(0xC3,0xAD),      o2(0xC3,0xAE),
          o2(0xC3,0xAF),      o2(0xC5,0xB5),
          o2(0xC3,0xB1),      o2(0xC3,0xB2),
          o2(0xC3,0xB3),      o2(0xC3,0xB4),
          o2(0xC3,0xB5),      o2(0xC3,0xB6),
     o3(0xE1,0xB9,0xAB),      o2(0xC3,0xB8),
          o2(0xC3,0xB9),      o2(0xC3,0xBA),
          o2(0xC3,0xBB),      o2(0xC3,0xBC),
          o2(0xC3,0xBD),      o2(0xC5,0xB7),
          o2(0xC3,0xBF),
};
static const BYTE_LOOKUP
from_ISO_8859_14 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_14_infos
};

static const rb_transcoder
rb_from_ISO_8859_14 = {
    "ISO-8859-14", "UTF-8", &from_ISO_8859_14, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_14_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 39, 39, 33, 39, 39, 39, 34,   39, 35, 39, 39, 39, 36, 37, 39,
     39, 39, 39, 39, 39, 39, 38, 39,   39, 39, 39, 39, 39, 39, 39, 39,
};
static const struct byte_lookup* const
to_ISO_8859_14_C2_infos[40] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA3), o1(0xA7), o1(0xA9),
     o1(0xAD), o1(0xAE), o1(0xB6),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_C2 = {
    to_ISO_8859_14_C2_offsets,
    to_ISO_8859_14_C2_infos
};

static const unsigned char
to_ISO_8859_14_C3_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     58, 16, 17, 18, 19, 20, 21, 58,   22, 23, 24, 25, 26, 27, 58, 28,
     29, 30, 31, 32, 33, 34, 35, 36,   37, 38, 39, 40, 41, 42, 43, 44,
     58, 45, 46, 47, 48, 49, 50, 58,   51, 52, 53, 54, 55, 56, 58, 57,
};
static const struct byte_lookup* const
to_ISO_8859_14_C3_infos[59] = {
     o1(0xC0), o1(0xC1), o1(0xC2), o1(0xC3),
     o1(0xC4), o1(0xC5), o1(0xC6), o1(0xC7),
     o1(0xC8), o1(0xC9), o1(0xCA), o1(0xCB),
     o1(0xCC), o1(0xCD), o1(0xCE), o1(0xCF),
     o1(0xD1), o1(0xD2), o1(0xD3), o1(0xD4),
     o1(0xD5), o1(0xD6), o1(0xD8), o1(0xD9),
     o1(0xDA), o1(0xDB), o1(0xDC), o1(0xDD),
     o1(0xDF), o1(0xE0), o1(0xE1), o1(0xE2),
     o1(0xE3), o1(0xE4), o1(0xE5), o1(0xE6),
     o1(0xE7), o1(0xE8), o1(0xE9), o1(0xEA),
     o1(0xEB), o1(0xEC), o1(0xED), o1(0xEE),
     o1(0xEF), o1(0xF1), o1(0xF2), o1(0xF3),
     o1(0xF4), o1(0xF5), o1(0xF6), o1(0xF8),
     o1(0xF9), o1(0xFA), o1(0xFB), o1(0xFC),
     o1(0xFD), o1(0xFF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_C3 = {
    to_ISO_8859_14_C3_offsets,
    to_ISO_8859_14_C3_infos
};

static const unsigned char
to_ISO_8859_14_C4_offsets[64] = {
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  0,  1,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      2,  3,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
};
static const struct byte_lookup* const
to_ISO_8859_14_C4_infos[5] = {
     o1(0xA4), o1(0xA5), o1(0xB2), o1(0xB3),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_C4 = {
    to_ISO_8859_14_C4_offsets,
    to_ISO_8859_14_C4_infos
};

static const unsigned char
to_ISO_8859_14_C5_offsets[64] = {
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  0,  1,  2,  3,    4,  5,  5,  5,  5,  5,  5,  5,
};
static const struct byte_lookup* const
to_ISO_8859_14_C5_infos[6] = {
     o1(0xD0), o1(0xF0), o1(0xDE), o1(0xFE),
     o1(0xAF),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_C5 = {
    to_ISO_8859_14_C5_offsets,
    to_ISO_8859_14_C5_infos
};

static const unsigned char
to_ISO_8859_14_E1_B8_offsets[64] = {
      6,  6,  0,  1,  6,  6,  6,  6,    6,  6,  2,  3,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  4,  5,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
};
static const struct byte_lookup* const
to_ISO_8859_14_E1_B8_infos[7] = {
     o1(0xA1), o1(0xA2), o1(0xA6), o1(0xAB),
     o1(0xB0), o1(0xB1),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_E1_B8 = {
    to_ISO_8859_14_E1_B8_offsets,
    to_ISO_8859_14_E1_B8_infos
};

static const unsigned char
to_ISO_8859_14_E1_B9_offsets[64] = {
      0,  1,  8,  8,  8,  8,  8,  8,    8,  8,  8,  8,  8,  8,  8,  8,
      8,  8,  8,  8,  8,  8,  2,  3,    8,  8,  8,  8,  8,  8,  8,  8,
      4,  5,  8,  8,  8,  8,  8,  8,    8,  8,  6,  7,  8,  8,  8,  8,
      8,  8,  8,  8,  8,  8,  8,  8,    8,  8,  8,  8,  8,  8,  8,  8,
};
static const struct byte_lookup* const
to_ISO_8859_14_E1_B9_infos[9] = {
     o1(0xB4), o1(0xB5), o1(0xB7), o1(0xB9),
     o1(0xBB), o1(0xBF), o1(0xD7), o1(0xF7),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_E1_B9 = {
    to_ISO_8859_14_E1_B9_offsets,
    to_ISO_8859_14_E1_B9_infos
};

static const unsigned char
to_ISO_8859_14_E1_BA_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
};
static const struct byte_lookup* const
to_ISO_8859_14_E1_BA_infos[7] = {
     o1(0xA8), o1(0xB8), o1(0xAA), o1(0xBA),
     o1(0xBD), o1(0xBE),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_E1_BA = {
    to_ISO_8859_14_E1_BA_offsets,
    to_ISO_8859_14_E1_BA_infos
};

static const unsigned char
to_ISO_8859_14_E1_BB_offsets[64] = {
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  2,  2,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
      2,  2,  0,  1,  2,  2,  2,  2,    2,  2,  2,  2,  2,  2,  2,  2,
};
static const struct byte_lookup* const
to_ISO_8859_14_E1_BB_infos[3] = {
     o1(0xAC), o1(0xBC),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_E1_BB = {
    to_ISO_8859_14_E1_BB_offsets,
    to_ISO_8859_14_E1_BB_infos
};

static const unsigned char
to_ISO_8859_14_E1_offsets[64] = {
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    4,  4,  4,  4,  4,  4,  4,  4,
      4,  4,  4,  4,  4,  4,  4,  4,    0,  1,  2,  3,  4,  4,  4,  4,
};
static const struct byte_lookup* const
to_ISO_8859_14_E1_infos[5] = {
     &to_ISO_8859_14_E1_B8, &to_ISO_8859_14_E1_B9,
     &to_ISO_8859_14_E1_BA, &to_ISO_8859_14_E1_BB,
                     UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14_E1 = {
    to_ISO_8859_14_E1_offsets,
    to_ISO_8859_14_E1_infos
};

static const unsigned char
to_ISO_8859_14_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  1,  2,  3,  4,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  5,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
      6,  6,  6,  6,  6,  6,  6,  6,    6,  6,  6,  6,  6,  6,  6,  6,
};
static const struct byte_lookup* const
to_ISO_8859_14_infos[7] = {
                  NOMAP, &to_ISO_8859_14_C2,
     &to_ISO_8859_14_C3, &to_ISO_8859_14_C4,
     &to_ISO_8859_14_C5, &to_ISO_8859_14_E1,
                  UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_14 = {
    to_ISO_8859_14_offsets,
    to_ISO_8859_14_infos
};

static const rb_transcoder
rb_to_ISO_8859_14 = {
    "UTF-8", "ISO-8859-14", &to_ISO_8859_14, 1, 1,
    NULL, NULL,
};

static const struct byte_lookup* const
from_ISO_8859_15_infos[129] = {
                  NOMAP,      o2(0xC2,0x80),
          o2(0xC2,0x81),      o2(0xC2,0x82),
          o2(0xC2,0x83),      o2(0xC2,0x84),
          o2(0xC2,0x85),      o2(0xC2,0x86),
          o2(0xC2,0x87),      o2(0xC2,0x88),
          o2(0xC2,0x89),      o2(0xC2,0x8A),
          o2(0xC2,0x8B),      o2(0xC2,0x8C),
          o2(0xC2,0x8D),      o2(0xC2,0x8E),
          o2(0xC2,0x8F),      o2(0xC2,0x90),
          o2(0xC2,0x91),      o2(0xC2,0x92),
          o2(0xC2,0x93),      o2(0xC2,0x94),
          o2(0xC2,0x95),      o2(0xC2,0x96),
          o2(0xC2,0x97),      o2(0xC2,0x98),
          o2(0xC2,0x99),      o2(0xC2,0x9A),
          o2(0xC2,0x9B),      o2(0xC2,0x9C),
          o2(0xC2,0x9D),      o2(0xC2,0x9E),
          o2(0xC2,0x9F),      o2(0xC2,0xA0),
          o2(0xC2,0xA1),      o2(0xC2,0xA2),
          o2(0xC2,0xA3), o3(0xE2,0x82,0xAC),
          o2(0xC2,0xA5),      o2(0xC5,0xA0),
          o2(0xC2,0xA7),      o2(0xC5,0xA1),
          o2(0xC2,0xA9),      o2(0xC2,0xAA),
          o2(0xC2,0xAB),      o2(0xC2,0xAC),
          o2(0xC2,0xAD),      o2(0xC2,0xAE),
          o2(0xC2,0xAF),      o2(0xC2,0xB0),
          o2(0xC2,0xB1),      o2(0xC2,0xB2),
          o2(0xC2,0xB3),      o2(0xC5,0xBD),
          o2(0xC2,0xB5),      o2(0xC2,0xB6),
          o2(0xC2,0xB7),      o2(0xC5,0xBE),
          o2(0xC2,0xB9),      o2(0xC2,0xBA),
          o2(0xC2,0xBB),      o2(0xC5,0x92),
          o2(0xC5,0x93),      o2(0xC5,0xB8),
          o2(0xC2,0xBF),      o2(0xC3,0x80),
          o2(0xC3,0x81),      o2(0xC3,0x82),
          o2(0xC3,0x83),      o2(0xC3,0x84),
          o2(0xC3,0x85),      o2(0xC3,0x86),
          o2(0xC3,0x87),      o2(0xC3,0x88),
          o2(0xC3,0x89),      o2(0xC3,0x8A),
          o2(0xC3,0x8B),      o2(0xC3,0x8C),
          o2(0xC3,0x8D),      o2(0xC3,0x8E),
          o2(0xC3,0x8F),      o2(0xC3,0x90),
          o2(0xC3,0x91),      o2(0xC3,0x92),
          o2(0xC3,0x93),      o2(0xC3,0x94),
          o2(0xC3,0x95),      o2(0xC3,0x96),
          o2(0xC3,0x97),      o2(0xC3,0x98),
          o2(0xC3,0x99),      o2(0xC3,0x9A),
          o2(0xC3,0x9B),      o2(0xC3,0x9C),
          o2(0xC3,0x9D),      o2(0xC3,0x9E),
          o2(0xC3,0x9F),      o2(0xC3,0xA0),
          o2(0xC3,0xA1),      o2(0xC3,0xA2),
          o2(0xC3,0xA3),      o2(0xC3,0xA4),
          o2(0xC3,0xA5),      o2(0xC3,0xA6),
          o2(0xC3,0xA7),      o2(0xC3,0xA8),
          o2(0xC3,0xA9),      o2(0xC3,0xAA),
          o2(0xC3,0xAB),      o2(0xC3,0xAC),
          o2(0xC3,0xAD),      o2(0xC3,0xAE),
          o2(0xC3,0xAF),      o2(0xC3,0xB0),
          o2(0xC3,0xB1),      o2(0xC3,0xB2),
          o2(0xC3,0xB3),      o2(0xC3,0xB4),
          o2(0xC3,0xB5),      o2(0xC3,0xB6),
          o2(0xC3,0xB7),      o2(0xC3,0xB8),
          o2(0xC3,0xB9),      o2(0xC3,0xBA),
          o2(0xC3,0xBB),      o2(0xC3,0xBC),
          o2(0xC3,0xBD),      o2(0xC3,0xBE),
          o2(0xC3,0xBF),
};
static const BYTE_LOOKUP
from_ISO_8859_15 = {
    from_ISO_8859_1_offsets,
    from_ISO_8859_15_infos
};

static const rb_transcoder
rb_from_ISO_8859_15 = {
    "ISO-8859-15", "UTF-8", &from_ISO_8859_15, 3, 0,
    NULL, NULL,
};

static const unsigned char
to_ISO_8859_15_C2_offsets[64] = {
      0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15,
     16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 34, 35, 56, 36, 56, 37,   56, 38, 39, 40, 41, 42, 43, 44,
     45, 46, 47, 48, 56, 49, 50, 51,   56, 52, 53, 54, 56, 56, 56, 55,
};
static const struct byte_lookup* const
to_ISO_8859_15_C2_infos[57] = {
     o1(0x80), o1(0x81), o1(0x82), o1(0x83),
     o1(0x84), o1(0x85), o1(0x86), o1(0x87),
     o1(0x88), o1(0x89), o1(0x8A), o1(0x8B),
     o1(0x8C), o1(0x8D), o1(0x8E), o1(0x8F),
     o1(0x90), o1(0x91), o1(0x92), o1(0x93),
     o1(0x94), o1(0x95), o1(0x96), o1(0x97),
     o1(0x98), o1(0x99), o1(0x9A), o1(0x9B),
     o1(0x9C), o1(0x9D), o1(0x9E), o1(0x9F),
     o1(0xA0), o1(0xA1), o1(0xA2), o1(0xA3),
     o1(0xA5), o1(0xA7), o1(0xA9), o1(0xAA),
     o1(0xAB), o1(0xAC), o1(0xAD), o1(0xAE),
     o1(0xAF), o1(0xB0), o1(0xB1), o1(0xB2),
     o1(0xB3), o1(0xB5), o1(0xB6), o1(0xB7),
     o1(0xB9), o1(0xBA), o1(0xBB), o1(0xBF),
        UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_15_C2 = {
    to_ISO_8859_15_C2_offsets,
    to_ISO_8859_15_C2_infos
};

static const unsigned char
to_ISO_8859_15_C5_offsets[64] = {
      7,  7,  7,  7,  7,  7,  7,  7,    7,  7,  7,  7,  7,  7,  7,  7,
      7,  7,  0,  1,  7,  7,  7,  7,    7,  7,  7,  7,  7,  7,  7,  7,
      2,  3,  7,  7,  7,  7,  7,  7,    7,  7,  7,  7,  7,  7,  7,  7,
      7,  7,  7,  7,  7,  7,  7,  7,    4,  7,  7,  7,  7,  5,  6,  7,
};
static const struct byte_lookup* const
to_ISO_8859_15_C5_infos[8] = {
     o1(0xBC), o1(0xBD), o1(0xA6), o1(0xA8),
     o1(0xBE), o1(0xB4), o1(0xB8),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_15_C5 = {
    to_ISO_8859_15_C5_offsets,
    to_ISO_8859_15_C5_infos
};

static const unsigned char
to_ISO_8859_15_E2_82_offsets[64] = {
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  0,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
to_ISO_8859_15_E2_82_infos[2] = {
     o1(0xA4),    UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_15_E2_82 = {
    to_ISO_8859_15_E2_82_offsets,
    to_ISO_8859_15_E2_82_infos
};

static const unsigned char
to_ISO_8859_15_E2_offsets[64] = {
      1,  1,  0,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  1,  1,  1,    1,  1,  1,  1,  1,  1,  1,  1,
};
static const struct byte_lookup* const
to_ISO_8859_15_E2_infos[2] = {
     &to_ISO_8859_15_E2_82,                 UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_15_E2 = {
    to_ISO_8859_15_E2_offsets,
    to_ISO_8859_15_E2_infos
};

static const unsigned char
to_ISO_8859_15_offsets[256] = {
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  1,  2,  5,  3,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  4,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
      5,  5,  5,  5,  5,  5,  5,  5,    5,  5,  5,  5,  5,  5,  5,  5,
};
static const struct byte_lookup* const
to_ISO_8859_15_infos[6] = {
                  NOMAP, &to_ISO_8859_15_C2,
      &to_ISO_8859_1_C3, &to_ISO_8859_15_C5,
     &to_ISO_8859_15_E2,              UNDEF,
};
static const BYTE_LOOKUP
to_ISO_8859_15 = {
    to_ISO_8859_15_offsets,
    to_ISO_8859_15_infos
};

static const rb_transcoder
rb_to_ISO_8859_15 = {
    "UTF-8", "ISO-8859-15", &to_ISO_8859_15, 1, 1,
    NULL, NULL,
};

void
Init_single_byte(void)
{
    rb_register_transcoder(&rb_from_US_ASCII);
    rb_register_transcoder(&rb_to_US_ASCII);
    rb_register_transcoder(&rb_from_ASCII_8BIT);
    rb_register_transcoder(&rb_to_ASCII_8BIT);
    rb_register_transcoder(&rb_from_ISO_8859_1);
    rb_register_transcoder(&rb_to_ISO_8859_1);
    rb_register_transcoder(&rb_from_ISO_8859_2);
    rb_register_transcoder(&rb_to_ISO_8859_2);
    rb_register_transcoder(&rb_from_ISO_8859_3);
    rb_register_transcoder(&rb_to_ISO_8859_3);
    rb_register_transcoder(&rb_from_ISO_8859_4);
    rb_register_transcoder(&rb_to_ISO_8859_4);
    rb_register_transcoder(&rb_from_ISO_8859_5);
    rb_register_transcoder(&rb_to_ISO_8859_5);
    rb_register_transcoder(&rb_from_ISO_8859_6);
    rb_register_transcoder(&rb_to_ISO_8859_6);
    rb_register_transcoder(&rb_from_ISO_8859_7);
    rb_register_transcoder(&rb_to_ISO_8859_7);
    rb_register_transcoder(&rb_from_ISO_8859_8);
    rb_register_transcoder(&rb_to_ISO_8859_8);
    rb_register_transcoder(&rb_from_ISO_8859_9);
    rb_register_transcoder(&rb_to_ISO_8859_9);
    rb_register_transcoder(&rb_from_ISO_8859_10);
    rb_register_transcoder(&rb_to_ISO_8859_10);
    rb_register_transcoder(&rb_from_ISO_8859_11);
    rb_register_transcoder(&rb_to_ISO_8859_11);
    rb_register_transcoder(&rb_from_ISO_8859_13);
    rb_register_transcoder(&rb_to_ISO_8859_13);
    rb_register_transcoder(&rb_from_ISO_8859_14);
    rb_register_transcoder(&rb_to_ISO_8859_14);
    rb_register_transcoder(&rb_from_ISO_8859_15);
    rb_register_transcoder(&rb_to_ISO_8859_15);
}
/* Footprint (bytes): gross: 27876, saved: 4544, net: 23332 */
