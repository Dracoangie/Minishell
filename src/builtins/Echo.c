/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:53:07 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/14 21:58:32 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char *get_env_value(const char *name, char **envp)
{
	int len = ft_strlen(name);
	int i = 0;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char *expand_arg(const char *arg, t_shell *mn_shell)
{
	char *val;
	const char *varname;

	if (!arg)
		return (NULL);

	if (arg[0] != '$')
		return (NULL);
	if (ft_strcmp(arg, "$?") == 0)
		return (ft_itoa(mn_shell->last_exit_code));
	if (ft_strcmp(arg, "$SHLVL") == 0)
		return (ft_itoa(mn_shell->lvl));

	varname = arg + 1;
	val = get_env_value(varname, mn_shell->envp);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

void expand_args(t_cmd *cmd, t_shell *mn_shell)
{
	int i = 0;
	char *expanded;

	while (cmd->args && cmd->args[i])
	{
		expanded = expand_arg(cmd->args[i], mn_shell);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}
