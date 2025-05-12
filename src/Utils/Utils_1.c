/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:42 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/12 15:11:37 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int ft_count_args(char **args)
{
    int count = 0;

    if (!args)
        return (0);
    while (args[count])
        count++;
    return (count);
}

void ft_print_cmds(t_cmd *cmd_list)
{
    t_cmd *current = cmd_list;
    int i;

    while (current)
    {
        printf("Command:\n");
        i = 0;
        while (current->args && current->args[i])
        {
            printf("  Arg[%d]: %s\n", i, current->args[i]);
            i++;
        }
        printf("  Input FD: %d\n", current->input_fd);
        printf("  Output FD: %d\n", current->output_fd);
        current = current->next;
    }
}

char	*ft_remove_quotes(const char *str)
{
	int		i = 0;
	int		j = 0;
	char	*new_str = malloc(strlen(str) + 1);

	if (!new_str)
		return NULL;

	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return new_str;
}