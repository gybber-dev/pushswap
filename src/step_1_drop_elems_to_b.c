/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_1_drop_elems_to_b.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeschall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:20:36 by yeschall          #+#    #+#             */
/*   Updated: 2021/10/30 15:20:38 by yeschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

static int	is_all_elements_were_moved(t_stack *a)
{
	while (a)
	{
		if (!a->mark)
			return (0);
		a = a->next;
	}
	return (1);
}

static void	drop_non_marked_elems_to_b(t_all *all)
{
	while (!is_all_elements_were_moved(all->a))
	{
		if (all->a->mark == 1)
			all->counter += ra(&all->a, 1);
		else
			all->counter += pb(&all->a, &all->b, 1);
	}
}

static int	count_lost_elems_in_a(t_stack *start, t_stack *head, \
				int mark_sequence, int size)
{
	int		counter;
	int		last_serial_index;
	t_stack	*current_node;
	t_stack	*next_node;

	current_node = start;
	counter = 1;
	start->mark = mark_sequence;
	last_serial_index = current_node->index;
	while (1)
	{
		next_node = get_next(current_node, head);
		if (next_node == start)
			break ;
		if (is_next_index(last_serial_index, next_node->index, size))
		{
			counter++;
			next_node->mark = mark_sequence;
			last_serial_index = next_node->index;
		}
		current_node = next_node;
	}
	return (counter);
}

static void	mark_elems_to_drop(t_stack *a, int size)
{
	t_stack		*tmp;
	t_stack		*max_p;
	int			max_lost;
	int			lost;

	tmp = a;
	max_p = NULL;
	max_lost = -1;
	while (tmp)
	{
		lost = count_lost_elems_in_a(tmp, a, 0, size);
		if (lost > max_lost)
		{
			max_lost = lost;
			max_p = tmp;
		}
		tmp = tmp->next;
	}
	count_lost_elems_in_a(max_p, a, 1, size);
}

void	prepare_stacks(t_all *all)
{
	mark_elems_to_drop(all->a, all->size);
	drop_non_marked_elems_to_b(all);
}
