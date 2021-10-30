/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_operations_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeschall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:28:10 by yeschall          #+#    #+#             */
/*   Updated: 2021/10/30 15:28:12 by yeschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

int	rra(t_stack **a, int is_print)
{
	if (is_print)
		ft_putstr_fd("rra\n", 1);
	shift_down(a);
	return (1);
}

int	rrb(t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("rrb\n", 1);
	shift_down(b);
	return (1);
}

int	rrr(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("rrr\n", 1);
	shift_down(a);
	shift_down(b);
	return (1);
}

int	pa(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("pa\n", 1);
	push(b, a);
	return (1);
}

int	pb(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("pb\n", 1);
	push(a, b);
	return (1);
}
