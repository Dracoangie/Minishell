/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/09 14:55:15 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"
#include "libft.h"


int	Check_exit_cmd(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		free(input);
		return (1);
	}
	return (0);
}

int	get_next_quote(int i, char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	cmd_count(const char *s)
{
    int	i;
    int	result;
    char	quote = '\0';

    i = 0;
    result = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
        {
            if (quote == '\0')
            {
                quote = s[i];
                result++;
            }
            else if (quote == s[i])
                quote = '\0';
            i++;
            continue;
        }
        if ((s[i] == '<' || s[i] == '>') && quote == '\0')
        {
            result++;
            if (s[i + 1] == s[i])
                i++;
            i++;
            continue;
        }
        if (s[i] != ' ' && s[i] != '"' && s[i] != '\'' && quote == '\0')
        {
            result++;
            while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'' &&
                   s[i] != '<' && s[i] != '>' && quote == '\0')
                i++;
            continue;
        }
        i++;
    }
    return (result);
}

int	cmd_count2(const char *s)
{
    int	i;
    int	result;

    i = -1;
    result = 0;
    while (s[++i])
    {
        if ((s[i] != ' ' && s[i] != '"' && s[i] != '\'')
            && (s[i + 1] == ' ' || s[i + 1] == '\0'
                || s[i + 1] == '"' || s[i + 1] == '\''))
				result++;
        if (s[i] == '"' || s[i] == '\'')
        {
            result++;
            i = get_next_quote(i + 1, (char *)s, s[i]);
        }
    }
    return (result);
}

char	**ft_split_with_quotes(const char *s, char c)
{
    char	**result;
    int		i = 0, j = 0, start;
    char	quote = '\0';

    result = ft_calloc(sizeof(char *), (cmd_count(s) + 1));
    if (!result)
        return (NULL);
    while (s[i])
    {
        while (s[i] == c && s[i])
            i++;
        if (!s[i])
            break;
        start = i;
        if (s[i] == '\'' || s[i] == '"')
        {
            quote = s[i];
			i++;
            while (s[i] && s[i] != quote)
                i++;
			if (s[i] == quote)
				i++;
			quote = '\0';
        }
        else if ((s[i] == '<' || s[i] == '>') && quote == '\0')
        {
            if (s[i + 1] == s[i])
                i += 2;
            else
                i++;
        }
        else
        {
            while (s[i] && s[i] != c && !(s[i] == '\'' || s[i] == '"') &&
                   !(s[i] == '<' || s[i] == '>'))
                i++;
        }
        result[j++] = ft_substr(s, start, i - start);
        if (!result[j - 1])
        {
            Free_args(result);
            return (NULL);
        }
    }
    result[j] = NULL;
    return (result);
}

t_cmd	*ft_split_to_cmds(char const *s, char c, t_shell *mn_shell)
{
    t_cmd	*head = NULL;
    t_cmd	*current = NULL;
    t_cmd	*new_cmd;
    int		i;
    int		start;
    char	quote = '\0';

    i = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
        {
            if (quote == '\0')
                quote = s[i];
            else if (quote == s[i])
                quote = '\0';
        }
        if (s[i] != c || quote != '\0')
        {
            start = i;
            while (s[i] && (s[i] != c || quote != '\0'))
            {
                if (s[i] == '\'' || s[i] == '"')
                {
                    if (quote == '\0')
                        quote = s[i];
                    else if (quote == s[i])
                        quote = '\0';
                }
                i++;
            }
            char *cmd_str = ft_substr(s, start, i - start);
            if (!cmd_str)
                return (Perr_mem(mn_shell), NULL);
            char **args = ft_split_with_quotes(cmd_str, ' ');
            free(cmd_str);
            new_cmd = Init_cmd(args);
            if (!new_cmd)
				return (Perr_mem(mn_shell), NULL);
            if (!head)
                head = new_cmd;
            else
                current->next = new_cmd;
            current = new_cmd;
        }
        else
            i++;
    }
	if (quote != '\0')
        return (Free_cmds(head), Perr_shll (mn_shell,"Error: Unmatched quotes in input", 1), NULL);
    return (head);
}

int Parse_echo(t_cmd *cmds, t_shell *mn_shell)
{
	if (cmds->args[1] && ft_strcmp(cmds->args[1], "-n") == 0)
		return (1);
	else if (cmds->args[1] && ft_strcmp(cmds->args[1], "$SHLVL") == 0)
		return (printf("%d\n", mn_shell->lvl), 1);
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

t_cmd	*Parse_input(char *input, t_shell *mn_shell)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = ft_split_to_cmds(input, '|', mn_shell);
	if (!cmds)
		return (NULL);
	else if (cmds->args[0] == NULL)
		return (Free_cmds(cmds), NULL);
	current = cmds;
	print_cmds(cmds);
	while (current)
	{
		if (Parse_redirect(current, mn_shell) == 1)
			return (Free_cmds(cmds), NULL);
		if(Builtin_cmds(current, mn_shell))
			return (Free_cmds(cmds), NULL);
		current->path = Check_cmd(mn_shell, current->args);
		if (!current->path)
			return (Free_cmds(cmds), NULL);
		if(Parse_files(mn_shell, current, cmds) == 0)
			return (Free_cmds(cmds), NULL);
		current = current->next;
	}
	return (cmds);
}
