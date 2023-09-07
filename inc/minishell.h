/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/07 11:02:17 by apriego-         ###   ########.fr       */
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
# include <errno.h>

/*--------------------------------MACROS--------------------------------*/

# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"
# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT
# define EXIT_SON 0
# define EXIT_DAD 1

# define C_VERTICAL_BAR 124
# define C_LESS 60
# define C_GREAT 62
# define C_DOLLAR 36
# define C_ONE_QUOTE 39
# define C_TWO_QUOTE 34

# define EXPAND 0
# define NO_EXPAND 1

/*------------------------------STRUCTURES-------------------------------*/

typedef enum s_token
{
	NONE = 0,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}					t_token;

typedef struct s_quote
{
	int				two;
	int				one;
}					t_quote;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lex;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

char				*generate_entry(char **envp);
int					ft_array_len(char **array);
void				init_signals(void);
void				ft_pwd(void);
void				ft_env(char **envp);
void				ft_cd(char **comand, char **envp);
char				*find_home(char **envp);
void				ft_echo(char **comand);
char				**ft_splitn(char *str, char c, int qtt);
int					count_spaces(char *str);
void				ft_export(char **comand, char **envp);
void				ft_unset(char **comand, char **envp);
void				generate_terminal(char **envp);
int					execute_comand(char **comand, char **envp);
int					ft_strcmp(const char *s1, const char *s2);
void				expansor(t_lex **def, char **envp);
int					ft_strlen_chr(char *str, char c);
void				ft_optimize_expan(t_lex **lexer);
char				*expand(char *str, char **envp);
int					ft_omit_var(char *var);
int					calc_len_expanded(char *str, char **envp);
char				*obtain_var(char *str);

/*------------------------------TOKENIZER-------------------------------*/
int					tokenizer(char *str, t_lex **lexer);
int					create_word(char *str, int i, t_lex *new, int *quoted);
int					create_token(char *str, int i, t_lex *lexer);

/*------------------------------TOKENIZER UTILS-------------------------------*/
int					ft_isspace(int c);
int					ft_isquote(int c);
int					ft_isreserved(int c);
void				print_tokens(t_lex *lexer);

/*------------------------------TOKENIZER LISTS-------------------------------*/
t_lex				*lexer_lstnew(void);
void				lexer_lstadd_back(t_lex **lst, t_lex *new);
void				lexer_lstclear(t_lex **lst);
int					lexer_lstsize(t_lex *lst);
t_lex				*lexer_lstlast(t_lex *lst);

/*------------------------------PARSER-------------------------------*/
t_cmd				*parser(t_lex *lexer);
t_quote				*init_quote(t_quote *quote);
int					find_quote(t_quote *quote, int i, char *str);

#endif