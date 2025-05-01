/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:42 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/01 15:58:47 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/*void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}*/

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	resize_line_buffer(char **line, size_t *len, int pos)
{
	char	*new_line;

	if (pos + 1 >= (int)*len)
	{
		*len *= 2;
		new_line = realloc(*line, *len);
		if (!new_line)
			return (-1);
		*line = new_line;
	}
	return (0);
}

int	ft_getline(char **line, size_t *len, int fd)
{
	char	buffer[1];
	int		pos;

	pos = 0;
	if (!line || !len || fd < 0)
		return (-1);
	if (*line == NULL || *len == 0)
	{
		*len = 128;
		*line = malloc(*len);
		if (!*line)
			return (-1);
	}
	while (read(fd, buffer, 1) > 0)
	{
		if (resize_line_buffer(line, len, pos) == -1)
			return (-1);
		(*line)[pos++] = buffer[0];
		if (buffer[0] == '\n')
			break ;
	}
	if (pos == 0)
		return (-1);
	(*line)[pos] = '\0';
	return (pos);
}

void	open_files(t_pipex *pipex, char **argv)
{
	if (!pipex->here_doc_mode)
	{
		pipex->file[0] = open(argv[1], O_RDONLY);
		if (pipex->file[0] < 0)
		{
			perror(argv[1]);
			pipex->file[0] = open("/dev/null", O_RDONLY);
			if (pipex->file[0] < 0)
				exit(1);
		}
		pipex->file[1] = open(argv[2 + pipex->cmd_len],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		pipex->file[0] = STDIN_FILENO;
		pipex->file[1] = open(argv[2 + pipex->cmd_len],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (pipex->file[1] < 0)
	{
		perror(argv[2 + pipex->cmd_len]);
		exit(1);
	}
}
