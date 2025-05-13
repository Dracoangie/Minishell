/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:13:55 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/13 18:18:25 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	tcmd_count(const char *s)
{
	int		i;
	int		result;
	char	quote;

	quote = '\0';
	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (quote == '\0')
				quote = s[i];
			else if (quote == s[i])
				quote = '\0';
			i++;
			continue ;
		}
		if ((s[i] == '<' || s[i] == '>') && quote == '\0')
		{
			result++;
			if (s[i + 1] == s[i])
				i++;
			i++;
			continue ;
		}
		if (s[i] != ' ' && s[i] != '"' && s[i] != '\'' && quote == '\0')
		{
			result++;
			while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\''
				&& s[i] != '<' && s[i] != '>' && quote == '\0')
				i++;
			continue ;
		}
		i++;
	}
	return (result);
}

char	**ft_split_with_quotes(const char *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	result = ft_calloc(tcmd_count(s) + 2, sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i])
		{
			if ((s[i] == '\'' || s[i] == '"'))
			{
				if (quote == '\0')
					quote = s[i];
				else if (quote == s[i])
					quote = '\0';
			}
			else if (quote == '\0' && (s[i] == c || s[i] == '<' || s[i] == '>'))
				break ;
			i++;
		}
		if (i > start)
		{
			result[j++] = ft_substr(s, start, i - start);
			if (!result[j - 1])
				return (free_args(result), NULL);
		}
		if (quote == '\0' && (s[i] == '<' || s[i] == '>'))
		{
			start = i;
			if (s[i + 1] == s[i])
				i += 2;
			else
				i++;
			result[j++] = ft_substr(s, start, i - start);
			if (!result[j - 1])
				return (free_args(result), NULL);
		}
	}
	result[j] = NULL;
	return (result);
}
