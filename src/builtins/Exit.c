/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:12:48 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/20 01:03:44 by angnavar         ###   ########.fr       */
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

int	check_exit_argument(t_shell *mn_shell, char *arg, int *out_code)
{
	int	i;
	int	minus;

	i = 0;
	minus = 0;
	if (!arg)
		return (mn_shell->last_exit_code);
	if (arg[i] == '+')
		i++;
	else if (arg[i] == '-')
	{
		minus = 1;
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			exit_free(mn_shell, 2, 1);
		i++;
	}
	*out_code = ft_atoi(arg);
	if (minus)
		*out_code = 156;
	return (0);
}

int	execute_exit(t_cmd *cmds, t_shell *mn_shell)
{
	int	exit_status;

	exit_status = 0;
	if (cmds->next || !check_exit_cmd(cmds->args[0]))
		return (0);
	ft_putendl_fd("exit", 1);
	if (cmds->args[1])
	{
		check_exit_argument(mn_shell, cmds->args[1], &exit_status);
		if (cmds->args[2])
			return (perr_name(mn_shell, "exit", "too many arguments", 1), 1);
	}
	else
		exit_status = mn_shell->last_exit_code;
	exit_free(mn_shell, exit_status, 0);
	exit(exit_status);
}
