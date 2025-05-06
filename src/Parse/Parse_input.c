/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/06 13:15:26 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"
#include "libft.h"


int	Check_exit_cmd(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		free(input);
		return (1);
	}
	return (0);
}


int	cmd_count(const char *s, char c)
{
	int	i;
	int	in_word;

	i = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			i++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (i);
}

t_cmd	*ft_split_to_cmds(char const *s, char c)
{
    t_cmd	*head = NULL; // Inicializa head a NULL
    t_cmd	*current = NULL; // Inicializa current a NULL
    t_cmd	*new_cmd;
    int		i;
    int		start;

    i = 0;
    while (s[i])
    {
        if (s[i] != c)
        {
            start = i;
            while (s[i] && s[i] != c)
                i++;
            char *cmd_str = ft_substr(s, start, i - start);
            if (!cmd_str)
                return (NULL);
            char **args = ft_split(cmd_str, ' ');
            free(cmd_str);
            new_cmd = Init_cmd(args);
            if (!new_cmd)
                return (NULL);
            if (!head)
                head = new_cmd;
            else
                current->next = new_cmd;
            current = new_cmd;
        }
        else
            i++;
    }
    return (head);
}
void Remove_arg(char **args, int index)
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

int Command_uses_files(const char *cmd)
{
    const char *file_commands[] = {"cat", "ls", "cp", "mv", NULL};
    for (int i = 0; file_commands[i]; i++)
    {
        if (ft_strcmp(cmd, file_commands[i]) == 0)
            return (1);
    }
    return (0);
}

int Parse_files(t_shell *mn_shell, t_cmd *current, 	t_cmd	*cmds)
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
		else if (current->args[i][0] == '<')
		{
			current->input_fd = open(current->args[i + 1], O_RDONLY);
			if (current->input_fd < 0)
			{
				if (errno == ENOENT)
					return (Print_error(mn_shell, "Error: File not found", 2), 0);
				else if (errno == EACCES)
					return (Print_error(mn_shell, "Error: Permission denied", 1), 0);
				else
					return (Print_error(mn_shell, "Error: Failed to open file", 1), 0);
			}
            Remove_arg(current->args, i);
			Remove_arg(current->args, i);
		}
		else if (current->args[i][0] == '>')
		{
			current->output_fd = open(current->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (current->output_fd < 0)
			{
				if (errno == ENOENT)
					return (Print_error(mn_shell, "Error: File not found", 2), 0);
				else if (errno == EACCES)
					return (Print_error(mn_shell, "Error: Permission denied", 1), 0);
				else
					return (Print_error(mn_shell, "Error: Failed to open file", 1), 0);
			}
            Remove_arg(current->args, i);
			Remove_arg(current->args, i);
		}
		else if(Command_uses_files(current->args[0]))
		{
			current->input_fd = open(current->args[i], O_RDONLY);
			if (current->input_fd < 0)
			{
				if (errno == ENOENT)
					return (Print_error(mn_shell, "Error: File not found", 2), 0);
				else if (errno == EACCES)
					return (Print_error(mn_shell, "Error: Permission denied", 1), 0);
				else
					return (Print_error(mn_shell, "Error: Failed to open file", 1), 0);
			}
		}
        i++;
    }
	if (current == cmds && current->input_fd == -1)
		current->input_fd = STDIN_FILENO;
    if (!current->next && current->output_fd == -1)
        current->output_fd = STDOUT_FILENO;
    return (1);
}

int	Builtin_cmds(char *input)
{
	if (ft_strcmp(input, "echo") == 0)
		return (1);
	else if (ft_strcmp(input, "cd") == 0)
		return (1);
	else if (ft_strcmp(input, "pwd") == 0)
		return (1);
	else if (ft_strcmp(input, "export") == 0)
		return (1);
	else if (ft_strcmp(input, "unset") == 0)
		return (1);
	else if (ft_strcmp(input, "env") == 0)
		return (1);
	return (0);
}

t_cmd	*Parse_input(char *input, t_shell *mn_shell)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = ft_split_to_cmds(input, '|');
	if (!cmds)
		return (perror("Error: Memory allocation failed"), NULL);
	else if (cmds->args[0] == NULL)
		return (Free_cmds(cmds), NULL);
	current = cmds;
	while (current)
	{
		if(Builtin_cmds(current->args[0]))
		return (printf("built-in detected"),Free_cmds(cmds), NULL);
		current->path = Check_cmd(mn_shell, current->args);
		if (!current->path)
			return (Free_cmds(cmds), NULL);
		if(Parse_files(mn_shell, current, cmds) == 0)
			return (Free_cmds(cmds), NULL);
		current = current->next;
	}
	return (cmds);
}

