/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:32:40 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/02 21:50:55 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptrsrc;
	size_t			i;

	if (n == 0)
		return (dest);
	ptr = (unsigned char *) dest;
	ptrsrc = (unsigned char *) src;
	if (ptr == ptrsrc && ptr == 0)
		return (dest);
	if (ptr > ptrsrc)
	{
		while (n-- > 0)
			ptr[n] = ptrsrc[n];
	}
	else
	{
		i = -1;
		while (++i < n)
			ptr[i] = ptrsrc[i];
	}
	return (dest);
}
