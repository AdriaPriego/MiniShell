/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:55:38 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/20 18:15:48 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	calc_len_value_expan(char *str, char **env, int status, int *len)
{
	int		i;
	char	*value;

	i = 0;
	if (str[0] == '~')
	{
		value = find_home(env);
		(*len) += ft_strlen(value);
		i += 1;
	}
	else if (ft_strncmp(str, "$?", 2) == 0)
	{
		(*len) += ft_numlen(status);
		i += 1;
	}
	else
	{
		value = expand(&str[i], env);
		(*len) += ft_strlen(value);
		i += ft_omit_var(&str[i]) - 1;
	}
	return (i);
}

void	expand_var(char *word, char *value, char *str, int len)
{
	if (value)
		ft_strlcat(str, value, len + 1);
	if (ft_strncmp(word, "$?", 2) == 0)
		free(value);
}

int	check_dollar(char *word, int i)
{
	if (word[i] == '$' && (ft_isalpha(word[i + 1]) == 1 || word[i + 1] == '_'
			|| word[i + 1] == '?'))
		return (1);
	return (0);
}

int	check_tilde(char *w, int i)
{
	if (w[i] == '~' && (w[i + 1] == '/' || w[i + 1] == '\0') && i == 0)
		return (1);
	return (0);
}

char	*create_value(char *word, int i, char **env, int exit)
{
	char	*value;

	if (word[i] == '~')
		value = find_home(env);
	else if (ft_strncmp(&word[i], "$?", 2) == 0)
		value = ft_itoa(exit);
	else
		value = expand(&word[i], env);
	return (value);
}
