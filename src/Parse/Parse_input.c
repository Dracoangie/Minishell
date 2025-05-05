/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/05 14:58:28 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"
#include "libft.h"


int	check_exit_cmd(char *input)
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
            new_cmd = init_cmd(args);
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

t_cmd	*Parse_input(char *input, t_shell *mn_shell)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = ft_split_to_cmds(input, '|');
	if (!cmds)
	{
		perror("Error: Memory allocation failed");
		return (NULL);
	}
	else if (cmds->args[0] == NULL)
	{
		free(cmds);
		return (NULL);
	}
	current = cmds;
	while (current)
	{
		current->path = get_cmd_path(current->args[0], mn_shell->envp);
		if (!current->path || access(current->path, X_OK) != 0)
		{
			write(2, current->args[0], ft_strlen(current->args[0]));
			print_error(mn_shell, ": command not found", 127);
			free(current->args);
			free(current);
			return (NULL);
		}
		current = current->next;
	}
	return (cmds);
}

