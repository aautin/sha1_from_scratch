#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "chunk.h"
#include "endian.h"
#include "parsing.h"
#include "mysha1.h"

#include "debug.h"

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i) {
		char*	file = argv[i];

		int		fd = open(file, O_RDONLY);
		if (fd < 0)
			perror(file);
		else {
			ssize_t content_size;
			char*	content = get_content_from_fd(fd, &content_size);
			close(fd);

			if (content == NULL)
				perror(file);
			else {
				uint32_t	hash[5];
				if (!sha1((uint8_t*) content, content_size * 8, hash))
					perror(file);
				else
					printf("%08x%08x%08x%08x%08x  %s\n", hash[0], hash[1], hash[2], hash[3], hash[4], file);
			}
			free(content);
		}
	}
}
