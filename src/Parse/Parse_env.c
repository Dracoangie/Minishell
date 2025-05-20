/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:34:49 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/20 00:11:54 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*expand_args(const char *arg, t_shell *mn_shell)
{
	char		*val;
	const char	*varname;

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

int	lit_seg(const char *str, int i, char quote, char **result)
{
	int		start;
	char	*tmp;
	char	*tmp2;

	start = i;
	while (str[i] && ((quote == '\'' && str[i] != '\'') || (quote == '"'
				&& str[i] != '$' && str[i] != '"') || (quote == '\0'
				&& str[i] != '$' && str[i] != '\'' && str[i] != '"')))
		i++;
	if (i > start)
	{
		tmp = ft_substr(str, start, i - start);
		if (!tmp)
			return (i);
		tmp2 = *result;
		*result = ft_strjoin(*result, tmp);
		free(tmp2);
		free(tmp);
	}
	return (i);
}

char	*get_expand_arg(const char *str, t_shell *mn_shell)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = '\0';
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
			i = handle_quotes(str, i, &quote, &result);
		else if (str[i] == '$' && quote != '\'')
			i = handle_expnd(str, i, mn_shell, &result);
		else
			i = lit_seg(str, i, quote, &result);
	}
	return (result);
}

void	parse_env(t_cmd *cmd, t_shell *mn_shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '$'))
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
	cmd->is_builtin = parse_builtins(cmd);
}
