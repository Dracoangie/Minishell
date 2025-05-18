/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:42 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/16 22:40:41 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

void	ft_print_cmds(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		i;

	current = cmd_list;
	while (current)
	{
		printf("Command:\n");
		i = 0;
		while (current->args && current->args[i])
		{
			printf("  Arg[%d]: %s\n", i, current->args[i]);
			i++;
		}
		printf("  Input FD: %d\n", current->input_fd);
		printf("  Output FD: %d\n", current->output_fd);
		current = current->next;
	}
}

char	*ft_remove_quotes(const char *str)
{
	int		i = 0;
	int		j = 0;
	char	quote = '\0';
	char	*new_str = malloc(strlen(str) + 1);

	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == '\0')
		{
			quote = str[i];
			i++;
			continue;
		}
		if (str[i] == quote)
		{
			quote = '\0';
			i++;
			continue;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	ft_fd_null(t_shell *mn_shell)
{
	int	fd_null;

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

int	ft_first_cmd(t_cmd *cmds, t_cmd *current)
{
	if (cmds == current)
		return (1);
	return (0);
}