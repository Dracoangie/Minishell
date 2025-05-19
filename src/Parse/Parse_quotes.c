/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:13:55 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/19 15:40:56 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static void	skip_token(const char *s, int *i, char *quote)
{
	if (s[*i] == '"' || s[*i] == '\'')
	{
		if (*quote == '\0')
			*quote = s[*i];
		else if (*quote == s[*i])
			*quote = '\0';
		(*i)++;
	}
	else if ((s[*i] == '<' || s[*i] == '>') && *quote == '\0')
	{
		if (s[*i + 1] == s[*i])
			(*i)++;
		(*i)++;
	}
	else if (s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && *quote == '\0')
	{
		while (s[*i] && s[*i] != ' ' && s[*i] != '"' && s[*i] != '\''
			&& s[*i] != '<' && s[*i] != '>' && *quote == '\0')
			(*i)++;
	}
	else
		(*i)++;
}

int	tcmd_count(const char *s)
{
	int		i;
	int		result;
	char	quote;

	i = 0;
	result = 0;
	quote = '\0';
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'')
			|| ((s[i] == '<' || s[i] == '>') && quote == '\0')
			|| (s[i] != ' ' && s[i] != '"' && s[i] != '\'' && quote == '\0'))
			result++;
		skip_token(s, &i, &quote);
	}
	return (result);
}

static int	extract_token_with_quotes(const char *s, char **result, int *i,
		int *j)
{
	int		start;
	char	q;

	q = '\0';
	start = *i;
	while (s[*i])
	{
		if ((s[*i] == '\'' || s[*i] == '"'))
		{
			if (q == '\0')
				q = s[*i];
			else if (q == s[*i])
				q = '\0';
		}
		else if (q == '\0' && (s[*i] == ' ' || s[*i] == '<' || s[*i] == '>'))
			break ;
		(*i)++;
	}
	if (*i > start)
	{
		result[(*j)++] = ft_substr(s, start, *i - start);
		if (!result[*j - 1])
			return (0);
	}
	return (1);
}

static int	extract_redirection_token(const char *s, char **result, int *i,
		int *j)
{
	int	start;

	if (s[*i] == '<' || s[*i] == '>')
	{
		start = *i;
		if (s[*i + 1] == s[*i])
			*i += 2;
		else
			(*i)++;
		result[(*j)++] = ft_substr(s, start, *i - start);
		if (!result[*j - 1])
			return (0);
	}
	return (1);
}

char	**ft_split_with_quotes(const char *s, char c)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = ft_calloc(tcmd_count(s) + 2, sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		if (!extract_token_with_quotes(s, result, &i, &j))
			return (free_args(result), NULL);
		if (!extract_redirection_token(s, result, &i, &j))
			return (free_args(result), NULL);
	}
	result[j] = NULL;
	return (result);
}
