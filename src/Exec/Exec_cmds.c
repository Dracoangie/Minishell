/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:19:04 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/07 11:37:43 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	Close_pipes(t_shell *mn_shell)
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

int create_pipes(t_shell *mn_shell)
{
    t_cmd *current;
    int i;

    current = mn_shell->cmds;
    i = 0;
    while (i < mn_shell->n_cmds - 1)
    {
        if (current->output_fd == -1 && current->next->input_fd == -1)
        {
            int pipe_fds[2];
            if (pipe(pipe_fds) == -1)
                return (Perr_shll (mn_shell, "pipe error", EXIT_FAILURE), 0);
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

int fd_null(t_shell *mn_shell)
{
	int fd_null;

	fd_null = open("/dev/null", O_WRONLY);
	if (fd_null < 0)
	{
		perror("/dev/null");
		mn_shell->last_exit_code = EXIT_FAILURE;
		return (-1);
	}
	dup2(fd_null, STDOUT_FILENO);
	return (fd_null);
}

static void set_dups_close(t_shell *mn_shell, int i)
{
    t_cmd *current;
    int j;
    int fd_n = -1;

    current = mn_shell->cmds;
    for (j = 0; j < i; j++)
        current = current->next;
    if (current->input_fd != STDIN_FILENO)
        dup2(current->input_fd, STDIN_FILENO);
    if (current->output_fd != -1 && current->output_fd != STDOUT_FILENO)
        dup2(current->output_fd, STDOUT_FILENO);
    else if (current->next && current->next->input_fd != -1)
        fd_n = fd_null(mn_shell);
    Close_pipes(mn_shell);
    if (fd_n != -1)
        close(fd_n);
}

void	set_childs(t_shell *mn_shell)
{
	int	i;
	t_cmd *current;

	i = 0;
	mn_shell->childs = malloc(sizeof(pid_t) * mn_shell->n_cmds);
	if (!mn_shell->childs)
	{
		Perr_shll(mn_shell, "malloc error", EXIT_FAILURE);
		return;
	}
	current = mn_shell->cmds;
	while (i < mn_shell->n_cmds)
	{
		mn_shell->childs[i] = fork();
		if (mn_shell->childs[i] == 0)
		{
			set_dups_close(mn_shell, i);
			Execute_command(current, mn_shell);
			exit(EXIT_SUCCESS);
		}
		current = current->next;
		i++;
	}
}

void Exec_cmds(t_shell *mn_shell)
{
    int status;
    int i;

	if (!mn_shell || mn_shell->n_cmds == 0)
		return;
    if (!create_pipes(mn_shell))
        return;
    set_childs(mn_shell);
    Close_pipes(mn_shell);
    i = -1;
    while (++i < mn_shell->n_cmds)
        waitpid(mn_shell->childs[i], &status, 0);
    free(mn_shell->childs);
    if (WIFEXITED(status))
        mn_shell->last_exit_code = WEXITSTATUS(status);
    else
        mn_shell->last_exit_code = 1;
}
