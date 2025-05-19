/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:26:05 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/19 14:05:57 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*update_shlvl(const char *env_var)
{
	int		lvl;
	char	*new_lvl;
	char	*shlvl;

	lvl = ft_atoi(env_var + 6);
	new_lvl = ft_itoa(lvl + 1);
	if (!new_lvl)
		return (NULL);
	shlvl = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	return (shlvl);
}

char	**init_env(char **env)
{
	int		count;
	int		i;
	char	**env_copy;

	count = 0;
	while (env[count])
		count++;
	env_copy = malloc((count + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			env_copy[i] = update_shlvl(env[i]);
		else
			env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
			return (NULL);
	}
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
