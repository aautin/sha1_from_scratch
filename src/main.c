#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "parsing.h"

int	main(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i) {
		char*	file = argv[i];

		int		fd = open(file, O_RDONLY);
		if (fd < 0)
			perror(file);
		else {
			char* content = get_fd_content(fd);
			if (content == NULL)
				perror(file);
			else
				printf("%s:\n%s", file, content);
			free(content);
		}
	}
}
