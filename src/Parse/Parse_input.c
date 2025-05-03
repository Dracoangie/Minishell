/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre_de_usuario <tu_email@ejemplo.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/03 15:34:02 by tu_nombre_d      ###   ########.fr       */
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
	//int		i;

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
	//i = 0;
	/*while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf("|");
		i++;
	}
	printf("\n");*/

	return (args);
}
/*
t_cmd *create_cmd_node(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->redirections = NULL;
    cmd->redir_count = 0;
    cmd->next = NULL;
    return (cmd);
}

void add_redirection(t_cmd *cmd, char *file, int type)
{
    t_redirection *new_redir;

    cmd->redirections = realloc(cmd->redirections, sizeof(t_redirection) * (cmd->redir_count + 1));
    if (!cmd->redirections)
        return;
    new_redir = &cmd->redirections[cmd->redir_count];
    new_redir->file = ft_strdup(file);
    new_redir->type = type;
    cmd->redir_count++;
}

t_cmd *parse_input(char *input)
{
    t_cmd *head = NULL;
    t_cmd *current = NULL;
    char **tokens = ft_split(input, ' ');
    int i = 0;

    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "|") == 0) // Pipe
        {
            if (!current)
                return (NULL); // Error: pipe sin comando previo
            current->next = create_cmd_node();
            current = current->next;
        }
        else if (ft_strcmp(tokens[i], "<") == 0) // Redirección de entrada
        {
            if (!tokens[i + 1])
                return (NULL); // Error: falta archivo
            add_redirection(current, tokens[++i], 0);
        }
        else if (ft_strcmp(tokens[i], ">") == 0) // Redirección de salida
        {
            if (!tokens[i + 1])
                return (NULL); // Error: falta archivo
            add_redirection(current, tokens[++i], 1);
        }
        else if (ft_strcmp(tokens[i], ">>") == 0) // Redirección de salida (append)
        {
            if (!tokens[i + 1])
                return (NULL); // Error: falta archivo
            add_redirection(current, tokens[++i], 2);
        }
        else // Argumento o comando
        {
            if (!current)
                current = create_cmd_node();
            current->args = realloc(current->args, sizeof(char *) * (ft_tablen(current->args) + 2));
            current->args[ft_tablen(current->args)] = ft_strdup(tokens[i]);
            current->args[ft_tablen(current->args) + 1] = NULL;
        }
        i++;
    }
    free(tokens);
    return (head);
}*/