#include <stdio.h>
#include "../includes/pushswap.h"

void	fatal_exit()
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void print_lst(t_stack *ptr)
{
	printf("================\n");
	while(ptr)
	{
		printf("%d\t[%d]\t'%d'\n", ptr->val, ptr->index, ptr->mark);
		ptr = ptr->next;
	}
	printf("================\n");
}


void put_head_on_top(t_stack **a, int size, int *counter)
{
	t_stack *tmp;
	int	i;
	int	is_shift_down;

	i = 0;
	tmp = *a;
	while (tmp->index != 0 && ++i)
		tmp = tmp->next;
	is_shift_down = 0;
	if (i > size/2)
	{
		is_shift_down = 1;
		i = size - i;
	}
	*counter += i;
	while (i-- > 0)
		if (is_shift_down)
			rra(a, 1);
		else
			ra(a, 1);
}

void find_fastest_way(t_all *all)
{
	t_stack *tmp;

	tmp = NULL;
	while(count_lst_size(all->b))
	{
		count_totals_for_each_b_elem(all);
		tmp = choose_elem_with_min_total(all->b);
		move_optimal_element_to_a(tmp, all);
	}
	put_head_on_top(&all->a, all->size, &all->counter);
}

int main(int argc, char **argv)
{
	char **inputs;
	t_all all;

	inputs = NULL;
	if (argc == 1 || split_string(&argc, argv, &inputs) == 0)
		return (EXIT_SUCCESS);
	init_struct(&all, argc);
	parse_argv(inputs, &(all.a));
	count_indexes(all.a, all.size);
	prepare_stacks(&all);
	find_fastest_way(&all);
	ft_lst_clear(&all.a);
	ft_lst_clear(&all.b);
	clear_arr_2x(&inputs);
	return 0;
}
