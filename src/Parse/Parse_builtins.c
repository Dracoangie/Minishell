/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:08:20 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/21 02:17:38 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	exec_builtin_cmds(t_cmd *cmds, t_shell *mn_shell)
{
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (mn_shell->last_exit_code = execute_cd(mn_shell, cmds->args)
			, mn_shell->last_exit_code);
	else if (ft_strcmp(cmds->args[0], "export") == 0)
		return (mn_shell->last_exit_code = execute_export(mn_shell, cmds->args)
			, mn_shell->last_exit_code);
	else if (ft_strcmp(cmds->args[0], "unset") == 0)
		return (execute_unset(mn_shell, cmds), 0);
	return (0);
}

int	parse_builtins(t_cmd *cmds)
{
	if (ft_strcmp(cmds->args[0], "cd") == 0
		|| ft_strcmp(cmds->args[0], "exit") == 0
		|| ft_strcmp(cmds->args[0], "export") == 0
		|| ft_strcmp(cmds->args[0], "unset") == 0)
		return (1);
	return (0);
}
