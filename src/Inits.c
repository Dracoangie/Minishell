/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:26:05 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/13 18:01:58 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	**init_env(char **env)
{
	int		count;
	int		i;
	char	**env_copy;

	count = 0;
	i = -1;
	while (env[count])
		count++;
	env_copy = malloc((count + 1) * sizeof(char *));
	while (++i < count)
		env_copy[i] = strdup(env[i]);
	env_copy[count] = NULL;
	return (env_copy);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cmds = NULL;
	shell->n_cmds = 0;
	shell->last_exit_code = 0;
	shell->envp = init_env(envp);
	shell->lvl = 0;
	return (shell);
}

t_cmd	*init_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->path = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->next = NULL;
	return (cmd);
}
