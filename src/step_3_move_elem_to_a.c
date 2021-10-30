/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_3_move_elem_to_a.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeschall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:26:16 by yeschall          #+#    #+#             */
/*   Updated: 2021/10/30 15:26:18 by yeschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

static int	rotate_stacks_by_up_down(t_stack *element, t_stack **a, t_stack **b)
{
	int	i;

	i = 0;
	while (i < element->table.a_up)
		i += ra(a, 1);
	while (i < element->table.b_down)
		i += rrb(b, 1);
	return (i);
}

static int	rotate_stacks_by_down_up(t_stack *element, t_stack **a, t_stack **b)
{
	int	i;

	i = 0;
	while (i < element->table.a_down)
		i += rra(a, 1);
	while (i < element->table.b_up)
		i += rb(b, 1);
	return (i);
}

static int	rotate_stacks_by_down_down(t_stack *element, t_stack **a, \
				t_stack **b)
{
	int	i;

	i = 0;
	while (i < min(element->table.a_down, element->table.b_down))
		i += rrr(a, b, 1);
	while (i < max(element->table.a_down, element->table.b_down))
	{
		if (element->table.a_down > element->table.b_down)
			i += rra(a, 1);
		else
			i += rrb(b, 1);
	}
	return (i);
}

static int	rotate_stacks_by_up_up(t_stack *element, t_stack **a, t_stack **b)
{
	int	i;

	i = 0;
	while (i < min(element->table.a_up, element->table.b_up))
		i += rr(a, b, 1);
	while (i < max(element->table.a_up, element->table.b_up))
	{
		if (element->table.a_up > element->table.b_up)
			i += ra(a, 1);
		else
			i += rb(b, 1);
	}
	return (i);
}

void	move_optimal_element_to_a(t_stack *element, t_all *all)
{
	if (element->table.optimal_comb == UP_UP)
		all->counter += rotate_stacks_by_up_up(element, &all->a, &all->b);
	else if (element->table.optimal_comb == DOWN_DOWN)
		all->counter += rotate_stacks_by_down_down(element, &all->a, &all->b);
	else if (element->table.optimal_comb == DOWN_UP)
		all->counter += rotate_stacks_by_down_up(element, &all->a, &all->b);
	else if (element->table.optimal_comb == UP_DOWN)
		all->counter += rotate_stacks_by_up_down(element, &all->a, &all->b);
	pa(&all->a, &all->b, 1);
	all->counter += 1;
}
