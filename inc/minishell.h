/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/27 00:02:55 by fbosch           ###   ########.fr       */
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

# define C_VERTICAL_BAR 124
# define C_LESS 60
# define C_GREAT 62
# define C_DOLLAR 36
# define C_SINGLE_QUOTE 39
# define C_DOUBLE_QUOTE 34

/*------------------------------STRUCTURES-------------------------------*/

typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	DOLLAR,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_token;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lex;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

/*------------------------------TOKENIZER-------------------------------*/
t_lex		*tokenizer(char *str);
int			create_token(char *str, int i, t_lex *lexer);

/*------------------------------TOKENIZER UTILS-------------------------------*/
int			ft_isspace(int c);
int			ft_isreserved(int c);
void		print_tokens(t_lex *lexer);

/*------------------------------TOKENIZER LISTS-------------------------------*/
t_lex		*lexer_lstnew(void);
void		lexer_lstadd_back(t_lex **lst, t_lex *new);
void		lexer_lstclear(t_lex **lst);
int			lexer_lstsize(t_lex *lst);
t_lex		*lexer_lstlast(t_lex *lst);

/*------------------------------PARSER-------------------------------*/
t_cmd	*parser(t_lex *lexer);

#endif