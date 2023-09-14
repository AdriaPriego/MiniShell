/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:10:15 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/14 21:40:36 by fbosch           ###   ########.fr       */
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

int	ft_change_command(t_cmd	*command, int i, char *str)
{
	free(command->args[i]);
	command->args[i] = ft_strdup(str);
	if (!command->args[i])
		return (1);
	command = command->next;
	free(str);
	str = NULL;
	return (0);
}

char	*expand(char *str, char **env)
{
	int		i;
	char	*var;
	char	*dup;
	char	*value;

	i = 0;
	var = obtain_var(str);
	if (var == NULL)
		return (NULL);
	while (env[i])
	{
		dup = malloc(ft_strlen_chr(env[i], '='));
		ft_memcpy(dup, env[i], ft_strlen_chr(env[i], '='));
		if (ft_strncmp(dup, var, ft_strlen_chr(env[i], '=')) == 0)
		{
			value = ft_strchr(env[i], '=');
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

void	check_expand(char *word, t_quote *quote, char *str, char **env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (word[i] != '\0')
	{
		find_quote(quote, i, word);
		if (word[i] == '$' && quote->one == 0)
		{
			value = expand(&word[i], env);
			if (value)
			{
				ft_strlcat(str, value, calc_len_expanded(word, env)
					+ 1);
				j = ft_strlen(str);
			}
			i += ft_omit_var(&word[i]) - 1;
		}
		else if (ft_isliteral(word[i], quote) == 1)
			str[j++] = word[i];
		i++;
	}
	str[j] = '\0';
}

int	expansor(t_cmd *def, char **env)
{
	char	*str;
	int		i;
	t_quote	quote;

	if (!def)
		return (0);
	i = 0;
	while (def->args[i])
	{
		if (def->args[i] != NULL)
		{
			str = malloc(calc_len_expanded(def->args[i], env) + 1);
			if (!str)
				return (1);
			ft_memset(str, '\0', calc_len_expanded(def->args[i], env) + 1);
			init_quote(&quote);
			check_expand(def->args[i], &quote, str, env);
			if (ft_change_command(def, i, str) == 1)
				return (1);
			i++;
		}
		else
			def = def->next;
	}
	return (0);
}
