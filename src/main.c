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

int	 fatal_exit()
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
	new->next = NULL;
	new->prev = NULL;
	new->virt_next = NULL;
	new->virt_prev = NULL;
	return (new);
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

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			fatal_exit();
		num = ft_atoi_clever(argv[i]);
		if (num == -1 && ft_strlen(argv[i]) != 2)
			fatal_exit();
		if (is_double(*a, num))
			fatal_exit();
		new = ft_lst2_new(num);
		new->size = size;
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

int count_lost(t_stack *start, t_stack *head, int mark_sequence)
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
		if (is_next(last_serial_index, next_node->index, current_node->size))
		{
			counter++;
			next_node->mark = mark_sequence;
			last_serial_index = next_node->index;
		}
		current_node = next_node;

	}
	printf("%d\t[%d] = %d\n", start->val, start->index, counter);
	return counter;
}

void mark_elems_to_drop(t_stack *a)
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
		lost = count_lost(tmp, a, 0);
		if (lost > max_lost)
		{
			max_lost = lost;
			max_p = tmp;
		}
		tmp = tmp->next;
	}
	printf("=========\nmax_sequence begins from: %d [%d]\n", max_p->val, max_lost);
	count_lost(max_p, a, 1);
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
	mark_elems_to_drop(all->a);
	drop_non_marked_elems_to_b(all);
}

int main(int argc, char **argv)
{
	t_all all;
	if (argc == 1)
		return (EXIT_SUCCESS);
	init_struct(&all, argc);
	parse_argv(argv, &(all.a), all.size);
	count_indexes(all.a, all.size);
	print_lst(all.a);
	prepare_stacks(&all);
	print_lst(all.a);
	print_lst(all.b);
	printf("total operations: %d\n", all.counter);
	return 0;
}
