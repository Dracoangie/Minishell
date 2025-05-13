/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:49:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/13 18:06:45 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
			free_args(current->args);
		if (current->path)
			free(current->path);
		free(current);
		current = next;
	}
}

void	free_env(char **env_copy)
{
	int	i;

	i = 0;
	if (!env_copy)
		return ;
	while (env_copy[i])
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
}

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmds)
			free_cmds(shell->cmds);
	}
}
