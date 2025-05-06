/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:49:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/06 13:49:49 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	Free_cmds(t_cmd *cmds)
{
    t_cmd	*current;
    t_cmd	*next;

    current = cmds;
    while (current)
    {
        next = current->next;
		if(	current->args)
			Free_args(current->args);
        if (current->path)
            free(current->path);
        free(current);
		current = next;
    }
}

void Free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmds)
			Free_cmds(shell->cmds);
	}
}