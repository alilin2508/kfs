#ifndef HELPERS_H
# define HELPERS_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "types.h"

#define GDTBASE 0x00000800

struct gdtr { // structure GDTR qui pointe vers la GDT
    u16 limite;
    u32 base; // adresse de la struct GDT
} __attribute__ ((packed));

struct gdtdescriptor { // protected mode flat/long model descriptor
    u16 limit;
    u16 base_low;
    u8 base_middle;
    u8 access_byte;
    u8 limit_high:4;
    u8 flags:4;
    u8 base_high;
} __attribute__ ((packed));

size_t  strlen(const char* str);
int     strncmp(const char *s1, const char *s2, size_t n);
void    *memcpy(void *dst, const void *src, size_t n);
void    init_gdt_descriptor(u32 base, u32 limit, u8 access_byte, u8 flags, struct gdtdescriptor *segment_descriptor);
// void    init_gdt();

#endif

