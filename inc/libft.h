/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:17:51 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/18 13:33:07 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
void	*ft_calloc(size_t count, size_t size);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memset(void *b, int c, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t	dstsize);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
int		ft_printf(const char *str, ...);
int		ft_test_write(int test, int i);
int		ft_printundhex(unsigned int nb, int test);
int		ft_printuphex(unsigned int nb, int test);
int		ft_printpnt(unsigned long pointer);
int		ft_printunnbr(unsigned int num, int test);
int		ft_printnbr(int n);
int		ft_printchar(int c);
int		ft_printstr(char *str);
int		ft_printf_fd(int fd, const char *str, ...);
int		ft_test_write_fd(int test, int i);
int		ft_printundhex_fd(unsigned int nb, int test, int fd);
int		ft_printuphex_fd(unsigned int nb, int test, int fd);
int		ft_printpnt_fd(unsigned long pointer, int fd);
int		ft_printunnbr_fd(unsigned int num, int test, int fd);
int		ft_printnbr_fd(int n, int fd);
int		ft_printchar_fd(int c, int fd);
int		ft_printstr_fd(char *str, int fd);
int		ft_test_int(const char *str);
char	*ft_strchr_line(const char *s, int c);
size_t	ft_strlen_line(const char *s);
char	*ft_strjoin_line(char *s1, char *s2);
char	*get_next_line(int fd);
size_t	ft_len_line(const char *s);
void	ft_free_malloc_array(char **arr, int i);
int		ft_array_len(char **arr);
int		ft_numlen(int n);
char	*ft_to_lower(char *str);
#endif