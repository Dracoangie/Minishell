/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:43:53 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/01 14:35:06 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
#include "libft.h"

void	Minishell(void)
{
	char	*input;
	char	**args;
	
	while (1)
	{
		input = readline("Minishell> ");
		if (!input)
			break ;
		if (check_exit_command(input))
			break ;
		add_history(input);
		args = Parse_input(input);
		if (!args)
		{
			free_input(input);
			continue ;
		}
		// parse the commands and execute them
		free_all(input, args);
	}
}
