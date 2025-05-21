/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:21:31 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/21 01:59:10 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	parse_redirs(t_shell *mn, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*first_cmd;

	(void)mn;
	i = 0;
	while (cmd->args[i])
	{
		if ((ft_strcmp(cmd->args[i], "<") == 0 || ft_strcmp(cmd->args[i],
					">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0
				|| ft_strcmp(cmd->args[i], "<<") == 0) && cmd->args[i + 1])
		{
			i += 2;
		}
		else if (cmd->args[i][0] != '<' && cmd->args[i][0] != '>')
		{
			break ;
		}
		else
			i++;
	}
	if (!cmd->args[i])
		return (0);
	if (i == 0)
		return (1);
	first_cmd = cmd->args[i];
	j = i;
	while (j > 0)
	{
		cmd->args[j] = cmd->args[j - 1];
		j--;
	}
	cmd->args[0] = first_cmd;
	return (1);
}