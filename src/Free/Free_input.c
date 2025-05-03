/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:38 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/03 14:45:11 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"

int free_input(char *input)
{
	if (input)
		return (free(input), 1);
	return (0);
}
int free_args(char **args)
{
	int i;

	if (args)
	{
		i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		return (free(args), 1);
	}
	return (0);
}

void free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmds)
			free(shell->cmds);
		if (shell->pipex)
			free(shell->pipex);
	}
}

void free_all(char *input, char **args, t_shell *shell)
{
	free_input(input);
	free_args(args);
	free_shell(shell);
}