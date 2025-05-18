/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:19:04 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/18 22:31:21 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	close_pipes(t_shell *mn_shell)
{
	t_cmd	*current;

	current = mn_shell->cmds;
	while (current)
	{
		if (current->input_fd != STDIN_FILENO && current->input_fd != -1)
			close(current->input_fd);
		if (current->output_fd != STDOUT_FILENO && current->output_fd != -1)
			close(current->output_fd);
		current = current->next;
	}
}

int	create_pipes(t_shell *mn_shell)
{
	t_cmd	*current;
	int		i;
	int		pipe_fds[2];

	current = mn_shell->cmds;
	i = 0;
	while (i < mn_shell->n_cmds - 1)
	{
		if (current->output_fd == -1 && current->next->input_fd == -1)
		{
			if (pipe(pipe_fds) == -1)
				return (perr_shll(mn_shell, "pipe error", EXIT_FAILURE), 0);
			current->output_fd = pipe_fds[1];
			current->next->input_fd = pipe_fds[0];
		}
		else if (current->output_fd == -1 && current->next->input_fd != -1)
			current->output_fd = -1;
		current = current->next;
		i++;
	}
	return (1);
}

static void	set_dups_close(t_shell *mn_shell, int i)
{
	t_cmd	*current;
	int		j;
	int		fd_n;

	j = 0;
	fd_n = -1;
	current = mn_shell->cmds;
	while (j < i)
	{
		current = current->next;
		j++;
	}
	if (current->input_fd != STDIN_FILENO)
		dup2(current->input_fd, STDIN_FILENO);
	if (current->output_fd != -1 && current->output_fd != STDOUT_FILENO)
		dup2(current->output_fd, STDOUT_FILENO);
	else if (current->next && current->next->input_fd != -1)
		fd_n = ft_fd_null(mn_shell);
	close_pipes(mn_shell);
	if (fd_n != -1)
		close(fd_n);
}

void	set_childs(t_shell *mn_shell)
{
	int		i;
	t_cmd	*current;

	i = 0;
	mn_shell->childs = malloc(sizeof(pid_t) * mn_shell->n_cmds);
	if (!mn_shell->childs)
	{
		perr_shll(mn_shell, "malloc error", EXIT_FAILURE);
		return ;
	}
	current = mn_shell->cmds;
	while (i < mn_shell->n_cmds)
	{
		mn_shell->childs[i] = fork();
		if (mn_shell->childs[i] == 0)
		{
			set_dups_close(mn_shell, i);
			execute_command(current, mn_shell);
			exit(mn_shell->last_exit_code);
		}
		current = current->next;
		i++;
	}
}

void	exec_cmds(t_shell *mn_shell)
{
	int	status;
	int	i;

	if (!mn_shell || mn_shell->n_cmds == 0)
		return ;
	if (!create_pipes(mn_shell))
		return ;
	if (mn_shell->n_cmds == 1 && mn_shell->cmds->is_builtin)
	{
		execute_command(mn_shell->cmds, mn_shell);
		return ;
	}
	else
		set_childs(mn_shell);
	close_pipes(mn_shell);
	i = -1;
	while (++i < mn_shell->n_cmds)
		waitpid(mn_shell->childs[i], &status, 0);
	free(mn_shell->childs);
	if (WIFEXITED(status))
		mn_shell->last_exit_code = WEXITSTATUS(status);
	else
		mn_shell->last_exit_code = 1;
}
