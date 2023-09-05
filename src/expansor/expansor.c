/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:10:15 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/05 19:28:37 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MIRAR QUE SE LE PASSA CON SEGURIDAD

#include <minishell.h>

void	ft_optimize_expan(t_lex **lexer)
{
	t_lex	*aux;
	t_lex	*tmp;

	if ((*lexer)->word && (*lexer)->word[0] == '\0')
	{
		aux = *lexer;
		free(aux->word);
		free(aux);
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

int		ft_omit_var(char *var)
{
	int	i;

	i = 1;
	while (ft_isalnum(var[i]))
		i++;
	return (i);
}

char	*obtain_var(char *str)
{
	char	*var;
	int		i;

	i = 0;
	str++;
	var = malloc(ft_strlen_chr(str, '$') + 1);
	if (!var)
		return (NULL);
	while (ft_isalnum(str[i]) == 1)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*expand(char *str, char **envp)
{
	int	i;
	char	*var;
	char	*value;

	i = 0;
	value = NULL;
	var = obtain_var(str);
	if (var == NULL)
		return (NULL);	
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen_chr(envp[i], '=')) == 0)
		{
			value = ft_strchr(envp[i], '=');
			free(var);
			return (value + 1);
		}
		i++;
	}
	free(var);
	return (NULL);
}

void	expansor(t_lex **def, char **envp)
{
	t_lex	*lexer;
	char	*str;
	int		i;
	int		j;
	int		quote;
	char	*value;
	int		double_quote;


	lexer = *def;
	while (lexer)
	{
		quote = 0;
		double_quote = 0;
		j = 0;
		i = 0;
		str = malloc(calc_len_expanded(lexer->word, envp) + 1);
		ft_memset(str, '\0', calc_len_expanded(lexer->word, envp) + 1);
		while (lexer->token == NONE && lexer->word[i] != '\0')
		{
			if (lexer->word[i] == C_TWO_QUOTE && quote == 0 && double_quote == 0)
			{
				double_quote = 1;
				i++;
			}
			else if (lexer->word[i] == C_TWO_QUOTE && quote == 0 && double_quote == 1)
			{
				double_quote = 0;
				i++;
			}
			if (lexer->word[i] == C_ONE_QUOTE && quote == 0 && double_quote == 0)
			{
				quote = 1;
				i++;
			}
			else if (lexer->word[i] == C_ONE_QUOTE && quote == 1 && double_quote == 0)
			{
				quote = 0;
				i++;
			}
			if (lexer->word[i] == '$' && quote == 0)
			{
				value = expand(&lexer->word[i], envp);
				if (value)
				{
					ft_strlcat(str, value, calc_len_expanded(lexer->word, envp) + 1);
					j = ft_strlen(str);
				}
				i += ft_omit_var(&lexer->word[i]) - 1;
			}
			else
				str[j++] = lexer->word[i];
			i++;
		}
		str[j] = '\0';
		lexer = ft_change_lexer(lexer, str);
		free(str);
	}
}
