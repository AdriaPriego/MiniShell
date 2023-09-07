/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/07 17:27:09 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
	> out							"Redirects {empty} to a file called out"
	< out							"It redirects standard input to a file called 'out' if it exists"
	ls |							"Opens std input" // (((("Syntax error"))))
	cat | cat						"Standard input open to write something"
	ls -la <						"Syntax error"
	|								"Syntax error"
	ls | sleep 3 | < dssd			"Executes 3 pipes and throws error for last process {file doesn't exist}"
	ls | sleep 3 | << eof			"Calls here doc and doesn't execute any process until here doc is finished"
	cat << eof < infile				"Open here_doc but uses infile as input for cat"
	< no_file wc
				-c < out | ls		"First command not executed because no_file doesn't exist,
				'ls' executed"

	When it comes to redirections the last parameter is used,
		the rest of files will be created independently"
*/

/*==============================	LIBRARIES	==============================*/

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <readline.h>
# include <history.h>
# include <errno.h>

/*=================================	MACROS	==================================*/

// Colours
# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"

// Signals
# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT

// ASCII characters
# define C_VERTICAL_BAR 124
# define C_LESS 60
# define C_GREAT 62
# define C_DOLLAR 36
# define C_ONE_QUOTE 39
# define C_TWO_QUOTE 34

/* //Redirection type
# define IN 0
# define HERE_DOC 1
# define OUT_TRUNC 2
# define OUT_APPEND 3 */

// General errors
# define MSSG_INVALID_ARGS "Invalid arguments: Usage [./minishell]\n"
# define MSSG_MEMORY_ERROR "Memory error, please free space and attempt again\n"

// Parser syntax errors
# define SYNTAX_ERR 42
# define SYNTAX_NL 0
# define SYNTAX_PIPE 1
# define SYNTAX_LESS 2
# define SYNTAX_GREAT 3
# define SYNTAX_LESS_LESS 4
# define SYNTAX_GREAT_GREAT 5

/*===============================	STRUCTURES	==============================*/

typedef enum s_redirect_type
{
	REDIRECT_NONE = 0,
	IN,
	HERE_DOC,
	OUT_TRUNC,
	OUT_APPEND,
}					t_type;

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

typedef struct s_in_out
{
	t_type			type;
	char			*file;
	struct s_in_out	*next;
}					t_io;

typedef struct s_cmd
{
	char			**args;
	t_io			*redirect;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

/*===============================	FUNCTIONS	==============================*/

// Holds minishell loop: MiniShell$>....
/*	ENTRY	*/
void				generate_terminal(char **envp);
int					string_to_command(char *str, t_cmd **commands, char **env);
char				*generate_entry(char **envp);
char				*ft_joincolors(char *array);

// Builtint shell commands
/*	BUILTINS	*/
void				ft_export(char **comand, char **envp);
void				ft_unset(char **comand, char **envp);
void				ft_echo(char **comand);
void				ft_pwd(void);
void				ft_env(char **envp);
void				ft_cd(char **comand, char **envp);

// Converts input string to tokens for minishell to interpret
/*	TOKENIZER	*/
int					tokenizer(char *str, t_lex **lexer);
int					create_word(char *str, int i, t_lex *new);
int					create_token(char *str, int i, t_lex *lexer);
int					ft_isspace(int c);
int					ft_isquote(int c);
int					ft_isreserved(int c);
void				print_tokens(t_lex *lexer, char *str);
t_lex				*lexer_lstnew(void);
void				lexer_lstadd_back(t_lex **lst, t_lex *new);
void				lexer_lstclear(t_lex **lst);
int					lexer_lstsize(t_lex *lst);
t_lex				*lexer_lstlast(t_lex *lst);

// Reads from lexer structure and expands variables
/*	EXPANSOR	*/
int					expansor(t_lex **def, char **envp);
char				*expand(char *str, char **envp);
int					ft_omit_var(char *var);
int					calc_len_expanded(char *str, char **envp);
char				*obtain_var(char *str);
void				init_quote(t_quote *quote);
void				find_quote(t_quote *quote, int i, char *str);

// Converts token list (lexer) into a simple arguments list
/*	PARSER	*/
int					parser(t_cmd **commands, t_lex **lexer);
int					create_simple_command(t_lex **head, t_cmd *cmd);
int					fill_command(t_lex **head, t_io **redirect, t_cmd *cmd);
int					add_redirection(t_io **redirect, t_lex **head);
int					count_arguments(t_lex *lexer);
void				print_commands(t_cmd *commands); // DEBUG ONLY AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
void				parser_error(int error);
int					check_duplicate_tokens(t_lex *lexer);
int					check_pipe_error(t_lex *lexer);
int					check_syntax_error(t_lex *lexer);
t_cmd				*parser_lstnew(void);
void				parser_lstadd_back(t_cmd **lst, t_cmd *new);
void				parser_lstclear(t_cmd **lst);
int					parser_lstsize(t_cmd *lst);
t_cmd				*parser_lstlast(t_cmd *lst);
t_io				*redirect_lstnew(void);
void				redirect_lstadd_back(t_io **lst, t_io *new);
void				redirect_lstclear(t_io **lst);
int					redirect_lstsize(t_io *lst);
t_io				*redirect_lstlast(t_io *lst);

// Receives clean arguments in a t_cmd* linked list and manages execution
/*	EXECUTOR	*/
int					execute_commands(t_cmd *commands, char **envp);
int					error_return(char *error);

// Handle signals
/*	SIGNALS	*/
void				init_signals(void);

// General utility functions
/*	UTILS	*/
char				*find_home(char **envp);
char				**ft_splitn(char *str, char c, int qtt);
int					count_spaces(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strlen_chr(char *str, char c);

#endif
