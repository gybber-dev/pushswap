#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# define INT_MAX 2147483647
# define UP_UP 0
# define UP_DOWN 1
# define DOWN_UP 2
# define DOWN_DOWN 3

typedef struct s_table
{
	int		a_up;
	int		a_down;
	int		b_up;
	int		b_down;
	int		total;
	int		optimal_comb;
}				t_table;

typedef struct s_stack
{
	int				val;
	int				index;
	int				mark;
	t_table			table;
	struct s_stack	*next;
	struct s_stack	*prev;
}				t_stack;

typedef struct s_all
{
	t_stack		*a;
	t_stack		*b;
	int			size;
	int			counter;
}				t_all;

#endif
