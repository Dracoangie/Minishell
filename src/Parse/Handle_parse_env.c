/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_parse_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 00:02:36 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/20 22:50:14 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	handle_quotes(const char *str, int i, char *quote, char **result)
{
	char	*tmp;
	char	*tmp2;

	if (!*quote)
		*quote = str[i];
	else if (*quote == str[i])
		*quote = '\0';
	tmp = ft_substr(str, i, 1);
	if (!tmp)
		return (i + 1);
	tmp2 = *result;
	*result = ft_strjoin(*result, tmp);
	free(tmp2);
	free(tmp);
	return (i + 1);
}

int	handle_expnd(const char *str, int i, t_shell *mn_shell,
		char **result)
{
	int		start;
	char	*tmp;
	char	*expanded;
	char	*tmp2;

	start = i;
	if (str[i + 1] == '?')
		i += 2;
	else if (str[i + 1] != '$')
	{
		i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	else
		i += 2;
	tmp = ft_substr(str, start, i - start);
	if (!tmp)
		return (i);
	return (expanded = expand_args(tmp, mn_shell)
		, free(tmp), tmp2 = *result, *result = ft_strjoin(*result, expanded)
		, free(tmp2), free(expanded), i);
}
