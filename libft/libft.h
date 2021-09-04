/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:24:50 by desausag          #+#    #+#             */
/*   Updated: 2021/07/23 15:13:47 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int					ft_isalnum(int c);
int     			ft_atoi_clever(const char *str);
int					ft_isalpha(int c);

int					ft_isascii(int ch);

int					ft_isdigit(int ch);

int					ft_isprint(int c);

size_t				ft_strlen(const char *src);

int					ft_strncmp(const char *s1, const char *s2, size_t c);

char				*ft_strrchr(const char *str, int ch);

int					ft_tolower(int character);

int					ft_toupper(int c);

int					ft_atoi(const char *str);

void				*ft_memset(void *destination, int c, size_t n);

void				ft_bzero(void *s, size_t n);

void				*ft_memcpy(void *destination, const void *source, size_t n);

void				*ft_memccpy(void *destination, const void *source, int c, \
					size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

void				*ft_memchr(const void *arr, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

char				*ft_strchr(const char *s, int c);

size_t				ft_strlcat(char *destination, const char *append, \
					size_t size);

size_t				ft_strlcpy(char *destination, const char *append, \
					size_t size);

char				*ft_strnstr(const char *large, const char *small, \
					size_t len);

char				*ft_strdup(const char *str);

void				*ft_calloc(size_t num, size_t size);

char				*ft_substr(char const *s, unsigned int start, size_t len);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_itoa(int n);

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char				**ft_split(char const *s, char c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);

void				ft_lstadd_front(t_list **lst, t_list *new);

t_list				*ft_lstnew(void *content);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
#endif
