#include "../includes/pushswap.h"

void swap(t_stack **ptr)
{
	t_stack *tmp1;
	t_stack *tmp2;

	if (!(*ptr) || !(*ptr)->next)
		return;
	tmp1 = *ptr;
	tmp2 = (*ptr)->next;
	tmp1->next = tmp2->next;
	tmp1->prev = tmp2->prev;
	tmp2->prev = NULL;
	tmp2->next = tmp1;
	*ptr = tmp2;
}

void push(t_stack **src, t_stack **dst)
{
	t_stack *tmp;

	if (!(*src))
		return;
	tmp = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	tmp->next = *dst;
	if (*dst)
		(*dst)->prev = tmp;
	*dst = tmp;
}

void shift_up(t_stack **head)
{
	t_stack *node;
	t_stack *tmp;

	if (!(*head) || !(*head)->next)
		return;
	node = *head;
	*head = (*head)->next;
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
	node->next = NULL;
	(*head)->prev = NULL;
}

void shift_down(t_stack **head)
{
	t_stack *node;

	if (!(*head) || !(*head)->next)
		return;
	node = *head;
	while (node->next)
		node = node->next;
	node->prev->next = NULL;
	node->next = *head;
	(*head)->prev = node;
	(*head) = node;
	(*head)->prev = NULL;
}


int rr(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("rr\n", 1);
	shift_up(a);
	shift_up(b);
	return (1);
}
