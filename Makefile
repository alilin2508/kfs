NAME    = myos.iso
RM      = rm      -rf
CC      = ~/opt/cross/bin/i386-elf-gcc
AS	= ~/opt/cross/bin/i386-elf-as
FLAGS   = -std=gnu99 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs -O2 -Wall -Wextra

CSRCS 	:= ./srcs/kernel.c

ASSRCS	:= ./srcs/boot.s

LDSRCS	:= ./srcs/linker.ld

OBJS    := ${CSRCS:.c=.o} ${ASSRCS:.s=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

%.o: %.s
	@$(AS) $< -o $@

$(NAME): $(OBJS)
	@$(CC) -T $(LDSRCS) -o myos.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc
	@mv myos.bin ./isodir/boot
	@grub-mkrescue --xorriso=/etc/xorriso-1.5.4/xorriso/xorriso -o $(NAME) isodir

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) ./isodir/boot/myos.bin

re:	fclean all

launch: 
	@qemu-system-i386 -cdrom myos.iso

