/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:19:04 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/05 12:46:49 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	close_pipes(t_shell *mn_shell)
{
	int	i;

	i = 0;
	while (i < mn_shell->n_cmds - 1)
	{
		close(mn_shell->pipex->pipes[i][0]);
		close(mn_shell->pipex->pipes[i][1]);
		free(mn_shell->pipex->pipes[i]);
		i++;
	}
	free(mn_shell->pipex->pipes);
}

int		create_pipes(t_shell *mn_shell)
{
	int	i;

	mn_shell->pipex->pipes = malloc(sizeof(int *) * (mn_shell->n_cmds - 1));
	if (!mn_shell->pipex->pipes)
	{
		perror("malloc error");
		mn_shell->last_exit_code = EXIT_FAILURE;
		return (0);
	}
	i = 0;
	while (i < mn_shell->n_cmds - 1)
	{
		mn_shell->pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!mn_shell->pipex->pipes[i] || pipe(mn_shell->pipex->pipes[i]) == -1)
		{
			perror("pipe error");
			mn_shell->last_exit_code = EXIT_FAILURE;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	set_dups_close(t_shell *mn_shell, int i)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		dup2(mn_shell->cmds->input_fd, STDIN_FILENO);
		dup2(mn_shell->pipex->pipes[i][1], STDOUT_FILENO);
	}
	else if (i == mn_shell->n_cmds - 1)
	{
		dup2(mn_shell->pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(mn_shell->cmds->next->output_fd, STDOUT_FILENO);
	}
	else
	{
		dup2(mn_shell->pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(mn_shell->pipex->pipes[i][1], STDOUT_FILENO);
	}
	while (j < mn_shell->n_cmds - 1)
	{
		close(mn_shell->pipex->pipes[j][0]);
		close(mn_shell->pipex->pipes[j][1]);
		j++;
	}
}

void	set_childs(t_shell *mn_shell)
{
	int	i;
	t_cmd *current;

	i = 0;
	mn_shell->pipex->childs = malloc(sizeof(pid_t) * mn_shell->n_cmds);
	if (!mn_shell->pipex->childs)
	{
		print_error(mn_shell, "malloc error", EXIT_FAILURE);
		return;
	}
	current = mn_shell->cmds;
	while (i < mn_shell->n_cmds)
	{
		mn_shell->pipex->childs[i] = fork();
		if (mn_shell->pipex->childs[i] == 0)
		{
			set_dups_close(mn_shell, i);
			execute_command(current->args[0], mn_shell->envp, mn_shell);
			exit(EXIT_SUCCESS);
		}
		current = current->next;
		i++;
	}
}

void	pipex(t_shell *mn_shell)
{
	int	status;
	int	i;
	int saved_stdin = dup(STDIN_FILENO);

	mn_shell->pipex = malloc(sizeof(t_pipex));
	if (!mn_shell->pipex)
	{
		print_error(mn_shell, "malloc error", EXIT_FAILURE);
		return;
	}
	/*if (!open_files(mn_shell))
	{
		free(mn_shell->pipex);
		mn_shell->pipex = NULL;
		return;
	}*/
	if (!create_pipes(mn_shell))
	{
		free(mn_shell->pipex);
		mn_shell->pipex = NULL;
		return;
	}
	dup2(mn_shell->cmds->input_fd, STDIN_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	set_childs(mn_shell);
	close_pipes(mn_shell);
	if (mn_shell->cmds->input_fd != STDIN_FILENO)
		close(mn_shell->cmds->input_fd);
	if (mn_shell->cmds->next->output_fd != STDOUT_FILENO)
		close(mn_shell->cmds->next->output_fd);
	i = 0;
	while (i < mn_shell->n_cmds)
	{
		waitpid(mn_shell->pipex->childs[i], &status, 0);
		i++;
	}
	free(mn_shell->pipex->childs);
	if (WIFEXITED(status))
		mn_shell->last_exit_code = WEXITSTATUS(status);
	else
		mn_shell->last_exit_code = 1;
	free(mn_shell->pipex);
	mn_shell->pipex = NULL;
}
