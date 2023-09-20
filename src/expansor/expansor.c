/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:10:15 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/20 18:53:11 by fbosch           ###   ########.fr       */
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
		if (((word[i] == '$' && (ft_isalpha(word[i + 1]) == 1 || word[i + 1] == '_' || word[i + 1] == '?')) || (word[i] == '~' && (word[i + 1] == '/' || word[i + 1] == '\0') && i == 0)) && quote.one == 0)
		{
			if (word[i] == '~')
				value = find_home(env);
			else if (ft_strncmp(&word[i], "$?", 2) == 0)
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

int	ft_change_redirection(t_io *redirect, char *str)
{
	free(redirect->file);
	redirect->file = ft_strdup(str);
	if (!redirect->file)
		return (1);
	free(str);
	str = NULL;
	return (0);
}

int	expand_redirections(t_io *redirect, char **env, int ex_s)
{
	char	*str;

	while (redirect)
	{
		if (redirect->file != NULL)
		{
			str = malloc(calc_len_expan(redirect->file, env, ex_s) + 1);
			if (!str)
				return (1);
			ft_memset(str, '\0', calc_len_expan(redirect->file, env, ex_s) + 1);
			check_expand(redirect->file, ex_s, str, env);
			if (ft_change_redirection(redirect, str) == 1)
				return (1);
			redirect = redirect->next;
		}
		else
			redirect = redirect->next;
	}
	return (0);
}

int	expansor(t_cmd *def, char **env, int ex_s)
{
	char	*str;
	int		i;

	i = 0;
	while (def)
	{
		if (def->args[i] != NULL)
		{
			str = malloc(calc_len_expan(def->args[i], env, ex_s) + 1);
			if (!str)
				return (1);
			ft_memset(str, '\0', calc_len_expan(def->args[i], env, ex_s) + 1);
			check_expand(def->args[i], ex_s, str, env);
			if (ft_change_command(def, i++, str) == 1)
				return (1);
			if (expand_redirections(def->redirect, env, ex_s) == 1)
				return (1);
		}
		else
		{
			def = def->next;
			i = 0;
		}
	}
	return (0);
}
