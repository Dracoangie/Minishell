/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:43:53 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/21 04:04:45 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

static int	minishell_loop(t_shell *mn_shell)
{
	char	*input;

	input = readline("Minishell> ");
	if (!input)
		return (1);
	if (input[0] == '\0')
		return (free(input), 0);
	add_history(input);
	mn_shell->cmds = parse_input(input, mn_shell);
	if (!mn_shell->cmds)
		return (free(input), 0);
	if (execute_exit(mn_shell->cmds, mn_shell) != 0)
		return (mn_shell->last_exit_code);
	mn_shell->n_cmds = count_cmds(mn_shell->cmds);
	exec_cmds(mn_shell);
	free_all(input, mn_shell);
	return (0);
}

int	minishell(char **envp)
{
	t_shell	*mn_shell;
	int		exit_code;

	mn_shell = init_shell(envp);
	if (!mn_shell)
		return (1);
	while (1)
	{
		if (minishell_loop(mn_shell))
			break ;
	}
	exit_code = mn_shell->last_exit_code;
	free_env(mn_shell->envp);
	free(mn_shell);
	rl_clear_history();
	return (exit_code);
}

//ft_print_cmds(mn_shell->cmds);
//posible main function
/*
int	main(int argc,char ** argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (1);
	}
	Minishell(envp);
	return (0);
}*/

// como se crear comandos
/*cmd_list = malloc(sizeof(t_cmd));
cmd_list->args = (char *[]){"echo", "hola", NULL};
cmd_list->path = get_cmd_path(cmd_list->args[0], envp);
cmd_list->input_fd = STDIN_FILENO;
cmd_list->output_fd = STDOUT_FILENO;
cmd_list->next = NULL;
cmd_list->next = malloc(sizeof(t_cmd));
cmd_list->next->args = (char *[]){"cat", NULL};
cmd_list->next->path = get_cmd_path(cmd_list->next->args[0], envp);
cmd_list->next->input_fd = input_fd;
cmd_list->next->output_fd = -1;
cmd_list->next->next = malloc(sizeof(t_cmd));
cmd_list->next->next->args = (char *[]){"cat", "-e", NULL};
cmd_list->next->next->path = get_cmd_path(cmd_list->next->next->args[0], envp);
cmd_list->next->next->input_fd = -1;
cmd_list->next->next->output_fd = STDOUT_FILENO;
cmd_list->next->next->next = NULL;*/