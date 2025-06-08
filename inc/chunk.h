#ifndef CHUNK_H
# define CHUNK_H

# include <stdint.h>

union Chunk
{
	uint8_t		bytes[64];
	uint32_t	words[16];
	
	struct
	{
		uint64_t	dummy[7];
		uint64_t	it;
	}	length;
};

#endif
