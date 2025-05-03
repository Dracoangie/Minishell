/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:27:45 by tu_nombre_d       #+#    #+#             */
/*   Updated: 2025/05/03 14:48:28 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	here_doc(char *delimiter);

int	here_doc_open_files(t_shell *mn_shell, char **argv)
{
    if (mn_shell->pipex->here_doc_mode)
    {
        mn_shell->pipex->file[1] = open(argv[3 + mn_shell->pipex->cmd_len],
                O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (mn_shell->pipex->file[1] < 0)
        {
            perror(argv[2 + mn_shell->pipex->cmd_len]);
            return (0);
        }
        mn_shell->pipex->file[0] = STDIN_FILENO;
    }
    else
    {
        if (!open_files(mn_shell, argv))
            return (0);
    }
    return (1);
}

void	do_here_doc(int argc, char **argv, char **envp)
{
    t_shell mn_shell;

    mn_shell.cmds_len = 2;
    mn_shell.pipex = malloc(sizeof(t_pipex));
    if (!mn_shell.pipex)
    {
        write(2, "Error: malloc failed\n", 22);
        exit(EXIT_FAILURE);
    }
    if (argc < 6)
    {
        write(2, "Usage: ./pipex_bonus here_doc ", 30);
        write(2, "delimiter cmd1 cmd2 ... outfile\n", 32);
        free(mn_shell.pipex);
        exit(1);
    }
    here_doc(argv[2]);
    pipex(argv, envp, &mn_shell, 1);
    free(mn_shell.pipex);
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