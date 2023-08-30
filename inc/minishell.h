/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/24 17:47:04 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <readline.h>
# include <history.h>

/*--------------------------------MACROS--------------------------------*/

# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"
# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT
# define EXIT_SON 0
# define EXIT_DAD 1

/*------------------------------FUNCTIONS-------------------------------*/

char	*generate_entry(char **envp);
char	**generate(char *str);
int		ft_array_len(char **array);
int		test_exist(char *str);
void	init_signals(void);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_cd(char **comand, char **envp);
char	*find_home(char **envp);
void	ft_echo(char **comand);
char	**ft_splitn(char *str, char c, int qtt);
int		count_spaces(char *str);
void	ft_export(char **comand, char **envp);
void	ft_unset(char **comand, char **envp);

#endif