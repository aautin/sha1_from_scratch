#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "chunk.h"
#include "endian.h"
#include "list.h"
#include "parsing.h"

char* get_content_from_fd(int fd, ssize_t *size)
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

	*size = read_chars;
	return content;
}

void mark_chunk(uint8_t* chunk_bytes, size_t index)
{
	size_t byte_index = index / 8;
	size_t bit_position = index % 8;

	chunk_bytes[byte_index] |= (1 << (7 - bit_position));
}

size_t put_bits_in_chunk(uint8_t* chunk, uint8_t* src, size_t index_from, size_t put_length)
{
	size_t index = 0;
	while (index < put_length && index < 512) {
		size_t	src_byte = (index_from + index) / 8;
		size_t	src_bit = (index_from + index) % 8;
		bool	value = (src[src_byte] >> (7 - src_bit)) & 1;
		
		size_t	chunk_byte = index / 8;
		size_t	chunk_bit = index % 8;

		chunk[chunk_byte] |= (value << (7 - chunk_bit));

		index++;
	}

	return index;
}

t_list* get_msg_from_content(uint8_t* content, uint64_t original_bit_len)
{
	uint64_t	bit_len = original_bit_len;
	t_list*		msg = NULL;
	size_t		bit_index = 0;
	
	bool	is_marked = false;
	while ((bit_len + !is_marked) > 448) {
		t_chunk	chunk;
		memset(&chunk, 0, sizeof(t_chunk));

		size_t	bits_put = put_bits_in_chunk(chunk.bytes, content, bit_index, bit_len);
		bit_len -= bits_put;
		bit_index += bits_put;

		if (!is_marked && bit_len == 0 && bits_put < 512) {
			mark_chunk(chunk.bytes, bits_put);
			is_marked = true;
		}

		addback_element(&msg, new_element(chunk));
	}

	{
		t_chunk	chunk;
		memset(&chunk, 0, sizeof(t_chunk));
	
		size_t	bits_put = put_bits_in_chunk(chunk.bytes, content, bit_index, bit_len);
		bit_len -= bits_put;
	
		if (!is_marked) {
			mark_chunk(chunk.bytes, bits_put);
			is_marked = true;
		}
		chunk.len.it = endian64(original_bit_len);
	
		addback_element(&msg, new_element(chunk));
	}

	return msg;
}
