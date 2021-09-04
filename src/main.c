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

void select_elems_to_drop(t_stack *a)
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

void drop_elems_to_b (t_all *all)
{
	select_elems_to_drop(all->a);
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
	drop_elems_to_b(&all);
	print_lst(all.a);
	return 0;
}
