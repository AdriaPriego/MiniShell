/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/08/26 20:17:30 by fbosch           ###   ########.fr       */
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
	while (str[i + j] && !ft_isspace(str[i + j]) && !ft_isreserved(str[i + j]))
		j++;
	word = ft_substr(str, i, j);
	if (!word)
		return (1);
	new->word = word;
	return (j);
}

int	tokenizer(char *str)
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
				return (1);
			lexer_lstadd_back(&lexer, new);
			if (ft_isreserved(str[i]))
				i += create_token(str, i, new); //check both returns to parse errors
			else
				i += create_word(str, i, new);
		}
		else
			i++;
	}
	print_tokens(lexer);
	return (0);
}

void print_tokens(t_lex *lexer)
{
	while (lexer)
	{
		if (!lexer->word)
		{
			if (lexer->token == PIPE)
				printf(" PIPE");
			else if (lexer->token == LESS)
				printf(" LESS");
			else if (lexer->token == LESS_LESS)
				printf(" LESS_LESS");
			else if (lexer->token == GREAT)
				printf(" GREAT");
			else if (lexer->token == GREAT_GREAT)
				printf(" GREAT_GREAT");
			else if (lexer->token == SINGLE_QUOTE)
				printf(" SINGLE_QUOTE");
			else if (lexer->token == DOUBLE_QUOTE)
				printf(" DOUBLE_QUOTE");
		}
		else
			printf(" %s ", lexer->word);
		lexer = lexer->next;
	}
}
int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	printf("entry: %s\n", av[1]);
	printf("token: ");
	tokenizer(av[1]);
	printf("\n");
}
