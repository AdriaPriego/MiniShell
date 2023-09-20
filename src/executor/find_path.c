/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:45:52 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/20 21:43:00 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	try_paths(char **full_path, char *cmd, char **path)
{
	char	*temp;
	int		i;

	i = -1;
	while (full_path[++i])
	{
		temp = ft_strjoin(full_path[i], "/");
		if (!temp)
			return (1);
		*path = ft_strjoin(temp, cmd);
		free(temp);
		if (!*path)
			return (1);
		if (access(*path, F_OK) == 0)
		{
			if (access(*path, X_OK) == 0)
				return (0);
			else
				return (CMD_NO_ACCESS);
		}
		free (*path);
	}
	return (CMD_NOT_FOUND);
}

int	try_local_path(char *cmd, char **path)
{
	char	*temp;
	char	*temp2;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (1);
	temp2 = ft_strjoin(temp, "/");
	if (!temp2)
		return (free(temp), 1);
	*path = ft_strjoin(temp2, cmd);
	free (temp);
	free (temp2);
	if (!*path)
		return (1);
	if (access(*path, F_OK) == 0)
	{
		if (access(*path, X_OK) == 0)
			return (0);
		else
			return (CMD_NO_ACCESS);
	}
	return (CMD_NOT_FOUND);
}

int	try_absolute_path(char *cmd, char **path)
{
	*path = ft_strdup(cmd);
	if (!*path)
		return (1);
	if (access(*path, F_OK) == 0)
	{
		if (access(*path, X_OK) == 0)
			return (0);
		else
			return (CMD_NO_ACCESS);
	}
	return (CMD_NOT_FOUND);
}

int	search_path(char *cmd, char **envp, char **path)
{
	char	**full_path;
	int		i;
	int		exit_status;

	if (!*cmd)
		return (CMD_NOT_FOUND);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL && envp[i])
		i++;
	full_path = ft_split(envp[i] + 5, ':');
	if (!full_path)
		return (1);
	exit_status = try_paths(full_path, cmd, path);
	if (exit_status == CMD_NOT_FOUND)
		exit_status = try_local_path(cmd, path);
	if (exit_status == CMD_NOT_FOUND)
		exit_status = try_absolute_path(cmd, path);
	if (exit_status == CMD_NOT_FOUND && ft_isdir(cmd))
	{
		exit_status = NO_SUCH_FILE;
		if (access(cmd, F_OK) == 0)
			exit_status = IS_A_DIR;
	}
	ft_free_malloc_array(full_path, ft_array_len(full_path));
	return (exit_status);
}
