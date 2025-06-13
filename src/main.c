#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "chunk.h"
#include "endian.h"
#include "parsing.h"
#include "sha1.h"

#include "debug.h"

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i) {
		char*	file = argv[i];

		int		fd = open(file, O_RDONLY);
		if (fd < 0)
			perror(file);
		else {
			char*	content = get_content_from_fd(fd);
			close(fd);

			if (content == NULL)
				perror(file);
			else {
				t_list*	message = get_msg_from_content(content);

				uint32_t	hash[5];
				sha1(message, hash);
				
				printf("%08x%08x%08x%08x%08x  %s\n", hash[0], hash[1], hash[2], hash[3], hash[4], file);
				list_clear(&message);
			}
			free(content);
		}
	}
}
