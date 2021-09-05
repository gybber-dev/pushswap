#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# define INT_MAX 2147483647

typedef struct s_stack
{
    int val;
    int index;
    int size;
    int mark;
    struct s_stack *next;
    struct s_stack *prev;
    struct s_stack *virt_next;
    struct s_stack *virt_prev;
}               t_stack;


typedef struct s_all
{
    t_stack *a;
    t_stack *b;
    int size;
    int counter;
}				t_all;

#endif