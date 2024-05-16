#ifndef GDT_H
# define GDT_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define GDTBASE 0x00000800
# define GDTDESCNUM 7

struct gdtr { // structure GDTR qui pointe vers la GDT
    uint16_t limite;
    uint32_t base; // adresse de la struct GDT
} __attribute__ ((packed));

struct gdtdescriptor { // protected mode flat/long model descriptor
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access_byte;
    uint8_t limit_high:4;
    uint8_t flags:4;
    uint8_t base_high;
} __attribute__ ((packed));

void    init_gdt_descriptor(uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags, struct gdtdescriptor *segment_descriptor);
void    init_gdt();

#endif

