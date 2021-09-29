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
