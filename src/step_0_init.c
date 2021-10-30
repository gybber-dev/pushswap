/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_0_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeschall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:19:15 by yeschall          #+#    #+#             */
/*   Updated: 2021/10/30 15:19:17 by yeschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

static int	is_double(t_stack *ptr, int value)
{
	while (ptr)
	{
		if (ptr->val == value)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int	split_string(int *argc, char **argv, char ***inputs)
{
	if (*argc == 2)
	{
		*inputs = ft_split(argv[1], ' ');
		*argc = get_arr_2x_len(*inputs) + 1;
	}
	else
	{
		*inputs = copy_arrays_2x(argv + 1);
	}
	if (!(*inputs))
		return (0);
	return (1);
}

void	init_struct(t_all *all, int argc)
{
	all->a = NULL;
	all->b = NULL;
	all->size = argc - 1;
	all->counter = 0;
}

void	parse_argv(char **argv, t_stack **a)
{
	int		i;
	int		num;
	t_stack	*new;

	i = 0;
	while (argv && argv[i])
	{
		if (!is_number(argv[i]))
			fatal_exit();
		num = ft_atoi_clever(argv[i]);
		if (num == -1 && ft_strlen(argv[i]) != 2)
			fatal_exit();
		if (is_double(*a, num))
			fatal_exit();
		new = ft_lst2_new(num);
		ft_lst2_add_back(a, new);
		i++;
	}
}

void	count_indexes(t_stack *ptr, int size)
{
	int		min;
	t_stack	*min_p;
	t_stack	*tmp;
	int		counter;

	counter = 0;
	while (counter < size)
	{
		tmp = ptr;
		min = INT_MAX;
		min_p = NULL;
		while (tmp)
		{
			if (tmp->index == -1 && (min > tmp->val || min_p == NULL))
			{
				min = tmp->val;
				min_p = tmp;
			}
			tmp = tmp->next;
		}
		if (min_p)
			min_p->index = counter;
		counter++;
	}
}
