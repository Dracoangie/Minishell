/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/04/30 14:40:30 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"
#include "libft.h"

int	check_exit_command(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		free(input);
		return (1);
	}
	return (0);
}

char	**Parse_input(char *input)
{
	char	**args;
	int		i;

	args = ft_split(input, ' ');
	if (!args)
	{
		perror("Error: Memory allocation failed");
		return (NULL);
	}
	if (args[0] == NULL)
	{
		free(args);
		return (NULL);
	}
	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");

	return (args);
}
