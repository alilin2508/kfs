NAME    = myos.iso
RM      = rm      -rf
CC      = $TARGET-gcc
AS		= $TARGET-as
FLAGS   = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

CSRCS 	:= 	kernel.c

ASSRCS	:=	boot.s

LDSRCS	:=	linker.ld

DIR_SRCS 	= ./srcs

DIR_OBJ1	= obj
DIR_OBJ2	= obj

OBJS1       := $(addprefix ${DIR_OBJ1}/, ${CSRCS:.c=.o})
OBJS2		:= $(addprefix ${DIR_OBJ2}/, ${ASSRCS:.s=.o})

all: $(NAME)

$(DIR_OBJ1)/%.o:	$(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

$(DIR_OBJ2)/%.o:	$(DIR_SRCS)/%.s
	@mkdir -p $(dir $@)
	@$(AS) -o $@

$(NAME): $(OBJS1) $(OBJS2)
	@$(CC) -T $(LDSRCS) -o myos.bin -ffreestanding -O2 -nostdlib $(OBJS1) $(OBJS2) -lgcc
	@mv myos.bin ./isodir/boot
	@grub-mkrescue --xorriso=/etc/xorriso-1.5.4/xorriso/xorriso -o $(NAME) isodir

clean:
	@$(RM) $(DIR_OBJ1) $(DIR_OBJ2)

fclean:		clean
	@$(RM) $(NAME)
	@$(RM) ./isodir/boot/myos.bin

re:	fclean all