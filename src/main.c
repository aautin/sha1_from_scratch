#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "parsing.h"

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i) {
		char*	file = argv[i];

		int		fd = open(file, O_RDONLY);
		if (fd < 0)
			perror(file);
		else {
			char*	content = get_content_from_fd(fd);
			if (content == NULL)
			perror(file);
			else {
				t_list*	message = get_msg_from_content(content);
				printf("%s:\n%s", file, content);
				list_clear(&message);
			}
			free(content);
		}
	}
}
