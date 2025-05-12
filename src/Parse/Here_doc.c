/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:27:45 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/12 14:15:33 by angnavar         ###   ########.fr       */
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

int	Here_doc(char *delimiter, t_shell *mn_shell)
{
    t_heredoc	hd_data;

    hd_data.size = 0;
    if (!check_here_doc_error(&hd_data, mn_shell))
        return (-1);
    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);
        hd_data.line = NULL;
        if (ft_getline(&hd_data.line, &hd_data.size, STDIN_FILENO) == -1)
            return (close(hd_data.pipe_fd[0]), close(hd_data.pipe_fd[1]), -1);
        hd_data.len = ft_strlen(hd_data.line);
        if (hd_data.line[hd_data.len - 1] == '\n')
            hd_data.line[hd_data.len - 1] = '\0';
        if (ft_strcmp(hd_data.line, delimiter) == 0)
        {
            free(hd_data.line);
            close(hd_data.pipe_fd[1]);
            return (hd_data.pipe_fd[0]);
        }
        write(hd_data.pipe_fd[1], hd_data.line, hd_data.len -1);
        write(hd_data.pipe_fd[1], "\n", 1);
        free(hd_data.line);
    }
}
