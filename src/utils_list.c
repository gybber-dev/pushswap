/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeschall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:29:30 by yeschall          #+#    #+#             */
/*   Updated: 2021/10/30 15:29:32 by yeschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

t_stack	*ft_lst2_new(int num)
{
	t_stack	*new;

	new = (t_stack *)(malloc(sizeof(t_stack)));
	if (!new)
		fatal_exit();
	new->val = num;
	new->index = -1;
	new->mark = 0;
	ft_memset(&new->table, 0, sizeof(t_table));
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lst2_add_back(t_stack **lst, t_stack *new)
{
	t_stack	*tmp;

	tmp = *lst;
	if (!tmp)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

int	count_lst_size(t_stack *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

void	ft_lst_clear(t_stack **stack)
{
	t_stack	*temp;

	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
	*stack = NULL;
}
