/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:10:15 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/15 14:04:03 by apriego-         ###   ########.fr       */
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

int	ft_change_comand(t_cmd	*comand, int i, char *str)
{
	free(comand->args[i]);
	comand->args[i] = ft_strdup(str);
	if (!comand->args[i])
		return (1);
	comand = comand->next;
	free(str);
	str = NULL;
	return (0);
}

char	*expand(char *str, char **env)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	var = obtain_var(str);
	if (var == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strcmp_env(env[i], var) == 0)
		{
			value = ft_strchr(env[i], '=');
			free(var);
			return (value + 1);
		}
		i++;
	}
	free(var);
	return (NULL);
}

void	check_expand(char *word, int exit, char *str, char **env)
{
	int		i;
	int		j;
	char	*value;
	t_quote	quote;

	(1) && ((i = 0) || (j = 0));
	init_quote(&quote);
	while (word[i] != '\0')
	{
		find_quote(&quote, i, word);
		if (word[i] == '$' && quote.one == 0)
		{
			if (ft_strncmp(&word[i], "$?", 2) == 0)
				value = ft_itoa(exit);
			else
				value = expand(&word[i], env);
			expand_var(&word[i], value, str, calc_len_expan(word, env, exit));
			i += ft_omit_var(&word[i]) - 1;
			j = ft_strlen(str);
		}
		else if (ft_isliteral(word[i], &quote) == 1)
			str[j++] = word[i];
		i++;
	}
	str[j] = '\0';
}

int	expansor(t_cmd *def, char **env, int status)
{
	char	*str;
	int		i;

	if (!def)
		return (0);
	i = 0;
	while (def->args[i])
	{
		if (def->args[i] != NULL)
		{
			str = malloc(calc_len_expan(def->args[i], env, status) + 1);
			if (!str)
				return (1);
			ft_memset(str, '\0', calc_len_expan(def->args[i], env, status)
				+ 1);
			check_expand(def->args[i], status, str, env);
			if (ft_change_comand(def, i, str) == 1)
				return (1);
			i++;
		}
		else
			def = def->next;
	}
	return (0);
}
