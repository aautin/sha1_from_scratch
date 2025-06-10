#include <stdio.h>

#include "list.h"

void print_chunks(t_list* message)
{
	printf("Message:\n");
	while (message) {
		if (message->next == NULL) {
			size_t i;
			for (i = 0; i < 64; ++i)
				printf("%#08x ", message->chunk.bytes[i]);
			printf("\nlength = %ld\n", message->chunk.len.it);
		}
		else {
			for (int i = 0; i < 64; ++i)
				printf("%#08x", message->chunk.bytes[i]);
			printf("<->");
		}
		message = message->next;
	}
	printf("\n");
}
