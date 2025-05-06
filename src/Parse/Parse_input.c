/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/06 14:28:47 by angnavar         ###   ########.fr       */
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
    t_cmd	*head = NULL;
    t_cmd	*current = NULL;
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

