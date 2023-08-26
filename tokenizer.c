/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/27 00:03:11 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	create_token(char *str, int i, t_lex *new)
{
	int	count;

	if (str[i] == C_VERTICAL_BAR)
		new->token = PIPE;
	else if (str[i] == C_LESS && str[i + 1] != C_LESS)
		new->token = LESS;
	else if (str[i] == C_LESS && str[i] == C_LESS)
		new->token = LESS_LESS;
	else if (str[i] == C_GREAT && str[i + 1] != C_GREAT)
		new->token = GREAT;
	else if (str[i] == C_GREAT && str[i] == C_GREAT)
		new->token = GREAT_GREAT;
	else if (str[i] == C_SINGLE_QUOTE)
		new->token = SINGLE_QUOTE;
	else if (str[i] == C_DOUBLE_QUOTE)
		new->token = DOUBLE_QUOTE;
	if (new->token == LESS_LESS || new->token == GREAT_GREAT)
		count = 2;
	else
		count = 1;
	return (count);
}

int	create_word(char *str, int i, t_lex *new)
{
	char	*word;
	int		j;

	j = 1;
	while (str[i + j] && !ft_isspace(str[i + j]) && !ft_isreserved(str[i + j])
		&& str[i + j] != C_DOLLAR)
		j++;
	word = ft_substr(str, i, j);
	if (!word)
		return (1);
	new->word = word;
	return (j);
}

/*	This function receives the input given on the terminal as a string
	and it creates a linked list of tokens, the tokens will be used
	to process the commands in a simpler way by the parser.

	Example:

	Input -> "ls -l | wc -c > outfile"
	Output -> linked_list {ls, -l, PIPE, wc, -c, GREAT, outfile}
*/
t_lex	*tokenizer(char *str)
{
	t_lex	*lexer;
	t_lex	*new;
	int		i;

	lexer = NULL;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			new = lexer_lstnew();
			if (!new)
				return (NULL);
			lexer_lstadd_back(&lexer, new);
			if (ft_isreserved(str[i]) && str[i] != C_DOLLAR)
				i += create_token(str, i, new); //check returns parse errors
			else
				i += create_word(str, i, new);
		}
		else
			i++;
	}
	print_tokens(lexer);
	return (lexer);
}

int	main(int ac, char **av)
{
	t_lex	*lexer;
	//t_cmd	*commands;

	if (ac != 2)
		return (1);
	printf("entry: %s\n", av[1]);
	printf("token: ");
	lexer = tokenizer(av[1]); //check return of lexer
	//commands = parser(lexer);
	//expander
	lexer_lstclear(&lexer);
	printf("\n");
}
