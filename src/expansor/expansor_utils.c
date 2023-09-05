/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:03:59 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/05 18:36:59 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	calc_len_expanded(char *str, char **envp)
{
	int		i;
	int		len;
	char	*value;
	int		quote;
	int		double_quote;

	i = 0;
	len = 0;
	quote = 0;
	double_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == C_TWO_QUOTE && quote == 0 && double_quote == 0)
		{
			double_quote = 1;
			i++;
		}
		else if (str[i] == C_TWO_QUOTE && quote == 0 && double_quote == 1)
		{
			double_quote = 0;
			i++;
		}
		if (str[i] == C_ONE_QUOTE && quote == 0 && double_quote == 0)
		{
			quote = 1;
			i++;
		}
		else if (str[i] == C_ONE_QUOTE && quote == 1 && double_quote == 0)
		{
			quote = 0;
			i++;
		}
		if (str[i] == '$' && quote == 0)
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
