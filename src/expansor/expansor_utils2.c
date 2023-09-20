/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:55:38 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/19 13:40:37 by apriego-         ###   ########.fr       */
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
