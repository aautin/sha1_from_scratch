#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "chunk.h"
#include "list.h"
#include "parsing.h"

char* get_content_from_fd(int fd)
{
	struct stat	stats;
	fstat(fd, &stats);

	char*	content = malloc((stats.st_size + 1) * sizeof(char));
	if (content == NULL)
		return NULL;

	ssize_t	read_chars = read(fd, content, stats.st_size);
	if (read_chars < 0) {
		free(content);
		return NULL;
	}
	content[read_chars] = '\0';

	return content;
}

void mark_chunk(uint8_t* chunk_bytes, size_t prev_index)
{
	size_t byte_index = (prev_index + 1) / 8;
	size_t bit_position = (prev_index + 1) % 8;

	chunk_bytes[byte_index] |= (1 << bit_position);
}

size_t put_bits_in_chunk(uint8_t* chunk, char* src, size_t put_length)
{
	size_t index = 0;
	while (index < put_length && index < 512) {
		size_t	byte_index = (512 - index + 1) / 8;
		size_t	bit_position = (512 - index + 1) % 8;
		bool	value = *src; // To be continued

		chunk[byte_index] |= (value << bit_position);
	}

	return index;
}

t_list* get_msg_from_content(char* content)
{
	t_list*	msg = NULL;
	bool	is_marked = false;
	size_t	length = strlen(content);
	
	size_t	bits_length = length * 8;
	while ((bits_length + !is_marked) > 448) {
		t_chunk	chunk;
		memset(&chunk, 0, sizeof(t_chunk));

		size_t	bits_put = put_bits_in_chunk(chunk.bytes, content, bits_length);
		bits_length -= bits_put;

		if (!is_marked && bits_length == 0 && bits_put < 512) {
			mark_chunk(chunk.bytes, 512 - bits_put + 1);
			is_marked = true;
		}

		addback_element(&msg, new_element(chunk));
	}

	{
		t_chunk	chunk;
		memset(&chunk, 0, sizeof(t_chunk));
	
		size_t	bits_put = put_bits_in_chunk(chunk.bytes, content, bits_length);
		bits_length -= bits_put;
	
		if (!is_marked) {
			mark_chunk(chunk.bytes, 512 - bits_put + 1);
			is_marked = true;
		}
		chunk.length.it = length;
	
		addback_element(&msg, new_element(chunk));
	}

	return msg;
}
