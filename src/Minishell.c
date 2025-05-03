/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:43:53 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/03 15:26:33 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_shell *init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cmds = NULL;
	shell->cmds_len = 0;
	shell->last_exit_code = 0;
	shell->envp = envp;
	shell->pipex = NULL	;
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
	return (cmd);
}

void	Minishell(char **envp)
{
	char	*input;
	char	**args;
	t_shell *mn_shell;

	mn_shell = init_shell(envp);
	if (!mn_shell)
		return;
	while (1)
	{
		input = readline("Minishell> ");
		if (!input)
		{
			print_error(mn_shell, "readline error", 1);
			break ;
		}
		if (check_exit_cmd(input))
			break ;
		add_history(input);
		args = Parse_input(input);
		if (!args)
		{
			free_input(input);
			continue ;
		}
		mn_shell->cmds_len = 0;
		while(args[mn_shell->cmds_len] != NULL)
			mn_shell->cmds_len++;
		free_args(args);
		args = malloc(sizeof(char *) * 6);
		args[0] = strdup("args");
		args[1] = strdup("in.txt");
		args[2] = strdup("cat");
		args[3] = strdup("cat");
		args[4] = strdup("out.txt");
		args[5] = NULL;
		mn_shell->cmds_len = 2;
		pipex(args, envp, mn_shell, 0);
		free_all(input, args, mn_shell);
	}
	free(mn_shell);
}
/*
	// Initialize the shell
	t_shell *shell = init_shell(argc, argv, envp);
	if (!shell)
		return (1);

	// Main loop
	while (1)
	{
		// Display prompt and read input
		char *input = read_input(shell);
		if (!input)
			break;

		// Parse the input into commands
		t_cmd *commands = parse_input(input);
		free(input);

		if (!commands)
			continue;

		// Execute the commands
		execute_commands(shell, commands);

		// Free the command list
		free_commands(commands);
	}

	free_shell(shell);
	return (0);*/