/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/02 22:07:05 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	int			counter;
	size_t		i;
	size_t		j;

	counter = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char *) malloc(i + j + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (i + 1));
	while (j--)
	{
		str[i + counter] = s2[counter];
		counter ++;
	}
	return (str[counter + i] = '\0', str);
}
/*
int main()
{
	printf("cadena concatenada: %s", ft_strjoin("hola", " mundo"));
	return (0);
}*/