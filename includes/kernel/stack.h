#ifndef STACK_H
# define STACK_H

# include <stdint.h>

#define MAX_STACK_FRAMES 10

typedef struct s_stackframe t_stackframe;
struct s_stackframe {
	t_stackframe* ebp;
	uint32_t eip;
};

void print_stack();

#endif

