/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:38 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/06 13:15:09 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"

int Free_input(char *input)
{
	if (input)
		return (free(input), 1);
	return (0);
}

int	Free_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (1);
}

int	Free_strn(char **str, int j)
{
	if (!str[j])
	{
		while (j > 0)
			free(str[--j]);
		free(str);
		return (1);
	}
	return (0);
}

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
		if (shell->pipex)
			free(shell->pipex);
	}
}

void Free_all(char *input, t_shell *shell)
{
	Free_input(input);
	Free_shell(shell);
}