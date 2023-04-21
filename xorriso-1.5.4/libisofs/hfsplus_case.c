/*
 * Copyright (c) 2012 Thomas Schmitt
 * 
 * This file is part of the libisofs project; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * or later as published by the Free Software Foundation.
 * See COPYING file for details.
 */

/**
 * Maps UTF-16BE double-byte characters to the representative of their
 * equivalence class under the relation of HFS+ case-insensitivity.
 */

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#include "libisofs.h"


/* The translation list utf16be_transl was generated by a program which
   compared input and output of existing example code by Apple Inc.
   found published on
     http://developer.apple.com/legacy/mac/library/#technotes/tn/tn1150.html

   Each deviation was recorded as pair of byte pairs. The first pair gives
   the input, the second pair gives the output. If a byte pair is not mentioned
   in this list as input, then it gets mapped to itself.
   Pairs which get mapped to pair 0,0 shall be ignored with HFS+ comparisons.

   Another comparison run verified that both implementations yield the same
   character translation with all 65536 possible input bit patterns.
*/
static uint8_t utf16be_transl[] = {
  0x00, 0x00,  0xff, 0xff,
  0x00, 0x41,  0x00, 0x61,
  0x00, 0x42,  0x00, 0x62,
  0x00, 0x43,  0x00, 0x63,
  0x00, 0x44,  0x00, 0x64,
  0x00, 0x45,  0x00, 0x65,
  0x00, 0x46,  0x00, 0x66,
  0x00, 0x47,  0x00, 0x67,
  0x00, 0x48,  0x00, 0x68,
  0x00, 0x49,  0x00, 0x69,
  0x00, 0x4a,  0x00, 0x6a,
  0x00, 0x4b,  0x00, 0x6b,
  0x00, 0x4c,  0x00, 0x6c,
  0x00, 0x4d,  0x00, 0x6d,
  0x00, 0x4e,  0x00, 0x6e,
  0x00, 0x4f,  0x00, 0x6f,
  0x00, 0x50,  0x00, 0x70,
  0x00, 0x51,  0x00, 0x71,
  0x00, 0x52,  0x00, 0x72,
  0x00, 0x53,  0x00, 0x73,
  0x00, 0x54,  0x00, 0x74,
  0x00, 0x55,  0x00, 0x75,
  0x00, 0x56,  0x00, 0x76,
  0x00, 0x57,  0x00, 0x77,
  0x00, 0x58,  0x00, 0x78,
  0x00, 0x59,  0x00, 0x79,
  0x00, 0x5a,  0x00, 0x7a,
  0x00, 0xc6,  0x00, 0xe6,
  0x00, 0xd0,  0x00, 0xf0,
  0x00, 0xd8,  0x00, 0xf8,
  0x00, 0xde,  0x00, 0xfe,
  0x01, 0x10,  0x01, 0x11,
  0x01, 0x26,  0x01, 0x27,
  0x01, 0x32,  0x01, 0x33,
  0x01, 0x3f,  0x01, 0x40,
  0x01, 0x41,  0x01, 0x42,
  0x01, 0x4a,  0x01, 0x4b,
  0x01, 0x52,  0x01, 0x53,
  0x01, 0x66,  0x01, 0x67,
  0x01, 0x81,  0x02, 0x53,
  0x01, 0x82,  0x01, 0x83,
  0x01, 0x84,  0x01, 0x85,
  0x01, 0x86,  0x02, 0x54,
  0x01, 0x87,  0x01, 0x88,
  0x01, 0x89,  0x02, 0x56,
  0x01, 0x8a,  0x02, 0x57,
  0x01, 0x8b,  0x01, 0x8c,
  0x01, 0x8e,  0x01, 0xdd,
  0x01, 0x8f,  0x02, 0x59,
  0x01, 0x90,  0x02, 0x5b,
  0x01, 0x91,  0x01, 0x92,
  0x01, 0x93,  0x02, 0x60,
  0x01, 0x94,  0x02, 0x63,
  0x01, 0x96,  0x02, 0x69,
  0x01, 0x97,  0x02, 0x68,
  0x01, 0x98,  0x01, 0x99,
  0x01, 0x9c,  0x02, 0x6f,
  0x01, 0x9d,  0x02, 0x72,
  0x01, 0x9f,  0x02, 0x75,
  0x01, 0xa2,  0x01, 0xa3,
  0x01, 0xa4,  0x01, 0xa5,
  0x01, 0xa7,  0x01, 0xa8,
  0x01, 0xa9,  0x02, 0x83,
  0x01, 0xac,  0x01, 0xad,
  0x01, 0xae,  0x02, 0x88,
  0x01, 0xb1,  0x02, 0x8a,
  0x01, 0xb2,  0x02, 0x8b,
  0x01, 0xb3,  0x01, 0xb4,
  0x01, 0xb5,  0x01, 0xb6,
  0x01, 0xb7,  0x02, 0x92,
  0x01, 0xb8,  0x01, 0xb9,
  0x01, 0xbc,  0x01, 0xbd,
  0x01, 0xc4,  0x01, 0xc6,
  0x01, 0xc5,  0x01, 0xc6,
  0x01, 0xc7,  0x01, 0xc9,
  0x01, 0xc8,  0x01, 0xc9,
  0x01, 0xca,  0x01, 0xcc,
  0x01, 0xcb,  0x01, 0xcc,
  0x01, 0xe4,  0x01, 0xe5,
  0x01, 0xf1,  0x01, 0xf3,
  0x01, 0xf2,  0x01, 0xf3,
  0x03, 0x91,  0x03, 0xb1,
  0x03, 0x92,  0x03, 0xb2,
  0x03, 0x93,  0x03, 0xb3,
  0x03, 0x94,  0x03, 0xb4,
  0x03, 0x95,  0x03, 0xb5,
  0x03, 0x96,  0x03, 0xb6,
  0x03, 0x97,  0x03, 0xb7,
  0x03, 0x98,  0x03, 0xb8,
  0x03, 0x99,  0x03, 0xb9,
  0x03, 0x9a,  0x03, 0xba,
  0x03, 0x9b,  0x03, 0xbb,
  0x03, 0x9c,  0x03, 0xbc,
  0x03, 0x9d,  0x03, 0xbd,
  0x03, 0x9e,  0x03, 0xbe,
  0x03, 0x9f,  0x03, 0xbf,
  0x03, 0xa0,  0x03, 0xc0,
  0x03, 0xa1,  0x03, 0xc1,
  0x03, 0xa3,  0x03, 0xc3,
  0x03, 0xa4,  0x03, 0xc4,
  0x03, 0xa5,  0x03, 0xc5,
  0x03, 0xa6,  0x03, 0xc6,
  0x03, 0xa7,  0x03, 0xc7,
  0x03, 0xa8,  0x03, 0xc8,
  0x03, 0xa9,  0x03, 0xc9,
  0x03, 0xe2,  0x03, 0xe3,
  0x03, 0xe4,  0x03, 0xe5,
  0x03, 0xe6,  0x03, 0xe7,
  0x03, 0xe8,  0x03, 0xe9,
  0x03, 0xea,  0x03, 0xeb,
  0x03, 0xec,  0x03, 0xed,
  0x03, 0xee,  0x03, 0xef,
  0x04, 0x02,  0x04, 0x52,
  0x04, 0x04,  0x04, 0x54,
  0x04, 0x05,  0x04, 0x55,
  0x04, 0x06,  0x04, 0x56,
  0x04, 0x08,  0x04, 0x58,
  0x04, 0x09,  0x04, 0x59,
  0x04, 0x0a,  0x04, 0x5a,
  0x04, 0x0b,  0x04, 0x5b,
  0x04, 0x0f,  0x04, 0x5f,
  0x04, 0x10,  0x04, 0x30,
  0x04, 0x11,  0x04, 0x31,
  0x04, 0x12,  0x04, 0x32,
  0x04, 0x13,  0x04, 0x33,
  0x04, 0x14,  0x04, 0x34,
  0x04, 0x15,  0x04, 0x35,
  0x04, 0x16,  0x04, 0x36,
  0x04, 0x17,  0x04, 0x37,
  0x04, 0x18,  0x04, 0x38,
  0x04, 0x1a,  0x04, 0x3a,
  0x04, 0x1b,  0x04, 0x3b,
  0x04, 0x1c,  0x04, 0x3c,
  0x04, 0x1d,  0x04, 0x3d,
  0x04, 0x1e,  0x04, 0x3e,
  0x04, 0x1f,  0x04, 0x3f,
  0x04, 0x20,  0x04, 0x40,
  0x04, 0x21,  0x04, 0x41,
  0x04, 0x22,  0x04, 0x42,
  0x04, 0x23,  0x04, 0x43,
  0x04, 0x24,  0x04, 0x44,
  0x04, 0x25,  0x04, 0x45,
  0x04, 0x26,  0x04, 0x46,
  0x04, 0x27,  0x04, 0x47,
  0x04, 0x28,  0x04, 0x48,
  0x04, 0x29,  0x04, 0x49,
  0x04, 0x2a,  0x04, 0x4a,
  0x04, 0x2b,  0x04, 0x4b,
  0x04, 0x2c,  0x04, 0x4c,
  0x04, 0x2d,  0x04, 0x4d,
  0x04, 0x2e,  0x04, 0x4e,
  0x04, 0x2f,  0x04, 0x4f,
  0x04, 0x60,  0x04, 0x61,
  0x04, 0x62,  0x04, 0x63,
  0x04, 0x64,  0x04, 0x65,
  0x04, 0x66,  0x04, 0x67,
  0x04, 0x68,  0x04, 0x69,
  0x04, 0x6a,  0x04, 0x6b,
  0x04, 0x6c,  0x04, 0x6d,
  0x04, 0x6e,  0x04, 0x6f,
  0x04, 0x70,  0x04, 0x71,
  0x04, 0x72,  0x04, 0x73,
  0x04, 0x74,  0x04, 0x75,
  0x04, 0x78,  0x04, 0x79,
  0x04, 0x7a,  0x04, 0x7b,
  0x04, 0x7c,  0x04, 0x7d,
  0x04, 0x7e,  0x04, 0x7f,
  0x04, 0x80,  0x04, 0x81,
  0x04, 0x90,  0x04, 0x91,
  0x04, 0x92,  0x04, 0x93,
  0x04, 0x94,  0x04, 0x95,
  0x04, 0x96,  0x04, 0x97,
  0x04, 0x98,  0x04, 0x99,
  0x04, 0x9a,  0x04, 0x9b,
  0x04, 0x9c,  0x04, 0x9d,
  0x04, 0x9e,  0x04, 0x9f,
  0x04, 0xa0,  0x04, 0xa1,
  0x04, 0xa2,  0x04, 0xa3,
  0x04, 0xa4,  0x04, 0xa5,
  0x04, 0xa6,  0x04, 0xa7,
  0x04, 0xa8,  0x04, 0xa9,
  0x04, 0xaa,  0x04, 0xab,
  0x04, 0xac,  0x04, 0xad,
  0x04, 0xae,  0x04, 0xaf,
  0x04, 0xb0,  0x04, 0xb1,
  0x04, 0xb2,  0x04, 0xb3,
  0x04, 0xb4,  0x04, 0xb5,
  0x04, 0xb6,  0x04, 0xb7,
  0x04, 0xb8,  0x04, 0xb9,
  0x04, 0xba,  0x04, 0xbb,
  0x04, 0xbc,  0x04, 0xbd,
  0x04, 0xbe,  0x04, 0xbf,
  0x04, 0xc3,  0x04, 0xc4,
  0x04, 0xc7,  0x04, 0xc8,
  0x04, 0xcb,  0x04, 0xcc,
  0x05, 0x31,  0x05, 0x61,
  0x05, 0x32,  0x05, 0x62,
  0x05, 0x33,  0x05, 0x63,
  0x05, 0x34,  0x05, 0x64,
  0x05, 0x35,  0x05, 0x65,
  0x05, 0x36,  0x05, 0x66,
  0x05, 0x37,  0x05, 0x67,
  0x05, 0x38,  0x05, 0x68,
  0x05, 0x39,  0x05, 0x69,
  0x05, 0x3a,  0x05, 0x6a,
  0x05, 0x3b,  0x05, 0x6b,
  0x05, 0x3c,  0x05, 0x6c,
  0x05, 0x3d,  0x05, 0x6d,
  0x05, 0x3e,  0x05, 0x6e,
  0x05, 0x3f,  0x05, 0x6f,
  0x05, 0x40,  0x05, 0x70,
  0x05, 0x41,  0x05, 0x71,
  0x05, 0x42,  0x05, 0x72,
  0x05, 0x43,  0x05, 0x73,
  0x05, 0x44,  0x05, 0x74,
  0x05, 0x45,  0x05, 0x75,
  0x05, 0x46,  0x05, 0x76,
  0x05, 0x47,  0x05, 0x77,
  0x05, 0x48,  0x05, 0x78,
  0x05, 0x49,  0x05, 0x79,
  0x05, 0x4a,  0x05, 0x7a,
  0x05, 0x4b,  0x05, 0x7b,
  0x05, 0x4c,  0x05, 0x7c,
  0x05, 0x4d,  0x05, 0x7d,
  0x05, 0x4e,  0x05, 0x7e,
  0x05, 0x4f,  0x05, 0x7f,
  0x05, 0x50,  0x05, 0x80,
  0x05, 0x51,  0x05, 0x81,
  0x05, 0x52,  0x05, 0x82,
  0x05, 0x53,  0x05, 0x83,
  0x05, 0x54,  0x05, 0x84,
  0x05, 0x55,  0x05, 0x85,
  0x05, 0x56,  0x05, 0x86,
  0x10, 0xa0,  0x10, 0xd0,
  0x10, 0xa1,  0x10, 0xd1,
  0x10, 0xa2,  0x10, 0xd2,
  0x10, 0xa3,  0x10, 0xd3,
  0x10, 0xa4,  0x10, 0xd4,
  0x10, 0xa5,  0x10, 0xd5,
  0x10, 0xa6,  0x10, 0xd6,
  0x10, 0xa7,  0x10, 0xd7,
  0x10, 0xa8,  0x10, 0xd8,
  0x10, 0xa9,  0x10, 0xd9,
  0x10, 0xaa,  0x10, 0xda,
  0x10, 0xab,  0x10, 0xdb,
  0x10, 0xac,  0x10, 0xdc,
  0x10, 0xad,  0x10, 0xdd,
  0x10, 0xae,  0x10, 0xde,
  0x10, 0xaf,  0x10, 0xdf,
  0x10, 0xb0,  0x10, 0xe0,
  0x10, 0xb1,  0x10, 0xe1,
  0x10, 0xb2,  0x10, 0xe2,
  0x10, 0xb3,  0x10, 0xe3,
  0x10, 0xb4,  0x10, 0xe4,
  0x10, 0xb5,  0x10, 0xe5,
  0x10, 0xb6,  0x10, 0xe6,
  0x10, 0xb7,  0x10, 0xe7,
  0x10, 0xb8,  0x10, 0xe8,
  0x10, 0xb9,  0x10, 0xe9,
  0x10, 0xba,  0x10, 0xea,
  0x10, 0xbb,  0x10, 0xeb,
  0x10, 0xbc,  0x10, 0xec,
  0x10, 0xbd,  0x10, 0xed,
  0x10, 0xbe,  0x10, 0xee,
  0x10, 0xbf,  0x10, 0xef,
  0x10, 0xc0,  0x10, 0xf0,
  0x10, 0xc1,  0x10, 0xf1,
  0x10, 0xc2,  0x10, 0xf2,
  0x10, 0xc3,  0x10, 0xf3,
  0x10, 0xc4,  0x10, 0xf4,
  0x10, 0xc5,  0x10, 0xf5,
  0x20, 0x0c,  0x00, 0x00,
  0x20, 0x0d,  0x00, 0x00,
  0x20, 0x0e,  0x00, 0x00,
  0x20, 0x0f,  0x00, 0x00,
  0x20, 0x2a,  0x00, 0x00,
  0x20, 0x2b,  0x00, 0x00,
  0x20, 0x2c,  0x00, 0x00,
  0x20, 0x2d,  0x00, 0x00,
  0x20, 0x2e,  0x00, 0x00,
  0x20, 0x6a,  0x00, 0x00,
  0x20, 0x6b,  0x00, 0x00,
  0x20, 0x6c,  0x00, 0x00,
  0x20, 0x6d,  0x00, 0x00,
  0x20, 0x6e,  0x00, 0x00,
  0x20, 0x6f,  0x00, 0x00,
  0x21, 0x60,  0x21, 0x70,
  0x21, 0x61,  0x21, 0x71,
  0x21, 0x62,  0x21, 0x72,
  0x21, 0x63,  0x21, 0x73,
  0x21, 0x64,  0x21, 0x74,
  0x21, 0x65,  0x21, 0x75,
  0x21, 0x66,  0x21, 0x76,
  0x21, 0x67,  0x21, 0x77,
  0x21, 0x68,  0x21, 0x78,
  0x21, 0x69,  0x21, 0x79,
  0x21, 0x6a,  0x21, 0x7a,
  0x21, 0x6b,  0x21, 0x7b,
  0x21, 0x6c,  0x21, 0x7c,
  0x21, 0x6d,  0x21, 0x7d,
  0x21, 0x6e,  0x21, 0x7e,
  0x21, 0x6f,  0x21, 0x7f,
  0xfe, 0xff,  0x00, 0x00,
  0xff, 0x21,  0xff, 0x41,
  0xff, 0x22,  0xff, 0x42,
  0xff, 0x23,  0xff, 0x43,
  0xff, 0x24,  0xff, 0x44,
  0xff, 0x25,  0xff, 0x45,
  0xff, 0x26,  0xff, 0x46,
  0xff, 0x27,  0xff, 0x47,
  0xff, 0x28,  0xff, 0x48,
  0xff, 0x29,  0xff, 0x49,
  0xff, 0x2a,  0xff, 0x4a,
  0xff, 0x2b,  0xff, 0x4b,
  0xff, 0x2c,  0xff, 0x4c,
  0xff, 0x2d,  0xff, 0x4d,
  0xff, 0x2e,  0xff, 0x4e,
  0xff, 0x2f,  0xff, 0x4f,
  0xff, 0x30,  0xff, 0x50,
  0xff, 0x31,  0xff, 0x51,
  0xff, 0x32,  0xff, 0x52,
  0xff, 0x33,  0xff, 0x53,
  0xff, 0x34,  0xff, 0x54,
  0xff, 0x35,  0xff, 0x55,
  0xff, 0x36,  0xff, 0x56,
  0xff, 0x37,  0xff, 0x57,
  0xff, 0x38,  0xff, 0x58,
  0xff, 0x39,  0xff, 0x59,
  0xff, 0x3a,  0xff, 0x5a,
  0x00
};
static int utf16be_transl_count = 329;

/* These are the start indice in utf16be_transl[] for the page numbers 0 to 9
   as classified by function what_page().
   As soon as the first byte of the input pair in utf16be_transl[] changes,
   the search can be ended and output is equal to input.
   If page -1 is returned by what_page(), then input is equal to output.
*/
static int utf16be_transl_starts[] = {
  0, 31, 81, 112, 195, 233, 271, 286, 302, 303
};


static int what_page(uint16_t x)
{
    switch(((uint8_t *) &x)[0]) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 3:
        return 2;
    case 4:
        return 3;
    case 5:
        return 4;
    case 16:
        return 5;
    case 32:
        return 6;
    case 33:
        return 7;
    case 254:
        return 8;
    case 255:
        return 9;
    default:
        return -1; /* no mapping */
    }
}


/* Accelerator for the ASCII subset which is expected to be the most
   frequently used one.
*/
static uint16_t cmp_name_page0(uint16_t x)
{
    uint8_t *low;

    low = ((uint8_t *) &x) + 1;
    
    if (x == 0)
        return 0xffff;
    if (*low <= 0x40)
        ; 
    else if (*low <= 0x5a)
        *low = *low + 0x20;
    else if (*low < 0xc6)
        ;
    else if (*low == 0xc6)
        *low = 0xe6;
    else if (*low == 0xd0)
        *low = 0xf0;
    else if (*low == 0xd8)
        *low = 0xf8;
    else if (*low == 0xde)
        *low = 0xfe;
    return x;
}


/* Converts a character into the representative of its HFS+ equivalence
   class.
   @param x The UTF-16BE character to be converted. 
   @return  0 = ignore character with comparisons
            else the case-insensitive character.
*/
uint16_t iso_hfsplus_cichar(uint16_t x)
{
    int page, i;
    uint16_t ret;
    uint8_t low, high;

    high = ((uint8_t *) &x)[0];
    low = ((uint8_t *) &x)[1];

    page = what_page(x);
    if (page < 0)
        return x; /* No translation needed */
    if (page == 0)
        return cmp_name_page0(x); /* Accelerator for ASCII subset */

    for (i = utf16be_transl_starts[page] * 4; i < utf16be_transl_count * 4;
         i += 4) {
        if (utf16be_transl[i] != high)
    break;
        if (utf16be_transl[i + 1] == low) { 
            ((uint8_t *) &ret)[0] = utf16be_transl[i + 2];
            ((uint8_t *) &ret)[1] = utf16be_transl[i + 3];
            return ret;
        }
    }
    return x;
}


