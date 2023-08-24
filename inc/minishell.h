/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/24 11:00:05 by apriego-         ###   ########.fr       */
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

/*------------------------------FUNCTIONS-------------------------------*/

char	*generate_entry(void);
char	**generate(char *str);
int		ft_array_len(char **array);
int		test_exist(char *str);
void	init_signals(void);

#endif