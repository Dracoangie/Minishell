/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:43:53 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/05 14:59:00 by angnavar         ###   ########.fr       */
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
	cmd->next = NULL;
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

void print_cmds(t_cmd *cmd_list)
{
    t_cmd *current = cmd_list;
    int i;

    while (current)
    {
        printf("Command:\n");
        i = 0;
        while (current->args && current->args[i])
        {
            printf("  Arg[%d]: %s\n", i, current->args[i]);
            i++;
        }
        printf("  Input FD: %d\n", current->input_fd);
        printf("  Output FD: %d\n", current->output_fd);
        current = current->next;
    }
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
		else if (check_exit_cmd(input))
			break ;
		else if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		int input_fd = open("in.txt", O_RDONLY);
		//int output_fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
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
		cmd_list = Parse_input(input, mn_shell);
		if (!cmd_list)
		{
			free(input);
			continue;
		}
		cmd_list->input_fd = STDIN_FILENO;
		cmd_list->next->output_fd = STDOUT_FILENO;
		mn_shell->cmds = cmd_list;
		mn_shell->n_cmds = count_cmds(cmd_list);
		print_cmds(mn_shell->cmds);
		pipex(mn_shell);
		free_all(input, mn_shell);
		close(input_fd);
		//close(output_fd);
	}
	free(mn_shell);
	clear_history();
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