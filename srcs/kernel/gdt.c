#include <string.h>
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

// Var globale
struct gdtr kgdtr;
struct gdtdescriptor kgdt[7];

/* Cette fonction initialise la GDT apres que le kernel soit charge en memoire. Une GDT est deja operationnelle, mais c'est celle qui
 a ete initialisee par le secteur de boot et qui ne correspond pas forcement a celle que l'on souhaite. */
void init_gdt(void)
{   
    // initialisation des descripteurs de segments
    init_gdt_descriptor(0x0, 0x0, 0x0, 0x0, &kgdt[0]); // null descriptor
    init_gdt_descriptor(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]); // kernel code
    init_gdt_descriptor(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]); // kernel data
    init_gdt_descriptor(0x0, 0x0, 0x97, 0x0D, &kgdt[3]); // kernel stack

    init_gdt_descriptor(0x0, 0xFFFFF, 0xFF, 0x0D, &kgdt[4]); // user code
    init_gdt_descriptor(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[5]); // user data
    init_gdt_descriptor(0x0, 0x0, 0xF7, 0x0D, &kgdt[6]); // user stack

    // inititialisation de la structure qui pointe vers la gdt
    kgdtr.limite = sizeof(struct gdtdescriptor) * 7;
    kgdtr.base = GDTBASE;

    // copie de la gdt à son addresse
    memcpy((char *)kgdtr.base, (char *)kgdt, kgdtr.limite);

    // assembleur inline
    // load du registry gdt avec lgdt (local gdt)
    asm("lgdtl (kgdtr)");

    // initialisation segments mémoire
    asm("   movw $0x10, %ax    \n \
            movw %ax, %ds    \n \
            movw %ax, %es    \n \
            movw %ax, %fs    \n \
            movw %ax, %gs    \n \
            movw %ax, %ss    \n \
            ljmp $0x08, $next    \n \
            next:        \n");
}
