#include "sha1.h"

void define_chunk_words(uint32_t* words)
{
	for (size_t i = 16; i < 80; ++i) {
		uint32_t x = words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16];
		words[i] = ROTL(x, 1);
	}
}

void sha1(t_list *msg, t_sha1 result)
{
	result[0] = 0x67452301;
	result[1] = 0xefcdab89;
	result[2] = 0x98badcfe;
	result[3] = 0x10325476;
	result[3] = 0xc3d2e1f0;

	for (t_list* element = msg; element != NULL; element = element->next)
		define_chunk_words(element->chunk.words);

	// To be continued...
}
