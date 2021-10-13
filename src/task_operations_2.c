#include "../includes/pushswap.h"

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