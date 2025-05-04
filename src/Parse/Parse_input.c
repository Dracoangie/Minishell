/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/03 18:37:53 by tu_nombre_d      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"
#include "libft.h"


int	check_exit_cmd(char *input)
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

	return (args);
}