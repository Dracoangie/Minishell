/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/05 16:35:31 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char **str, int j)
{
	if (!str[j])
	{
		while (j > 0)
			free(str[--j]);
		free(str);
		return (1);
	}
	return (0);
}

static int	ft_wcounter(const char *s, char c)
{
	int	i;
	int	in_word;

	i = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			i++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		start;

	str = (char **)ft_calloc (ft_wcounter (s, c) + 1, sizeof (char *));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			str[j] = ft_substr(s, start, i - start);
			if (ft_free (str, j))
				return (NULL);
			j++;
			i--;
		}
	}
	return (str);
}
/*
int main ()
{
	char *s = "      split       this for   me  !       ";

	char **result = ft_split(s, ' ');
	int i = 0;
	while (result[i] != NULL)
	{
		printf ("%s ", result[i]);
		i++;
	}
	return (0);
}*/
