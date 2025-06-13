#ifndef SHA1_H
# define SHA1_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# include "list.h"

# define ROTL(value, shift) ((value << shift) | (value >> (32 - shift)))

void	define_chunk_words(uint32_t* words);
bool	sha1(uint8_t* content, uint64_t bit_len, uint32_t* hash);

#endif
