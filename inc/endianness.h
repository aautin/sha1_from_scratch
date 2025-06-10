#ifndef ENDIANNESS_h
# define ENDIANNESS_H

# include <stdint.h>

uint32_t	swap_endian32(uint32_t value);
uint64_t	swap_endian64(uint64_t value);

#endif
