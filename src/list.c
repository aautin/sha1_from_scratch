#include <stdlib.h>

#include "list.h"

t_list *new_element(t_chunk chunk)
{
	t_list*	element = malloc(sizeof(t_list));
	if (element == NULL)
		return element;

	element->chunk = chunk;
	element->next = NULL;
	return element;
}

void addback_element(t_list** head, t_list* new)
{
	if (*head == NULL)
		*head = new;
	else {
		t_list* ptr = *head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void list_clear(t_list** list)
{
	while (*list != NULL) {
		t_list* next = (*list)->next;

		free(*list);
		*list = next;
	}
}
