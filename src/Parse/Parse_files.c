/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:07:17 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/19 23:48:10 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	command_uses_files(const char *cmd)
{
	const char	**file_commands;
	int			i;

	file_commands = (const char *[]){"cat", NULL};
	i = 0;
	while (file_commands[i])
	{
		if (ft_strcmp(cmd, file_commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	handle_file_open(t_shell *mn_shell, char *file, int flags, int *fd)
{
	*fd = open(file, flags, 0644);
	if (*fd < 0)
	{
		if (errno == ENOENT)
			return (perr_name(mn_shell, file, "No such file or directory", 1),
				0);
		else if (errno == EACCES)
			return (perr_name(mn_shell, file, "Permission denied", 1), 0);
		else
			return (perr_name(mn_shell, file, "Failed to open file", 1), 0);
	}
	return (1);
}

static int	is_redirection_case(t_shell *mn, t_cmd *cmd, int *i)
{
	int	fd;

	if (!cmd->args[*i + 1])
		return (0);
	if (cmd->args[*i][0] == '>' && cmd->args[*i][1] == '>')
		fd = handle_file_open(mn, cmd->args[*i + 1],
				O_WRONLY | O_CREAT | O_APPEND, &cmd->output_fd);
	else if (cmd->args[*i][0] == '<' && cmd->args[*i][1] == '<')
	{
		fd = here_doc(cmd->args[*i + 1], mn);
		if (fd != -1)
			cmd->input_fd = fd;
	}
	else if (cmd->args[*i][0] == '<' && cmd->args[*i][1] == '\0')
		fd = handle_file_open(mn, cmd->args[*i + 1], O_RDONLY, &cmd->input_fd);
	else if (cmd->args[*i][0] == '>')
		fd = handle_file_open(mn, cmd->args[*i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, &cmd->output_fd);
	else
		return (0);
	if (fd == 0)
		return (-1);
	return (ft_remove_arg(cmd->args, *i), ft_remove_arg(cmd->args, *i), 1);
}

static int	handle_command_file(t_shell *mn, t_cmd *cmd, int *i)
{
	if (cmd->args[*i][0] == '-')
	{
		(*i)++;
		return (1);
	}
	if (command_uses_files(cmd->args[0]))
	{
		if (!handle_file_open(mn, cmd->args[*i], O_RDONLY, &cmd->input_fd))
			return (-1);
		(*i)++;
		return (1);
	}
	return (0);
}

int	parse_files(t_shell *mn, t_cmd *cmd, t_cmd *first)
{
	int	i;
	int	aux;

	i = 1;
	while (cmd->args[i])
	{
		aux = is_redirection_case(mn, cmd, &i);
		if (aux == -1)
			return (0);
		else if (aux == 1)
			continue ;
		aux = handle_command_file(mn, cmd, &i);
		if (aux == -1)
			return (0);
		else if (aux == 1)
			continue ;
		else
			i++;
	}
	if (cmd == first && cmd->input_fd == -1)
		cmd->input_fd = STDIN_FILENO;
	if (!cmd->next && cmd->output_fd == -1)
		cmd->output_fd = STDOUT_FILENO;
	return (1);
}
