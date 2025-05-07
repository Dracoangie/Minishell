/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:07:17 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/07 20:42:51 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int Command_uses_files(const char *cmd)
{
    const char *file_commands[] = {"cat", NULL};
    for (int i = 0; file_commands[i]; i++)
    {
        if (ft_strcmp(cmd, file_commands[i]) == 0)
            return (1);
    }
    return (0);
}

int handle_file_open(t_shell *mn_shell, char *file, int flags, int *fd)
{
    *fd = open(file, flags, 0644);
    if (*fd < 0)
    {
        if (errno == ENOENT)
            return (Perr_shll(mn_shell, "Error: File not found", 2), 0);
        else if (errno == EACCES)
            return (Perr_shll(mn_shell, "Error: Permission denied", 1), 0);
        else
            return (Perr_shll(mn_shell, "Error: Failed to open file", 1), 0);
    }
    return (1);
}

int Parse_files(t_shell *mn_shell, t_cmd *current, t_cmd *cmds)
{
    int i;

    i = 1;
    while (current->args[i])
    {
        if (current->args[i][0] == '-')
        {
            i++;
            continue;
        }
        else if (current->args[i][0] == '<' && current->args[i][1] == '\0')
        {
			if (current->input_fd != -1 && current->input_fd != STDIN_FILENO)
                close(current->input_fd);
            if (!handle_file_open(mn_shell, current->args[i + 1], O_RDONLY, &current->input_fd))
                return (0);
			ft_remove_arg(current->args, i);
			ft_remove_arg(current->args, i);
        }
        else if (current->args[i][0] == '>')
        {
			if (current->output_fd != -1 && current->output_fd != STDOUT_FILENO)
				close(current->output_fd);
            if (!handle_file_open(mn_shell, current->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, &current->output_fd))
                return (0);
			ft_remove_arg(current->args, i);
			ft_remove_arg(current->args, i);
        }
        else if (Command_uses_files(current->args[0]))
        {
            if (!handle_file_open(mn_shell, current->args[i], O_RDONLY, &current->input_fd))
                return (0);
        }
        else
            i++;
    }
    if (current == cmds && current->input_fd == -1)
        current->input_fd = STDIN_FILENO;
    if (!current->next && current->output_fd == -1)
        current->output_fd = STDOUT_FILENO;
    return (1);
}
