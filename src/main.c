#include <fcntl.h>
#include <stdio.h>

#include "chunk.h"

int	main(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		char*	file = argv[i];
		int		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			perror(file);
		}
	}
}
