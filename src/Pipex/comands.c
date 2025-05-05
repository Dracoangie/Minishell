/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:40:01 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/05 11:42:42 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*search_executable_in_paths(char *cmd, char **paths)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
		{
			free_args(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_args(paths);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (search_executable_in_paths(cmd, paths));
}

void	execute_command(char *cmd, char **envp, t_shell *mn_shell)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_cmd_path(args[0], envp);
	if (!path || access(path, X_OK) != 0)
	{
		write(2, args[0], ft_strlen(args[0]));
		print_error(mn_shell, ": command not found", 127);
		free_args(args);
		free(path);
		free(mn_shell->pipex->childs);
		close_pipes(mn_shell);
	}
	else if (execve(path, args, envp) == -1)
	{
		print_error(mn_shell, "execve error", EXIT_FAILURE);
		free_args(args);
		free(path);
		free(mn_shell->pipex->childs);
		close_pipes(mn_shell);
	}
}
