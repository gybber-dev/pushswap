#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
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
    int val;
    int index;
    int mark;
	t_table		table;
    struct s_stack *next;
    struct s_stack *prev;
}               t_stack;

typedef struct s_info
{
	int top_index;
	int bottom_index;
	int size_a;
	int size_b;
}	t_info;

typedef struct s_all
{
    t_stack *a;
    t_stack *b;
    int size;
    int counter;
}				t_all;

int	is_number(char *str);
int max(int a, int b);
int min(int a, int b);
int	get_arr_2x_len(char **arr);
void		clear_arr_2x(char ***arr);
t_stack	*ft_lst2_new(int num);
t_stack	*ft_lst2_add_back(t_stack **lst, t_stack *new);
int	count_lst_size(t_stack *ptr);
t_stack *get_next(t_stack *ptr, t_stack *head);
int is_next_index(int current_index, int next_index, int size);
t_stack *get_prev(t_stack *ptr);
void ft_lst_clear(t_stack **stack);
int sa(t_stack **a, int is_print);
int sb(t_stack **b, int is_print);
int ss(t_stack **a, t_stack **b, int is_print);
int ra(t_stack **a, int is_print);
int rb(t_stack **b, int is_print);
int rra(t_stack **a, int is_print);
int rrb(t_stack **b, int is_print);
int rrr(t_stack **a, t_stack **b, int is_print);
int pa(t_stack **a, t_stack **b, int is_print);
int pb(t_stack **a, t_stack **b, int is_print);
int rr(t_stack **a, t_stack **b, int is_print);
void shift_down(t_stack **head);
void shift_up(t_stack **head);
void push(t_stack **src, t_stack **dst);
void swap(t_stack **ptr);
int split_string(int *argc, char **argv, char ***inputs);
void init_struct(t_all *all, int argc);
void parse_argv(char **argv, t_stack **a);
char		**copy_arrays_2x(char **src_arr);
void count_indexes(t_stack *ptr, int size);
void prepare_stacks (t_all *all);
void count_totals_for_each_b_elem(t_all *all);
t_stack *choose_elem_with_min_total(t_stack *ptr);
void move_optimal_element_to_a(t_stack *ptr, t_all *all);
void	fatal_exit();

#endif