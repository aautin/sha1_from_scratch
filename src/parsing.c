#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char	*get_fd_content(int fd)
{
	struct stat	stats;
	fstat(fd, &stats);

	char*	content = malloc((stats.st_size + 1) * sizeof(char));
	if (content == NULL)
		return NULL;

	ssize_t	read_chars = read(fd, content, stats.st_size);
	if (read_chars < 0) {
		free(content);
		return NULL;
	}
	content[read_chars] = '\0';

	return content;
}
