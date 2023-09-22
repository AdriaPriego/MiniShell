/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:13:58 by apriego-          #+#    #+#             */
/*   Updated: 2023/09/22 11:21:49 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_extra_path(char *cmd, char *envp, char **path, int exit_status)
{
	if (exit_status == CMD_NOT_FOUND)
		exit_status = try_local_path(cmd, path);
	if (exit_status == CMD_NOT_FOUND)
		exit_status = try_absolute_path(cmd, path);
	if (exit_status == CMD_NOT_FOUND && !envp)
		return (NO_SUCH_FILE);
	return (exit_status);
}
