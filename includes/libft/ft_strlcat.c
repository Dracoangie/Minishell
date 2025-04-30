/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:32:40 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/10 17:52:34 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	count = 0;
	while (dst[i] != '\0')
		i++;
	while (src[count] != '\0')
		count++;
	if (size <= i)
		count += size;
	else
		count += i;
	if (size <= 0)
		return (count);
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		++i;
		++j;
	}
	dst[i] = '\0';
	return (count);
}
/*
int main()
{
	char dst[] = "hola ";
	char src[] = "hola mundo"; 
	printf("longitud del array: %li, 
	\n cadena: %s", ft_strlcat(dst, src, 12), dst);
	return (0);
}*/
