/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/14 21:03:10 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
#include "libft.h"

int	check_exit_cmd(char *input)
{
	if (ft_strcmp(input, "exit") == 0)
	{
		free(input);
		return (1);
	}
	return (0);
}

int	builtin_cmds(t_cmd *cmds, t_shell *mn_shell)
{
	if (ft_strcmp(cmds->args[0], "echo") == 0)
		return (0);
	//	return (execute_echo(cmds, mn_shell));
	else if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmds->args[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmds->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmds->args[0], "unset") == 0)
		return (execute_unset(mn_shell->envp, cmds->args[0]), 0);
	else if (ft_strcmp(cmds->args[0], "env") == 0)
		return (0);
	return (0);
}

int	parse_redirect(t_cmd *cmds, t_shell *mn_shell)
{
	const char	**redirs;
	t_cmd		*aux;
	int			j;

	redirs = (const char *[]){"<<", "<", ">>", ">", "|", NULL};
	aux = cmds;
	while (aux)
	{
		j = ft_count_args(aux->args) - 1;
		if (aux->args[0] == NULL || j < 1)
			return (0);
		if (ft_argstr(redirs, aux->args[j]) != -1 && aux->next == NULL)
			return (perr_redir(mn_shell, "newline"), 1);
		if (ft_argstr(redirs, aux->args[j]) != -1)
			return (perr_redir(mn_shell, "|"), 1);
		while (j > 0)
		{
			if (ft_argstr(redirs, aux->args[j]) != -1
				&& ft_argstr(redirs, aux->args[j - 1]) != -1)
				return (perr_redir(mn_shell, (char *)aux->args[j]), 1);
			j--;
		}
		aux = aux->next;
	}
	return (0);
}

void	parse_quotes(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!cmd || !cmd->args)
		return ;
	while (cmd->args[i])
	{
		tmp = ft_remove_quotes(cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
		i++;
	}
}

t_cmd	*parse_input(char *input, t_shell *mn_shell)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = parse_to_cmds(input, '|', mn_shell);
	if (!cmds)
		return (NULL);
	else if (cmds->args[0] == NULL)
		return (free_cmds(cmds), NULL);
	current = cmds;
	ft_print_cmds(cmds);
	while (current)
	{
		if (parse_redirect(current, mn_shell) == 1)
			return (free_cmds(cmds), NULL);
		if (builtin_cmds(current, mn_shell))
			return (free_cmds(cmds), NULL);
		parse_quotes(current);
		current->path = check_cmd(mn_shell, current->args);
		if (!current->path)
			return (free_cmds(cmds), NULL);
		if (parse_files(mn_shell, current, cmds) == 0)
			return (free_cmds(cmds), NULL);
		current = current->next;
	}
	return (cmds);
}
