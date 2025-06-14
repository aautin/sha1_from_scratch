#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t endian32(uint32_t value) {
	#ifdef __ORDER_LITTLE_ENDIAN__
        return ((value & 0xFF000000) >> 24) |
            ((value & 0x00FF0000) >> 8) |
            ((value & 0x0000FF00) << 8) |
            ((value & 0x000000FF) << 24);
	#else
		return value;
	#endif
}

uint64_t endian64(uint64_t value) {
    
	#ifdef __ORDER_LITTLE_ENDIAN__
        return ((value & 0xFF00000000000000) >> 56) |
            ((value & 0x00FF000000000000) >> 40) |
            ((value & 0x0000FF0000000000) >> 24) |
            ((value & 0x000000FF00000000) >> 8) |
            ((value & 0x00000000FF000000) << 8) |
            ((value & 0x0000000000FF0000) << 24) |
            ((value & 0x000000000000FF00) << 40) |
            ((value & 0x00000000000000FF) << 56);
	#else
        return value;
    #endif
}
