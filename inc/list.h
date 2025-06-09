#ifndef LIST_H
# define LIST_H

# include "chunk.h"

typedef struct s_list
{
	t_chunk			chunk;
	struct s_list*	next;
}	t_list;

t_list	*new_element(t_chunk chunk);
void	addback_element(t_list** head, t_list* new);
void	list_clear(t_list** list);

#endif
