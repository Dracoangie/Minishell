/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/03 18:40:14 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*aux;

	aux = (char *)s;
	while (*aux)
		aux++;
	if (*aux == (unsigned char) c)
		return (aux);
	while (aux != s)
	{
		aux--;
		if (*aux == (unsigned char) c)
			return (aux);
	}
	if (*aux == (unsigned char)c)
		return (aux);
	return (NULL);
}
/*
int main()
{
	printf ("%s", ft_strrchr("hello world", 'w'));
	return (0);
}*/