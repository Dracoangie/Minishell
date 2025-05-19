/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:12:48 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/19 15:38:56 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	check_exit_cmd(char *input)
{
	if (ft_strcmp(input, "exit") == 0)
		return (1);
	return (0);
}

void	exit_free(t_shell *mn_shell, int exit_status, int printerror)
{
	if (printerror)
		perr_name(mn_shell, "exit", "numeric argument required", 2);
	free_all(NULL, mn_shell);
	free_env(mn_shell->envp);
	free(mn_shell);
	exit(exit_status);
}

int	execute_exit(t_cmd *cmds, t_shell *mn_shell)
{
	int	exit_status;
	int	i;

	i = 0;
	if (cmds->next || !check_exit_cmd(cmds->args[0]))
		return (0);
	ft_putendl_fd("exit", 1);
	if (cmds->args[1])
	{
		while (cmds->args[1][i])
		{
			if (!ft_isdigit(cmds->args[1][i]))
				exit_free(mn_shell, 2, 1);
			i++;
		}
		if (cmds->args[2])
			return (perr_name(mn_shell, "exit", "too many arguments", 1), 1);
		exit_status = ft_atoi(cmds->args[1]);
	}
	else
		exit_status = mn_shell->last_exit_code;
	exit_free(mn_shell, exit_status, 0);
	exit(exit_status);
}
