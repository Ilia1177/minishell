/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:23:22 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/16 19:00:51 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *ptr, int x, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
/*copy string src in dest guarantee null terminated*/
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
/* seek and find the first occurence of c in s - if not return NULL*/
char		*ft_strchr(const char *s, int c);
/* seek and find the last occurence of c in s - if not return NULL*/
char		*ft_strrchr(const char *s, int c);
/* compare 2 string until n byte return s1-s2*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
/*seek and find first intance of c until n byte - if not return NULL*/
void		*ft_memchr(const void *s, int c, size_t n);
/* compare 2 buffer until n byte return s1-s2, 0 if n=0*/
int			ft_memcmp(const void *s1, const void *s2, size_t n);
/*seek and find the first little in len big, if little=0 return big, 
 if not find NULL  */
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
long int	ft_atol(const char *nptr);
int			ft_atoier(const char *nptr, int *error);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
/*return str from start until len*/
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
/* remove each char of set in begin and end s1*/
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*BONUS*/

typedef struct s_token
{
	char **content;
	t_type	type;
	int		error;
	struct s_token *next;
}	t_token;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
