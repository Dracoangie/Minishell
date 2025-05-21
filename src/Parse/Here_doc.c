/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:27:45 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/21 01:23:51 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	check_here_doc_error(t_heredoc *hd_data, t_shell *mn_shell)
{
	if (pipe(hd_data->pipe_fd) == -1)
	{
		perror("pipe error");
		mn_shell->last_exit_code = 1;
		return (0);
	}
	return (1);
}

int	read_here_doc(char *delimiter, int pipe_fd[2])
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

int	here_doc(char *delimiter, t_shell *mn_shell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	(void)mn_shell;
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	else if (pid == 0)
		read_here_doc(delimiter, pipe_fd);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
