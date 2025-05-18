/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:44:10 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/18 21:44:10 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	perr_shll(t_shell *shell, char *msg, int err_code)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	shell->last_exit_code = err_code;
}

void	perr_name(t_shell *shell, char *name, char *msg, int err_code)
{
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	shell->last_exit_code = err_code;
}

void	perr_exit(t_shell *shell, char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(shell->last_exit_code);
}

void	perr_mem(t_shell *mn_shell)
{
	write(2, "Error: Memory allocation failed\n", 33);
	mn_shell->last_exit_code = 1;
}

void	perr_redir(t_shell *mn_shell, char *msg)
{
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, msg, ft_strlen(msg));
	write(2, "\'\n", 2);
	mn_shell->last_exit_code = 2;
}

void	perr_export(t_shell *mn_shell, char *msg)
{
	write(2, "bash: export: `", 16);
	write(2, msg, ft_strlen(msg));
	write(2, "\': not a valid identifier\n", 27);
	mn_shell->last_exit_code = 1;
}