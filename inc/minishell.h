/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/03 04:38:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*==============================	LIBRARIES	==============================*/

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <readline.h>
# include <history.h>
# include <errno.h>

/*=================================	MACROS	==================================*/

//Colours
# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"

//Signals
# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT

//ASCII characters
# define C_VERTICAL_BAR 124
# define C_LESS 60
# define C_GREAT 62
# define C_DOLLAR 36
# define C_ONE_QUOTE 39
# define C_TWO_QUOTE 34

//Redirection type
# define IN 0
# define HERE_DOC 1
# define OUT_TRUNC 2
# define OUT_APPEND 3

/*===============================	STRUCTURES	==============================*/

typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_token;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lex;

typedef struct s_in_out
{
	int				type;
	char			*file;
	struct s_in_out	*next;
}	t_in_out;

typedef struct s_cmd
{
	char			**args;
	t_in_out		*redirect;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

/*===============================	FUNCTIONS	==============================*/

//Holds minishell loop: MiniShell$>....
/*	ENTRY	*/
void	generate_terminal(char **envp);
char	*generate_entry(char **envp);
int		ft_array_len(char **array);
char	*ft_joincolors(char *array);

//Builtint shell commands
/*	BUILTINS	*/
void	ft_export(char **comand, char **envp);
void	ft_unset(char **comand, char **envp);
void	ft_echo(char **comand);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_cd(char **comand, char **envp);

//Converts input string to tokens for minishell to interpret
/*	TOKENIZER	*/
int		tokenizer(char *str, t_lex **lexer);
int		create_word(char *str, int i, t_lex *new, int *quoted);
int		create_token(char *str, int i, t_lex *lexer);
int		ft_isspace(int c);
int		ft_isquote(int c);
int		ft_isreserved(int c);
void	print_tokens(t_lex *lexer, char *str);
t_lex	*lexer_lstnew(void);
void	lexer_lstadd_back(t_lex **lst, t_lex *new);
void	lexer_lstclear(t_lex **lst);
int		lexer_lstsize(t_lex *lst);
t_lex	*lexer_lstlast(t_lex *lst);

//Converts token list (lexer) into a simple arguments list
/*	PARSER	*/
int		parser(t_cmd **commands, t_lex **lexer);
t_cmd	*parser_lstnew(void);
void	parser_lstadd_back(t_cmd **lst, t_cmd *new);
void	parser_lstclear(t_cmd **lst);
int		parser_lstsize(t_cmd *lst);
t_cmd	*parser_lstlast(t_cmd *lst);

//Reads from lexer structure and expands variables
/*	EXPANSOR	*/

//Handle signals
/*	SIGNALS	*/
void	init_signals(void);

//General utility functions
/*	UTILS	*/
char	*find_home(char **envp);
char	**ft_splitn(char *str, char c, int qtt);
int		count_spaces(char *str);
int		ft_strcmp(const char *s1, const char *s2);

#endif
