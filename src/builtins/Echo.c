/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:53:07 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/13 18:04:01 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	parse_echo(t_cmd *cmds, t_shell *mn_shell)
{
	if (cmds->args[1] && ft_strcmp(cmds->args[1], "-n") == 0)
		return (1);
	else if (cmds->args[1] && ft_strcmp(cmds->args[1], "$SHLVL") == 0)
		return (printf("%d\n", mn_shell->lvl), 1);
	return (0);
}
