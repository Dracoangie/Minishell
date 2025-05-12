/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:42 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/12 14:41:11 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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


void ft_remove_arg(char **args, int index)
{
    int i;

    free(args[index]);
    i = index;
    while (args[i])
    {
        args[i] = args[i + 1];
        i++;
    }
}

int		ft_argstr(const char **args, const char *str)
{
    int i;

    if (!args || !str)
        return (-1);
    i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], str) == 0)
            return (i);
        i++;
    }
    return (-1);
}
