/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:38 by angnavar          #+#    #+#             */
/*   Updated: 2025/04/30 15:19:33 by angnavar         ###   ########.fr       */
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
void free_all(char *input, char **args)
{
	free_input(input);
	free_args(args);
}