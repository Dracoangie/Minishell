/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/03 16:33:26 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc (count * size);
	if (ptr != NULL)
	{
		ft_bzero(ptr, count * size);
		return (ptr);
	}
	return (NULL);
}

/*
int    main(void)
{
    int *s1 = ft_calloc(5, sizeof(int));
    int *s2 = calloc(5, sizeof(int));

    printf("%d\n", *s1);
    printf("%d", *s2);
    free(s1);
    free(s2);
    return (0);
}*/
