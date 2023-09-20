/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:14:06 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/20 18:14:36 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	expand_redirections(t_io *redir, char **env, int ex_s)
{
	char	*str;

	while (redir)
	{
		if (redir->file != NULL)
		{
			str = malloc(calc_len_expan(redir->file, env, ex_s) + 1);
			if (!str)
				return (1);
			ft_memset(str, '\0', calc_len_expan(redir->file, env, ex_s) + 1);
			check_expand(redir->file, ex_s, str, env);
			if (ft_change_redirection(redir, str) == 1)
				return (1);
			redir = redir->next;
		}
		else
			redir = redir->next;
	}
	return (0);
}
