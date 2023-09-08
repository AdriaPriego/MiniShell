/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:10:15 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/08 15:08:48 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isliteral(char c, t_quote *quote)
{
	if ((c == C_ONE_QUOTE && quote->two == 1) || (c == C_TWO_QUOTE
			&& quote->one == 1) || ft_isquote(c) == 0)
		return (1);
	return (0);
}

int	ft_change_lexer(t_lex **lexer, char *str)
{
	t_lex	*temp;

	temp = *lexer;
	free(temp->word);
	temp->word = ft_strdup(str);
	if (!temp->word && temp->token == NONE)
		return (1);
	temp = temp->next;
	*lexer = temp;
	free(str);
	str = NULL;
	return (0);
}

char	*expand(char *str)
{
	int		i;
	char	*var;
	char	*dup;
	char	*value;

	i = 0;
	var = obtain_var(str);
	if (var == NULL)
		return (NULL);
	while (g_global.env[i])
	{
		dup = malloc(ft_strlen_chr(g_global.env[i], '='));
		ft_memcpy(dup, g_global.env[i], ft_strlen_chr(g_global.env[i], '='));
		if (ft_strncmp(dup, var, ft_strlen_chr(g_global.env[i], '=')) == 0)
		{
			value = ft_strchr(g_global.env[i], '=');
			free(var);
			free(dup);
			return (value + 1);
		}
		i++;
		free(dup);
	}
	free(var);
	return (NULL);
}

void	check_expand(t_lex *lexer, t_quote *quote, char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (lexer->token == NONE && lexer->word[i] != '\0')
	{
		find_quote(quote, i, lexer->word);
		if (lexer->word[i] == '$' && quote->one == 0)
		{
			value = expand(&lexer->word[i]);
			if (value)
			{
				ft_strlcat(str, value, calc_len_expanded(lexer->word)
					+ 1);
				j = ft_strlen(str);
			}
			i += ft_omit_var(&lexer->word[i]) - 1;
		}
		else if (ft_isliteral(lexer->word[i], quote) == 1)
			str[j++] = lexer->word[i];
		i++;
	}
	str[j] = '\0';
}

int	expansor(t_lex **def)
{
	t_lex	*lexer;
	char	*str;
	t_quote	quote;

	lexer = *def;
	while (lexer)
	{
		if (lexer->word != NULL)
		{
			str = malloc(calc_len_expanded(lexer->word) + 1);
			if (!str)
				return (1);
			ft_memset(str, '\0', calc_len_expanded(lexer->word) + 1);
			init_quote(&quote);
			check_expand(lexer, &quote, str);
			if (ft_change_lexer(&lexer, str) == 1)
				return (1);
		}
		else
			lexer = lexer->next;
	}
	return (0);
}
