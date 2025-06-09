#ifndef PARSING_H
# define PARSING_H

# include "list.h"

char	*get_content_from_fd(int fd);
t_list	*get_msg_from_content(char* content);

#endif
