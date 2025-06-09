#ifndef CHUNK_H
# define CHUNK_H

# include <stdint.h>

typedef union u_chunk
{
	uint8_t		bytes[64];
	uint32_t	words[80];
	
	struct
	{
		uint64_t	dummy[7];
		uint64_t	it;
	}	len;
}	t_chunk;

#endif
