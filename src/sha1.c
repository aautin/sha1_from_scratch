#include "sha1.h"

uint32_t choice(uint32_t b, uint32_t c, uint32_t d)
{
	return (b & c) | ((~b) & d);
}
uint32_t parity(uint32_t b, uint32_t c, uint32_t d)
{
	return b ^ c ^ d;
}
uint32_t majority(uint32_t b, uint32_t c, uint32_t d)
{
	return (b & c) | (b & d) | (c & d);
}

void define_chunk_words(uint32_t* words)
{
	for (size_t i = 16; i < 80; ++i) {
		uint32_t x = words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16];
		words[i] = ROTL(x, 1);
	}
}

void sha1(t_list *msg, t_sha1 hash)
{
	hash[0] = 0x67452301;
	hash[1] = 0xefcdab89;
	hash[2] = 0x98badcfe;
	hash[3] = 0x10325476;
	hash[4] = 0xc3d2e1f0;

	for (t_list* element = msg; element != NULL; element = element->next)
		define_chunk_words(element->chunk.words);

	for (t_list* element = msg; element != NULL; element = element->next) {
		uint32_t	a = hash[0], b = hash[1], c = hash[2],	
					d = hash[3], e = hash[4];

		for (size_t i = 0; i < 80; ++i) {
			uint32_t	(*function)(uint32_t, uint32_t, uint32_t);
			uint32_t	k, temp;
			uint32_t	w = element->chunk.words[i];
	
			if (i <= 19) {
				function = &choice;
				k = 0x5a827999;
			}
			else if (20 <= i && i <= 39) {
				function = &parity;
				k = 0x6ed9eba1;
			}
			else if (40 <= i && i <= 59) {
				function = &majority;
				k = 0x8f1bbcdc;
			}
			else {
				function = &parity;
				k = 0xca62c1d6;
			}

			temp = ROTL(a, 5) + function(b, c, d) + e + w + k;
			e = d, d = c, c = ROTL(b, 30), b = a, a = temp;
		}
		hash[0] += a;
		hash[1] += b;
		hash[2] += c;
		hash[3] += d;
		hash[4] += e;
	}
}
