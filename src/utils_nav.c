#include "../includes/pushswap.h"

t_stack *get_next(t_stack *ptr, t_stack *head)
{
	if (!ptr)
		return (NULL);
	if (ptr->next == NULL)
		return (head);
	return (ptr->next);
}

int is_next_index(int current_index, int next_index, int size)
{
	int last_index;

	last_index = size - 1;
	if (next_index == current_index + 1)
		return 1;
	if (current_index == last_index && next_index == 0)
		return 1;
	return 0;
}

t_stack *get_prev(t_stack *ptr)
{
	if (!ptr)
		return (NULL);
	if (ptr->prev)
		return ptr->prev;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
