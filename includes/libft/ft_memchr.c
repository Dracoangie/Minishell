/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/03 18:49:26 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long long	i;
	unsigned char		*aux;

	i = -1;
	aux = (unsigned char *) s;
	while (++i < n)
	{
		if (aux[i] == (unsigned char)c)
			return (&aux[i]);
	}
	return (NULL);
}
/*
int main()
{
	printf ("%p", ft_memchr("hello world!", 'w', 8));
	return (0);
}*/
