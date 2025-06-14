/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:40:01 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/21 02:15:29 by angnavar         ###   ########.fr       */
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

char	*check_cmd(t_shell *mn_shell, char	**args)
{
	char	*path;

	path = get_cmd_path(args[0], mn_shell->envp);
	if (!path || access(path, X_OK) != 0)
	{
		write(2, args[0], ft_strlen(args[0]));
		perr_shll(mn_shell, ": command not found", 2);
		free(path);
		mn_shell->last_exit_code = 127;
		return (NULL);
	}
	return (path);
}

void	execute_command(t_cmd *cmd, t_shell *mn_shell)
{
	if (!cmd->has_cmd)
	{
		mn_shell->last_exit_code = EXIT_SUCCESS;
		return ;
	}
	if (!cmd->is_builtin)
	{
		if (execve(cmd->path, cmd->args, mn_shell->envp) == -1)
		{
			perr_name(mn_shell, cmd->args[0], "permission denied", 126);
			mn_shell->last_exit_code = 126;
		}
		else
			mn_shell->last_exit_code = EXIT_SUCCESS;
		return ;
	}
	if (exec_builtin_cmds(cmd, mn_shell) != 0)
	{
		close_pipes(mn_shell);
		return ;
	}
	else
		mn_shell->last_exit_code = EXIT_SUCCESS;
}
