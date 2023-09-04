/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/04 23:17:25 by fbosch           ###   ########.fr       */
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
	else if (str[i] == C_LESS && str[i + 1] == C_LESS)
		new->token = LESS_LESS;
	else if (str[i] == C_GREAT && str[i + 1] != C_GREAT)
		new->token = GREAT;
	else if (str[i] == C_GREAT && str[i + 1] == C_GREAT)
		new->token = GREAT_GREAT;
	if (new->token == LESS_LESS || new->token == GREAT_GREAT)
		count = 2;
	else
		count = 1;
	return (count);
}

int	create_word(char *str, int i, t_lex *new, int *quoted)
{
	char	*word;
	int		j;

	j = 0;
	while (str[i + j])
	{
		if (*quoted == 1 && ft_isquote(str[i + j]) == 1)
			*quoted = 0;
		else if (*quoted == 0 && ft_isquote(str[i + j]) == 1)
			*quoted = 1;
		if (*quoted == 0 && (ft_isspace(str[i + j])
				|| ft_isreserved(str[i + j])))
			break ;
		j++;
	}
	word = ft_substr(str, i, j);
	if (!word)
		return (-1);
	new->word = word;
	return (j);
}

int	initialize_lexer_node(t_lex *new, char *str, int i, int *quoted)
{
	int		temp;

	if (ft_isreserved(str[i]))
		i += create_token(str, i, new);
	else
	{
		temp = create_word(str, i, new, quoted);
		if (temp == -1)
			return (-1);
		i += temp;
	}
	return (i);
}

/*	This function receives the input given on the terminal as a string
	and it creates a linked list of tokens, the tokens will be used
	to process the commands in a simpler way by the parser.
	Example:

	Input -> "ls -l | wc -c > outfile"
	Output -> linked_list {ls, -l, PIPE, wc, -c, GREAT, outfile}
*/
int	tokenizer(char *str, t_lex **lexer)
{
	t_lex	*new;
	int		i;
	int		quoted;

	quoted = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			new = lexer_lstnew();
			if (!new)
				return (1);
			lexer_lstadd_back(lexer, new);
			i = initialize_lexer_node(new, str, i, &quoted);
			if (i == -1)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
