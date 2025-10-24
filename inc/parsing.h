#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>

# include "list.h"

char		*get_content_from_fd(int fd, ssize_t *size);
t_list		*get_msg_from_content(uint8_t* content, uint64_t len);

#endif
