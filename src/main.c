#include <stdio.h>
#include "../includes/pushswap.h"

int	is_number(char *str)
{
	while (*str && ((*str == ' ') || (*str == '\t') || (*str == '\n') || \
	(*str == '\v') || (*str == '\f') || (*str == '\r')))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}

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

int	count_lst_size(t_stack *ptr)
{
	int	i;

	i = 0;
	while(ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

t_stack	*ft_lst2_add_back(t_stack **lst, t_stack *new)
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

int is_double(t_stack *ptr, int value)
{
	while (ptr)
	{
		if (ptr->val == value)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void parse_argv(char **argv, t_stack **a, int size)
{
	int i;
	int num;
	t_stack *new;

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

void count_indexes(t_stack *ptr, int size)
{
	int min;
	t_stack *min_p;
	t_stack *tmp;
	int counter;

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

void init_struct(t_all *all, int argc)
{
	all->a = NULL;
	all->b = NULL;
	all->size = argc - 1;
	all->counter = 0;
}

int is_next(int current_index, int next_index, int size)
{
	int last_index;

	last_index = size - 1;
	if (next_index == current_index + 1)
		return 1;
	if (current_index == last_index && next_index == 0)
		return 1;
	return 0;
}

int count_lost_elems_in_a(t_stack *start, t_stack *head, int mark_sequence, int size)
{
	int counter;
	t_stack *current_node;
	t_stack *next_node;
	int last_serial_index;

	counter = 1;
	current_node = start;
	start->mark = mark_sequence;
	last_serial_index = current_node->index;
	while (1)
	{
		if (current_node->next == NULL)
			next_node = head;
		else
			next_node = current_node->next;
		if (next_node == start)
			break;
		if (is_next(last_serial_index, next_node->index, size))
		{
			counter++;
			next_node->mark = mark_sequence;
			last_serial_index = next_node->index;
		}
		current_node = next_node;

	}
//	printf("%d\t[%d] = %d\n", start->val, start->index, counter);
	return counter;
}

void mark_elems_to_drop(t_stack *a, int size)
{
	t_stack *tmp;
	t_stack *max_p;
	int max_lost;
	int lost;

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
//	printf("=========\nmax_sequence begins from: %d [%d]\n", max_p->val, max_lost);
	count_lost_elems_in_a(max_p, a, 1, size);
}

//ptr 	ptr.next 	ptr.next
//tmp

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

int sa(t_stack **a, int is_print)
{
	if (is_print)
		ft_putstr_fd("sa\n", 1);
	swap(a);
	return (1);
}

int sb(t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("sb\n", 1);
	swap(b);
	return (1);
}

int ss(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("ss\n", 1);
	swap(a);
	swap(b);
	return (1);
}

int ra(t_stack **a, int is_print)
{
	if (is_print)
		ft_putstr_fd("ra\n", 1);
	shift_up(a);
	return (1);
}

int rb(t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("rb\n", 1);
	shift_up(b);
	return (1);
}

int rr(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("rr\n", 1);
	shift_up(a);
	shift_up(b);
	return (1);
}

int rra(t_stack **a, int is_print)
{
	if (is_print)
		ft_putstr_fd("rra\n", 1);
	shift_down(a);
	return (1);
}

int rrb(t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("rrb\n", 1);
	shift_down(b);
	return (1);
}

int rrr(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("rrr\n", 1);
	shift_down(a);
	shift_down(b);
	return (1);
}


int pa(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("pa\n", 1);
	push(b, a);
	return (1);
}

int pb(t_stack **a, t_stack **b, int is_print)
{
	if (is_print)
		ft_putstr_fd("pb\n", 1);
	push(a, b);
	return (1);
}

int is_all_elements_were_moved(t_stack *a)
{
	while (a)
	{
		if (!a->mark)
			return 0;
		a = a->next;
	}
	return 1;
}

void drop_non_marked_elems_to_b(t_all *all)
{
	while (!is_all_elements_were_moved(all->a))
	{
		if (all->a->mark == 1)
			all->counter += ra(&all->a, 1);
		else
			all->counter += pb(&all->a, &all->b, 1);
	}
}

void prepare_stacks (t_all *all)
{
	mark_elems_to_drop(all->a, all->size);
	drop_non_marked_elems_to_b(all);
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

void count_total(t_table *table)
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

void	find_side_indexes(t_stack *ptr, int *top_index, int *bottom_index)
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

void	count_steps_for_b_elem(t_stack **ptr, int index, t_all *all, t_info info)
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
	count_total(&(*ptr)->table);
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

void move_optimal_element_to_a(t_stack *ptr, t_all *all)
{
	int	i;

	if (ptr->table.optimal_comb == UP_UP)
	{
		i = 0;
		while(i < min(ptr->table.a_up, ptr->table.b_up))
			i += rr(&all->a, &all->b, 1);
		while(i < max(ptr->table.a_up, ptr->table.b_up))
			if (ptr->table.a_up > ptr->table.b_up)
				i += ra(&all->a, 1);
			else
				i += rb(&all->b, 1);
		all->counter += i;
	}
	if (ptr->table.optimal_comb == DOWN_DOWN)
	{
		i = 0;
		while(i < min(ptr->table.a_down, ptr->table.b_down))
			i += rrr(&all->a, &all->b, 1);
		while(i < max(ptr->table.a_down, ptr->table.b_down))
			if (ptr->table.a_down > ptr->table.b_down)
				i += rra(&all->a, 1);
			else
				i += rrb(&all->b, 1);
		all->counter += i;
	}
	if (ptr->table.optimal_comb == DOWN_UP)
	{
		i = 0;
		while(i < ptr->table.a_down)
			i += rra(&all->a, 1);
		all->counter += i;
		i = 0;
		while(i < ptr->table.b_up)
			i += rb(&all->b, 1);
		all->counter += i;
	}
	if (ptr->table.optimal_comb == UP_DOWN)
	{
		i = 0;
		while(i < ptr->table.a_up)
			i += ra(&all->a, 1);
		all->counter += i;
		i = 0;
		while(i < ptr->table.b_down)
			i += rrb(&all->b, 1);
		all->counter += i;
	}
	pa(&all->a, &all->b, 1);
	all->counter += 1;
//	print_lst(all->a);
//	print_lst(all->b);
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

char		**copy_arrays_2x(char **src_arr)
{
	int		i;
	char	**tmp_src;
	char	**tmp_dst;
	char	**res_arr;

	i = 0;
	if (!src_arr)
		return NULL;
	tmp_src = src_arr;
	while(*(tmp_src++)) {
		i++;
	}
	res_arr = (char **) malloc(sizeof(char *) * i + 1);
	tmp_src = src_arr;
	tmp_dst = res_arr;
	while(*tmp_src)
	{
		*tmp_dst = ft_strdup(*tmp_src);
		tmp_src++;
		tmp_dst++;
	}
	*tmp_dst = NULL;
	return res_arr;
}

int	get_arr_2x_len(char **arr)
{
	int		res;

	res = 0;
	while (*arr++)
		res++;
	return (res);
}

int split_string(int *argc, char **argv, char ***inputs)
{
	int res;

	res = 0;
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
	return 1;
}

void		clear_arr_2x(char ***arr)
{
	int		i;
	int size;

	i = 0;
	size = get_arr_2x_len(*arr);
	while (i < size)
		free((*arr)[i++]);
	free(*arr);
}

int main(int argc, char **argv)
{
	char **inputs;
	t_all all;

	inputs = NULL;
//	printf("args: %d\n", argc);
	if (argc == 1 || split_string(&argc, argv, &inputs) == 0)
		return (EXIT_SUCCESS);
	init_struct(&all, argc);
	parse_argv(inputs, &(all.a), all.size);
	count_indexes(all.a, all.size);

	prepare_stacks(&all);
//	print_lst(all.a);
//	print_lst(all.b);
	find_fastest_way(&all);
//	printf("total operations: %d\n", all.counter);
//	print_lst(all.a);
	clear_arr_2x(&inputs);
	return 0;
}
