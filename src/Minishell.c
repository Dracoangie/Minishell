/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:43:53 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/01 15:49:24 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
#include "libft.h"

void	Minishell(char **envp)
{
	char	*input;
	char	**args;
	t_minishell mn_shell;
	
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
		mn_shell.cmds_len = 0;
		while(args[mn_shell.cmds_len] != NULL)
			mn_shell.cmds_len++;
		free_args(args);
		args = malloc(sizeof(char *) * 6);
		args[0] = strdup("args");
		args[1] = strdup("in.txt");
		args[2] = strdup("cat");
		args[3] = strdup("cat");
		args[4] = strdup("out.txt");
		args[5] = NULL;
		mn_shell.cmds_len = 2;
		// parse the commands and execute them
		pipex(args, envp, &mn_shell, 0);
		free_all(input, args);
	}
}
