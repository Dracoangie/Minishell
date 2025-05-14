/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:34:49 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/15 01:13:54 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char *expand_args(const char *arg, t_shell *mn_shell)
{
	char *val;
	const char *varname;

	if (!arg)
		return (NULL);
	if (arg[0] != '$')
		return (NULL);
	if (arg[1] == '\0')
		return (ft_strdup("$"));
	if (arg[1] == '$')
		return (ft_itoa(getpid()));
	if (ft_strcmp(arg, "$?") == 0)
		return (ft_itoa(mn_shell->last_exit_code));
	varname = arg + 1;
	val = get_env_value(varname, mn_shell->envp);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

char *get_expand_arg(const char *str, t_shell *mn_shell)
{
	int i = 0;
	int start = 0;
	char *result = ft_strdup("");
	char *expanded = NULL;
	char quote = '\0';

	while (str[i])
	{
		start = i;
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = '\0';
			i++;
			continue;
		}
		if (str[i] == '$' && quote != '\'')
		{
			start = i;
			if ((str[i + 1] == '\'' || str[i + 1] == '"') && quote != '"')
			{
				i++;
				continue;
			}
			else if (str[i + 1] == '?')
				i += 2;
			else if (str[i + 1] != '$')
			{
				i++;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
			}
			else
				i += 2;
			char *tmp = ft_substr(str, start, i - start);
			expanded = expand_args(tmp, mn_shell);
			free(tmp);
			tmp = result;
			result = ft_strjoin(result, expanded);
			free(tmp);
			free(expanded);
		}
		else
			i++;
	}
	return result;
}

void	parse_env(t_cmd *cmd, t_shell *mn_shell)
{
	int i = 0;
	char *expanded;

	while (cmd->args[i])
	{
		if(ft_strchr(cmd->args[i], '$'))
		{
			expanded = get_expand_arg(cmd->args[i], mn_shell);
			if (expanded)
			{
				free(cmd->args[i]);
				cmd->args[i] = expanded;
			}
		}
		i++;
	}
	parse_quotes(cmd);
}
