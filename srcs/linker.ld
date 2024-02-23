/* le linker permet de créer un seul exécutable (kernel) à partir des deux objets: header de boot et fichier d'implémentation kernel */
/* le bootloader exécutera l'image à partir du symbole _start */
ENTRY(_start)

/* déclaration de là où les différentes sections des fichier objet vont se trouver dans l'executable kernel */
SECTIONS
{
	. = 2M;

	/* header de multiboot puis section text */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
 
	/* read-only data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* read-write data initialisée */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* read-write data non initialisée et la stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
