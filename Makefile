NAME    = myos.iso
RM      = rm      -rf
CC      = i686-elf-gcc
AS	= i686-elf-as
FLAGS   = -std=gnu99 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -O2 -Wall -Wextra

DIR_INC = -I ./includes/

CSRCS 	:= 	./srcs/helpers.c \
		./srcs/kernel.c

ASSRCS	:= 	./srcs/boot.s

LDSRCS	:= 	./srcs/linker.ld

OBJS    := ${CSRCS:.c=.o} ${ASSRCS:.s=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(DIR_INC) -c $< -o $@

%.o: %.s
	@$(AS) $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(DIR_INC) -T $(LDSRCS) -o myos.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc
	@mv myos.bin ./isodir/boot
	@grub-mkrescue -o $(NAME) isodir

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) ./isodir/boot/myos.bin

re:	fclean all

launch: 
	@qemu-system-i386 -cdrom myos.iso

