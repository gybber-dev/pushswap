/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:02:40 by desausag          #+#    #+#             */
/*   Updated: 2021/07/23 15:13:47 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strrchr(set, *s1))
		s1++;
	if (*s1 == '\0')
		return (ft_calloc(1, 1));
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len]))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
