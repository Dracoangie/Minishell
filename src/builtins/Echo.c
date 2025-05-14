/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:53:07 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/14 18:37:48 by angnavar         ###   ########.fr       */
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
			return envp[i] + len + 1;
		i++;
	}
	return NULL;
}

char *expand_arg(const char *arg, t_shell *mn_shell)
{
	char *val;
	const char *varname;

	if (!arg)
		return NULL;

	if (arg[0] != '$')
		return strdup(arg);

	if (ft_strcmp(arg, "$?") == 0)
		return ft_itoa(mn_shell->last_exit_code);

	if (ft_strcmp(arg, "$SHLVL") == 0)
		return ft_itoa(mn_shell->lvl);

	varname = arg + 1;
	val = get_env_value(varname, mn_shell->envp);
	if (val)
		return strdup(val);
	else
	{
		char *empty = malloc(1);
		if (empty)
			empty[0] = '\0';
		return empty;
	}
}

int execute_echo(t_cmd *cmds, t_shell *mn_shell)
{
	int i = 1;
	int newline = 1;

	if (cmds->args[1] && strcmp(cmds->args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (cmds->args[i])
	{
		char *expanded = expand_arg(cmds->args[i], mn_shell);
		if (expanded)
		{
			printf("%s", expanded);
			free(expanded);
		}
		if (cmds->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	mn_shell->last_exit_code = 0;
	return 1;
}
