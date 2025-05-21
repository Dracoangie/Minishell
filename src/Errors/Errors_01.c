/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:44:10 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/18 21:44:10 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	perr_export(t_shell *mn_shell, char *msg)
{
	write(2, "bash: export: `", 16);
	write(2, msg, ft_strlen(msg));
	write(2, "\': not a valid identifier\n", 27);
	mn_shell->last_exit_code = 1;
}

void	perr_cd(t_shell *mn_shell, char *msg)
{
	write(2, "bash: cd: ", 10);
	write(2, msg, ft_strlen(msg));
	write(2, ": No such file or directory\n", 29);
	mn_shell->last_exit_code = 1;
}
