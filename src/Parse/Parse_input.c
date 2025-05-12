/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/12 15:12:24 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"
#include "libft.h"


int	Check_exit_cmd(char *input)
{
	if (ft_strcmp(input, "exit") == 0)
	{
		free(input);
		return (1);
	}
	return (0);
}

int	Builtin_cmds(t_cmd	*cmds, t_shell *mn_shell)
{
	if (ft_strcmp(cmds->args[0], "echo") == 0)
		return (Parse_echo(cmds, mn_shell));
	else if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmds->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmds->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmds->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmds->args[0], "env") == 0)
		return (1);
	return (0);
}

int Parse_redirect(t_cmd *cmds, t_shell *mn_shell)
{
    const char *redirs[] = {"<<", "<", ">>", ">", "|", NULL};
	t_cmd *aux;
    int j;

	aux = cmds;
	while (aux)
	{
		if (aux->args[0] == NULL)
			return (0);
		j = ft_count_args(aux->args) - 1;
		if (j < 1)
			return (0);
		if (ft_argstr(redirs, aux->args[j]) != -1 && aux->next == NULL)
			return (Perr_redir(mn_shell, "newline"), 1);
		if (ft_argstr(redirs, aux->args[j]) != -1)
			return (Perr_redir(mn_shell, "|"), 1);
		while (j > 0)
		{
			if (ft_argstr(redirs, aux->args[j]) != -1)
			{
				if (ft_argstr(redirs, aux->args[j - 1]) != -1)
					return (Perr_redir(mn_shell, (char *)aux->args[j]), 1);
			}
			j--;
		}
		aux = aux->next;
	}
    return (0);
}

void	Parse_quotes(t_cmd *cmd)
{
	int		i = 0;
	char	*tmp;

	if (!cmd || !cmd->args)
		return;
	while (cmd->args[i])
	{
		tmp = ft_remove_quotes(cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
		i++;
	}
}


t_cmd	*Parse_input(char *input, t_shell *mn_shell)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = Parse_to_cmds(input, '|', mn_shell);
	if (!cmds)
		return (NULL);
	else if (cmds->args[0] == NULL)
		return (Free_cmds(cmds), NULL);
	current = cmds;
	ft_print_cmds(cmds);
	while (current)
	{
		if (Parse_redirect(current, mn_shell) == 1)
			return (Free_cmds(cmds), NULL);
		if(Builtin_cmds(current, mn_shell))
			return (Free_cmds(cmds), NULL);
		Parse_quotes(cmds);
		current->path = Check_cmd(mn_shell, current->args);
		if (!current->path)
			return (Free_cmds(cmds), NULL);
		if(Parse_files(mn_shell, current, cmds) == 0)
			return (Free_cmds(cmds), NULL);
		current = current->next;
	}
	return (cmds);
}
