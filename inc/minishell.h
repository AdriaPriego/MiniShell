/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/25 17:50:30 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>

/*--------------------------------MACROS--------------------------------*/

# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"
# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT

# define WORD 0
# define RESERVED 1


/*------------------------------STRUCTURES-------------------------------*/

typedef enum s_token
{
    PIPE = 1,
    GREAT,
    GREAT_GREAT,
    LESS,
    LESS_LESS,
} t_token;


typedef struct s_lexer
{
	char			*word;
	t_token			token;
	struct s_lexer	*next;
}	t_lex;

/*------------------------------FUNCTIONS-------------------------------*/

t_lex	*lexer_lstnew(void);
void	lexer_lstadd_back(t_lex **lst, t_lex *new);
void	lexer_lstclear(t_lex **lst);
int		lexer_lstsize(t_lex *lst);
t_lex	*lexer_lstlast(t_lex *lst);




#endif