#include <stdio.h>

#include "list.h"

void print_chunks(t_list* message)
{
	printf("Message:\n");
	while (message) {
		if (message->next == NULL) {
			size_t i;
			for (i = 0; i < 55 && message->chunk.bytes[i] != 0; ++i)
				printf("%c", message->chunk.bytes[i]);
			printf("length = %ld\n", message->chunk.len.it);
		}
		else {
			for (int i = 0; i < 64; ++i)
				printf("%c", message->chunk.bytes[i]);
			printf("<->");
		}
		message = message->next;
	}
	printf("\n");
}
