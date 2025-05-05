/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:43:53 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/05 11:58:25 by angnavar         ###   ########.fr       */
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
	shell->n_cmds = 0;
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

int count_cmds(t_cmd *cmds)
{
    int count = 0;

    while (cmds)
    {
        count++;
        cmds = cmds->next;
    }
    return (count);
}

void	Minishell(char **envp)
{
	char	*input;
	t_shell *mn_shell;
	t_cmd *cmd_list;

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
		
		cmd_list = malloc(sizeof(t_cmd));
		cmd_list->args = (char *[]){"ls", "-l", NULL};
		cmd_list->path = get_cmd_path(cmd_list->args[0], envp);
		cmd_list->input_fd = STDIN_FILENO;
		cmd_list->output_fd = -1;
		cmd_list->next = malloc(sizeof(t_cmd));
		cmd_list->next->args = (char *[]){"cat", "-e", NULL};
		cmd_list->next->path = get_cmd_path(cmd_list->next->args[0], envp);
		cmd_list->next->input_fd = -1;
		cmd_list->next->output_fd = STDOUT_FILENO;
		cmd_list->next->next = NULL;
		mn_shell->cmds = cmd_list;
		mn_shell->n_cmds = 2;
		/*cmd_list = Parse_input(input, mn_shell);
		if (!cmd_list)
		{
			free(input);
			continue;
		}
		cmd_list->input_fd = "in.txt";
		cmd_list->next->output_fd = STDOUT_FILENO;
		mn_shell->cmds = cmd_list;
		mn_shell->n_cmds = count_cmds(cmd_list);
		if (mn_shell->n_cmds == 0)
		{
			free(input);
			continue;
		}*/
		pipex(mn_shell);
		free_all(input, mn_shell);
	}
	free(mn_shell);
}

//posible main function
/*
int main(int argc,char ** argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (1);
	}
	Minishell(envp);
	return 0;
}*/