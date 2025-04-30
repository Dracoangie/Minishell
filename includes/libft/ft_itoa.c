/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/01 14:03:48 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(int n, char *str, int i)
{
	if (n == -2147483648)
	{
		str[i--] = '8';
		n = -(n / 10);
	}
	if (n >= 10)
		ft_putnbr(n / 10, str, i - 1);
	str[i] = (n % 10) + '0';
}

static int	ft_getlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = ft_getlen(n);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		ft_putnbr(-n, str, i - 1);
	}
	else
		ft_putnbr(n, str, i - 1);
	return (str);
}
/*
int main()
{
	printf("%s", ft_itoa(-2147483648));
	return (0);
}*/