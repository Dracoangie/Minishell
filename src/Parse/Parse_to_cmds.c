/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_to_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:08:03 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/13 14:26:43 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


t_cmd	*ft_split_to_cmds(char const *s, char c, t_shell *mn_shell)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	t_cmd	*new_cmd;
	int		i = 0;
	int		start;
	char	quote = '\0';

	while (s[i])
	{
		while (s[i] == c && quote == '\0')
			i++;
		if (!s[i])
			break;

		start = i;
		while (s[i])
		{
			if ((s[i] == '\'' || s[i] == '"'))
			{
				if (quote == '\0')
					quote = s[i];
				else if (quote == s[i])
					quote = '\0';
			}
			else if (quote == '\0' && s[i] == c)
				break;
			i++;
		}
		if (quote != '\0')
			return (Perr_shll(mn_shell, "Error: quote not closed", 1), Free_cmds(head), NULL);
		char *cmd_str = ft_substr(s, start, i - start);
		if (!cmd_str)
			return (Perr_mem(mn_shell), Free_cmds(head), NULL);
		char **args = ft_split_with_quotes(cmd_str, ' ');
		free(cmd_str);
		if (!args)
			return (Perr_shll(mn_shell, "Error: quote not closed", 1), Free_cmds(head), NULL);
		new_cmd = Init_cmd(args);
		if (!new_cmd)
			return (Perr_mem(mn_shell), Free_cmds(head), NULL);
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
	}
	return (head);
}



t_cmd	*Parse_to_cmds(char const *s, char c, t_shell *mn_shell)
{
    t_cmd	*cmds = NULL;

	cmds = ft_split_to_cmds(s, c, mn_shell);

	return (cmds);
}