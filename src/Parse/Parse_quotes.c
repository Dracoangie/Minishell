/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:13:55 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/12 14:21:49 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	cmd_count(const char *s)
{
    int	i;
    int	result;
    char	quote = '\0';

    i = 0;
    result = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
        {
            if (quote == '\0')
            {
                quote = s[i];
                result++;
            }
            else if (quote == s[i])
                quote = '\0';
            i++;
            continue;
        }
        if ((s[i] == '<' || s[i] == '>') && quote == '\0')
        {
            result++;
            if (s[i + 1] == s[i])
                i++;
            i++;
            continue;
        }
        if (s[i] != ' ' && s[i] != '"' && s[i] != '\'' && quote == '\0')
        {
            result++;
            while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'' &&
                   s[i] != '<' && s[i] != '>' && quote == '\0')
                i++;
            continue;
        }
        i++;
    }
    return (result);
}

char	**ft_split_with_quotes(const char *s, char c)
{
    char	**result;
    int		i = 0, j = 0, start;
    char	quote = '\0';

    result = ft_calloc(sizeof(char *), (cmd_count(s) + 1));
    if (!result)
        return (NULL);
    while (s[i])
    {
        while (s[i] == c && s[i])
            i++;
        if (!s[i])
            break;
        start = i;
        if (s[i] == '\'' || s[i] == '"')
        {
            quote = s[i];
			i++;
            while (s[i] && s[i] != quote)
                i++;
			if (s[i] == quote)
				i++;
			quote = '\0';
        }
        else if ((s[i] == '<' || s[i] == '>') && quote == '\0')
        {
            if (s[i + 1] == s[i])
                i += 2;
            else
                i++;
        }
        else
        {
            while (s[i] && s[i] != c && !(s[i] == '\'' || s[i] == '"') &&
                   !(s[i] == '<' || s[i] == '>'))
                i++;
        }
        result[j++] = ft_substr(s, start, i - start);
        if (!result[j - 1])
        {
            Free_args(result);
            return (NULL);
        }
    }
    result[j] = NULL;
    return (result);
}