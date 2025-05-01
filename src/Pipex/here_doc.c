/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:17:54 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/01 14:45:33 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	here_doc_open_files(t_pipex *pipex, char **argv)
{
	if (pipex->here_doc_mode)
	{
		pipex->file[1] = open(argv[3 + pipex->cmd_len],
				O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (pipex->file[1] < 0)
		{
			perror(argv[2 + pipex->cmd_len]);
			exit(EXIT_FAILURE);
		}
		pipex->file[0] = STDIN_FILENO;
	}
	else
		open_files(pipex, argv);
}

void	do_here_doc(int argc, char **argv, char **envp)
{
	if (argc < 6)
	{
		write(2, "Usage: ./pipex_bonus here_doc ", 30);
		write(2, "delimiter cmd1 cmd2 ... outfile\n", 32);
		exit(1);
	}
	here_doc(argv[2]);
	pipex(argv, envp, argc - 4, 1);
}

void	check_here_doc_error(t_heredoc *hd_data)
{
	if (pipe(hd_data->pipe_fd) == -1)
	{
		perror("pipe error");
		exit(1);
	}
}

void	here_doc(char *delimiter)
{
	t_heredoc	hd_data;

	hd_data.size = 0;
	check_here_doc_error(&hd_data);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		hd_data.line = NULL;
		if (ft_getline(&hd_data.line, &hd_data.size, STDIN_FILENO) == -1)
			break ;
		hd_data.len = ft_strlen(hd_data.line);
		if (hd_data.line[hd_data.len - 1] == '\n')
			hd_data.line[hd_data.len - 1] = '\0';
		if (ft_strcmp(hd_data.line, delimiter) == 0)
		{
			free(hd_data.line);
			break ;
		}
		write(hd_data.pipe_fd[1], hd_data.line, hd_data.len - 1);
		write(hd_data.pipe_fd[1], "\n", 1);
		free(hd_data.line);
	}
	close(hd_data.pipe_fd[1]);
	dup2(hd_data.pipe_fd[0], STDIN_FILENO);
	close(hd_data.pipe_fd[0]);
}
