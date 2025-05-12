/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_to_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:08:03 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/12 14:35:13 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


t_cmd	*ft_split_to_cmds(char const *s, char c, t_shell *mn_shell)
{
    t_cmd	*head = NULL;
    t_cmd	*current = NULL;
    t_cmd	*new_cmd;
    int		i;
    int		start;
    char	quote = '\0';

    i = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
        {
            if (quote == '\0')
                quote = s[i];
            else if (quote == s[i])
                quote = '\0';
        }
        if (s[i] != c || quote != '\0')
        {
            start = i;
            while (s[i] && (s[i] != c || quote != '\0'))
            {
                if (s[i] == '\'' || s[i] == '"')
                {
                    if (quote == '\0')
                        quote = s[i];
                    else if (quote == s[i])
                        quote = '\0';
                }
                i++;
            }
            char *cmd_str = ft_substr(s, start, i - start);
            if (!cmd_str)
                return (Perr_mem(mn_shell), NULL);
            char **args = ft_split_with_quotes(cmd_str, ' ');
            free(cmd_str);
            new_cmd = Init_cmd(args);
            if (!new_cmd)
				return (Perr_mem(mn_shell), NULL);
            if (!head)
                head = new_cmd;
            else
                current->next = new_cmd;
            current = new_cmd;
        }
        else
            i++;
    }
	if (quote != '\0')
        return (Free_cmds(head), Perr_shll (mn_shell,"Error: Unmatched quotes in input", 1), NULL);
    return (head);
}

t_cmd	*Parse_to_cmds(char const *s, char c, t_shell *mn_shell)
{
    t_cmd	*cmds = NULL;

	cmds = ft_split_to_cmds(s, c, mn_shell);

	return (cmds);
}