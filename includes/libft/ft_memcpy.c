/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:32:40 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/05 16:33:47 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptrsrc;

	ptr = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	if (ptr == ptrsrc && ptr == 0)
		return (dest);
	else
	{
		i = -1;
		while (++i < n)
			ptr[i] = ptrsrc[i];
	}
	return (dest);
}
