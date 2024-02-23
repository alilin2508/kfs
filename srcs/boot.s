/* Le header contient des informations telles que la taille du kernel ou les segments mémoires du système.
Ici on instancie le header de multiboot à l'aide de la magic value, reconnue par le bootloader (GRUB).
Le multiboot permet d'éliminer la nécessité d'avoir un header de seulement 510 bytes qui se termine par 0x55AA pour etre reconnu.
*/
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO /* flag de multiboot */
.set MAGIC,    0x1BADB002 /* 'magic number' qui permet au bootloader de trouver et reconnaitre le header */
.set CHECKSUM, -(MAGIC + FLAGS) /* cette somme permet de prouver que c'est un header multiboot */

/* déclaration du header de multiboot */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* allocation d'une petite stack de 16384 bytes */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:

	/* setup de stack */
	mov $stack_top, %esp

	/* appel du kernel */
	call kernel_main

	/* disable les interrupts */
	cli
	/* attend un interrupts */
1:	hlt
	jmp 1b /* a pour conséquence un kernel qui tourne a l'infini */

.size _start, . - _start
