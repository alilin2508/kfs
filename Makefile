NAME    = myos.iso
RM      = rm -rf
CC      = gcc
FLAGS   = -m32 -march=i386 -ffreestanding -fno-stack-protector -nodefaultlibs -nostdlib -Wall -Wextra

DIR_INC = -I ./includes/kernel -I ./includes/libc

CSRCS	:= 	./srcs/ctype/isdigit.c \
			./srcs/ctype/islower.c \
			./srcs/ctype/isprint.c \
			./srcs/ctype/isupper.c \
			./srcs/ctype/tolower.c \
			./srcs/ctype/toupper.c \
			./srcs/kernel/gdt.c \
			./srcs/kernel/main.c \
			./srcs/kernel/stack.c \
			./srcs/kernel/tty.c \
			./srcs/kernel/utils.c \
			./srcs/kernel/vga.c \
			./srcs/stdio/__parse_format.c \
			./srcs/stdio/printf.c \
			./srcs/stdio/putchar.c \
			./srcs/stdio/puts.c \
			./srcs/stdio/snprintf.c \
			./srcs/stdio/sprintf.c \
			./srcs/stdio/vprintf.c \
			./srcs/stdio/vsnprintf.c \
			./srcs/stdio/vsprintf.c \
			./srcs/string/memcpy.c \
			./srcs/string/strchr.c \
			./srcs/string/strlen.c \
			./srcs/string/strncmp.c

ASSRCS	:= 	./srcs/boot.s

LDFLAGS	:= 	-T ./srcs/linker.ld

OBJS    := ${CSRCS:.c=.o} ${ASSRCS:.s=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(DIR_INC) -c $< -o $@

%.o: %.s
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(DIR_INC) -o myos.bin $(FLAGS) $(OBJS) $(LDFLAGS)
	mv myos.bin ./isodir/boot
	grub-mkrescue -o $(NAME) isodir

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME) ./isodir/boot/myos.bin

re:	fclean all

launch: 
	qemu-system-i386 -cdrom myos.iso

