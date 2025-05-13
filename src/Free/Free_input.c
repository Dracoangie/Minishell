/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:38 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/13 18:06:06 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	free_input(char *input)
{
	if (input)
		return (free(input), 1);
	return (0);
}

int	free_args(char **args)
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

int	free_strn(char **str, int j)
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

void	free_all(char *input, t_shell *shell)
{
	free_input(input);
	free_shell(shell);
}
