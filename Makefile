NAME = push_swap

SRCS = src/main.c \
			src/step_0_init.c \
			src/step_1_drop_elems_to_b.c \
			src/step_2_find_elem_in_b.c \
			src/step_3_move_elem_to_a.c \
			src/task_operations_0.c \
			src/task_operations_1.c \
			src/task_operations_2.c \
			src/utils.c \
			src/utils_arr2x.c \
			src/utils_list.c \
			src/utils_nav.c \

OBJS		= $(patsubst %.c, %.o, $(SRCS))

CC = gcc
FLAGS = -Wall -Wextra -Werror
HEADER = includes/pushswap.h
RM = rm -f



all:		${NAME}

$(NAME): $(OBJS) $(HEADER)
			make -C libft
			${CC} $(FLAGS)  $(OBJS) -Llibft -lft -o $(NAME)

%.o : %.c
			${CC} $(FLAGS) -c $< -o $@

clean:
			${RM} $(OBJS)
			make -C libft clean

fclean:		clean
			make -C libft fclean
			${RM} $(NAME)
re:			fclean all

norm:
			norminette $(SRCS)
			norminette $(HEADER)
			norminette libft/*.c

.PHONY:		all clean fclean re norm