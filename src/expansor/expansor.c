/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:10:15 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/06 19:54:33 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_optimize_expan(t_lex **lexer)
{
	t_lex	*aux;
	t_lex	*tmp;

	if ((*lexer)->word && (*lexer)->word[0] == '\0')
	{
		aux = *lexer;
		*lexer = (*lexer)->next;
	}
	aux = *lexer;
	tmp = aux;
	while (aux)
	{
		if (aux->word && aux->word[0] == '\0')
		{
			tmp->next = aux->next;
			free(aux->word);
			free(aux);
		}
		else
			tmp = aux;
		aux = tmp->next;
	}
}

t_lex	*ft_change_lexer(t_lex *lexer, char *str)
{
	free(lexer->word);
	lexer->word = ft_strdup(str);
	lexer = lexer->next;
	str[0] = '\0';
	return (lexer);
}

char	*expand(char *str, char **envp)
{
	int		i;
	char	*var;
	char	*dup;
	char	*value;

	i = 0;
	var = obtain_var(str);
	if (var == NULL)
		return (NULL);
	while (envp[i])
	{
		dup = malloc(ft_strlen_chr(envp[i], '='));
		ft_memcpy(dup, envp[i], ft_strlen_chr(envp[i], '='));
		if (ft_strncmp(dup, var, ft_strlen_chr(envp[i], '=')) == 0)
		{
			value = ft_strchr(envp[i], '=');
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

void	test(t_lex *lexer, t_quote *quote, char **envp, char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (lexer->token == NONE && lexer->word[i] != '\0')
	{
		i = find_quote(quote, i, lexer->word);
		if (lexer->word[i] == '$' && quote->one == 0)
		{
			value = expand(&lexer->word[i], envp);
			if (value)
			{
				ft_strlcat(str, value, calc_len_expanded(lexer->word, envp)+ 1);
				j = ft_strlen(str);
			}
			i += ft_omit_var(&lexer->word[i]) - 1;
		}
		else
			str[j++] = lexer->word[i];
		i++;
	}
	str[j] = '\0';
}

void	expansor(t_lex **def, char **envp)
{
	t_lex	*lexer;
	char	*str;
	t_quote	*quote;

	lexer = *def;
	while (lexer)
	{
		str = malloc(calc_len_expanded(lexer->word, envp) + 1);
		ft_memset(str, '\0', calc_len_expanded(lexer->word, envp) + 1);
		quote = init_quote();
		test(lexer, quote, envp, str);
		lexer = ft_change_lexer(lexer, str);
		free(str);
	}
}
