#ifndef SHA1_H
# define SHA1_H

# include <stddef.h>
# include <stdint.h>

# include "list.h"

# define ROTL(value, shift) ((value << shift) | (value >> (32 - shift)))

typedef uint32_t t_sha1[5];

void	define_chunk_words(uint32_t* words);
void	sha1(t_list *msg, t_sha1 result);

#endif
