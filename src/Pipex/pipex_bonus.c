/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:19:04 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/05 14:21:51 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	close_pipes(t_shell *mn_shell)
{
    t_cmd	*current;

    current = mn_shell->cmds;
    while (current)
    {
        // Cierra input_fd si no es el descriptor estándar
        if (current->input_fd != STDIN_FILENO && current->input_fd != -1)
            close(current->input_fd);

        // Cierra output_fd si no es el descriptor estándar
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
        // Solo crea un pipe si no hay redirecciones configuradas
        if (current->output_fd == -1 && current->next->input_fd == -1)
        {
            int pipe_fds[2];
            if (pipe(pipe_fds) == -1)
            {
                perror("pipe error");
                mn_shell->last_exit_code = EXIT_FAILURE;
                return (0);
            }
            current->output_fd = pipe_fds[1]; // Escribe en el pipe
            current->next->input_fd = pipe_fds[0]; // Lee del pipe
        }
		else if (current->output_fd == -1 && current->next->input_fd != -1)
        {
            // Si el siguiente comando ya tiene un input_fd, no redirijas al stdout
            current->output_fd = -1;
        }
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
	int fd_n;

    current = mn_shell->cmds;
    for (j = 0; j < i; j++)
        current = current->next;

    if (current->input_fd != STDIN_FILENO)
        dup2(current->input_fd, STDIN_FILENO);
    if (current->output_fd != -1 && current->output_fd != STDOUT_FILENO)
        dup2(current->output_fd, STDOUT_FILENO);
    else if (current->next && current->next->input_fd != -1)
        fd_n = fd_null(mn_shell);
    current = mn_shell->cmds;
    while (current)
    {
        if (current->input_fd != STDIN_FILENO)
            close(current->input_fd);
        if (current->output_fd != STDOUT_FILENO && current->output_fd != -1)
            close(current->output_fd);
		current = current->next;
    }
	if(fd_n)
		close(fd_n);
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
			execute_command(current, mn_shell);
			exit(EXIT_SUCCESS);
		}
		current = current->next;
		i++;
	}
}

void pipex(t_shell *mn_shell)
{
    int status;
    int i;
    t_cmd *current;

    mn_shell->pipex = malloc(sizeof(t_pipex));
    if (!mn_shell->pipex)
    {
        print_error(mn_shell, "malloc error", EXIT_FAILURE);
        return;
    }

    if (!create_pipes(mn_shell))
    {
        free(mn_shell->pipex);
        mn_shell->pipex = NULL;
        return;
    }

    set_childs(mn_shell);
    current = mn_shell->cmds;
    while (current)
    {
        if (current->input_fd != STDIN_FILENO)
            close(current->input_fd);
        if (current->output_fd != STDOUT_FILENO)
            close(current->output_fd);
        current = current->next;
    }

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
