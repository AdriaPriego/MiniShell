/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:03:59 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/06 19:54:18 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_quote	*init_quote(void)
{
	t_quote	*quote;

	quote = malloc(sizeof(t_quote));
	quote->one = 0;
	quote->two = 0;
	return (quote);
}

int	find_quote(t_quote *quote, int i, char *str)
{
	if (str[i] == C_TWO_QUOTE && quote->one == 0 && quote->two == 0)
	{
		quote->two = 1;
		i++;
	}
	else if (str[i] == C_TWO_QUOTE && quote->one == 0 && quote->two == 1)
	{
		quote->two = 0;
		i++;
	}
	if (str[i] == C_ONE_QUOTE && quote->one == 0 && quote->two == 0)
	{
		quote->one = 1;
		i++;
	}
	else if (str[i] == C_ONE_QUOTE && quote->one == 1 && quote->two == 0)
	{
		quote->one = 0;
		i++;
	}
	return (i);
}

int	calc_len_expanded(char *str, char **envp)
{
	int		i;
	int		len;
	char	*value;
	t_quote	*quote;

	i = 0;
	len = 0;
	quote = init_quote();
	while (str[i] != '\0')
	{
		i = find_quote(quote, i, str);
		if (str[i] == '$' && quote->one == 0)
		{
			value = expand(&str[i], envp);
			len += ft_strlen(value);
			i += ft_omit_var(&str[i]) - 1;
		}
		else
			len++;
		i++;
	}
	return (len);
}

int	ft_omit_var(char *var)
{
	int	i;

	i = 1;
	while (ft_isalnum(var[i]) || var[i] == '_')
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
