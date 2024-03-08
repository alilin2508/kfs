#include "gdt.h"

void init_gdt_descriptor(uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags, struct gdtdescriptor *segment_descriptor) // chaque descripteur fait 8 bytes
{
    // base: là où le segment commence
    // limit: sa taille ou son offset
    // access byte: privilèges d'accès au segment
    // flags contient le set up de granularité (définit la taille des blocks qui composent le segment) ou encore si on est en long mode ou pas

    segment_descriptor->limit = (limit & 0xffff);
    segment_descriptor->base_low = (base & 0xffff);
    segment_descriptor->base_middle = (base & 0xff0000) >> 16;
    segment_descriptor->access_byte = access_byte;
    segment_descriptor->limit_high = (limit & 0xf0000) >> 16;
    segment_descriptor->flags = (flags & 0xf);
    segment_descriptor->base_high = (base & 0xff000000) >> 24;
    return;
}

/* Pourquoi Long protected mode: If you do not desire to use Segmentation to separate memory into protected areas, you can get away with using only a few segment descriptors.
One reason may be that you desire to only use paging to protect memory. As well, this model is strictly enforced in Long Mode, as the BASE AND LIMIT VALUES ARE IGNORED.*/

void init_gdt()
{
    
}
