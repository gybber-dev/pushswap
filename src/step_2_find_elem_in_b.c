#include "../includes/pushswap.h"

static void count_total_steps (t_table *table)
{
	int	prev_total;

	table->optimal_comb = UP_UP;
	table->total = max(table->a_up, table->b_up);
	prev_total = table->total;
	table->total = min(table->a_up + table->b_down, table->total);
	if (table->total < prev_total)
	{
		prev_total = table->total;
		table->optimal_comb = UP_DOWN;
	}
	table->total = min(table->a_down + table->b_up, table->total);
	if (table->total < prev_total)
	{
		prev_total = table->total;
		table->optimal_comb = DOWN_UP;
	}
	table->total = min(max(table->a_down, table->b_down), table->total);
	if (table->total < prev_total)
	{
		prev_total = table->total;
		table->optimal_comb = DOWN_DOWN;
	}
}

static void	count_steps_for_b_elem(t_stack **ptr, int index, t_all *all, t_info info)
{
	t_stack *tmp;
	t_stack *prev;
	t_stack *next;

	(*ptr)->table.b_up = index;
	(*ptr)->table.b_down = info.size_b - index;
	tmp = all->a;
	while(tmp)
	{
		prev = get_prev(tmp);
		next = tmp;
		if ((prev->index < (*ptr)->index && (*ptr)->index < next->index) || \
		(prev->index == info.bottom_index && next->index == info.top_index && ((*ptr)->index < info.top_index || (*ptr)->index > info.bottom_index)))
			break;
		(*ptr)->table.a_up++;
		tmp = tmp->next;
	}
	(*ptr)->table.a_down = info.size_a - (*ptr)->table.a_up;
	count_total_steps(&(*ptr)->table);
}

static void	find_side_indexes(t_stack *ptr, int *top_index, int *bottom_index)
{
	if (!ptr)
	{
		*top_index = 0;
		*bottom_index = 0;
		return;
	}
	*top_index = ptr->index;
	*bottom_index = ptr->index;
	while (ptr)
	{
		if (*top_index > ptr->index)
			*top_index = ptr->index;
		if (*bottom_index < ptr->index)
			*bottom_index = ptr->index;
		ptr = ptr->next;
	}
}

void count_totals_for_each_b_elem(t_all *all)
{
	t_stack *ptr;
	int		index;
	t_info info;

	ft_memset(&info, 0, sizeof(t_info));
	find_side_indexes(all->a, &info.top_index, &info.bottom_index);
	info.size_a = count_lst_size(all->a);
	info.size_b = count_lst_size(all->b);
	index = 0;
	ptr = all->b;
	while(ptr)
	{
		ft_memset(&ptr->table, 0, sizeof(t_table));
		count_steps_for_b_elem(&ptr, index, all, info);
		index++;
		ptr = ptr->next;
	}
}

t_stack *choose_elem_with_min_total(t_stack *ptr)
{
	int current_total;
	t_stack *res_elem;

	if (!ptr)
		return (ptr);
	res_elem = ptr;
	current_total = ptr->table.total;
	while(ptr->next)
	{
		if (ptr->table.total < current_total)
		{
			current_total = ptr->table.total;
			res_elem = ptr;
		}
		ptr = ptr->next;
	}
	return (res_elem);
}
