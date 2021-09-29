#include "../includes/pushswap.h"

int	get_arr_2x_len(char **arr)
{
	int		res;

	res = 0;
	while (*arr++)
		res++;
	return (res);
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
