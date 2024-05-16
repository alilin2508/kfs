#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <utils.h>

#define WIDTH 16

void hexdump(const void *addr, size_t size) {
	const unsigned char *p = addr;
	for (size_t i = 0; i < size; i += WIDTH) {
		printf("%08x  ", (uint32_t)(p + i));
		for (size_t j = 0; j < WIDTH; ++j) {
			if (i + j < size)
				printf("%02x ", p[i + j]);
			else
				printf("   ");
			if (j == WIDTH / 2 - 1)
				putchar(' ');
		}
		printf(" |");
		for (size_t j = 0; j < WIDTH; ++j) {
			if (i + j < size)
				putchar(isprint(p[i + j]) ? p[i + j] : '.');
			else
				putchar(' ');
		}
		printf("|\n");
	}
}
