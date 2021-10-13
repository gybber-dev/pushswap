/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:31:47 by desausag          #+#    #+#             */
/*   Updated: 2021/07/23 15:13:47 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		minus;
	int		num;

	i = 0;
	minus = 1;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (num * minus);
}

int	ft_atoi_clever(const char *str)
{
	int		i;
	long	result;
	int		positive;

	i = 0;
	result = 0;
	positive = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || \
	(str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		positive = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (((result > 2147483647) && positive) || \
		((result > 2147483648) && !positive))
			return (-1);
		i++;
	}
	if (positive == 0)
		result = result * (-1);
	return ((int)result);
}
