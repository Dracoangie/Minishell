/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_to_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:08:03 by angnavar          #+#    #+#             */
/*   Updated: 2025/05/20 22:19:44 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static int	next_pipe(const char *s, int i, char c, char *quote)
{
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"'))
		{
			if (*quote == '\0')
				*quote = s[i];
			else if (*quote == s[i])
				*quote = '\0';
		}
		else if (*quote == '\0' && s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static t_cmd	*create_cmd(char *seg, t_shell *mn_shell, t_cmd **head)
{
	t_cmd	*new;
	char	**args;

	if (!seg)
		return (perr_mem(mn_shell), free_cmds(*head), NULL);
	args = ft_split_with_quotes(seg, ' ');
	free(seg);
	if (!args)
		return (perr_shll(mn_shell, "Error: quote not closed", 1),
			free_cmds(*head),
			NULL);
	new = init_cmd(args);
	if (!new)
		return (perr_mem(mn_shell), free_cmds(*head), NULL);
	return (new);
}

static int	parse_empty(const char *s, char c, t_shell *mn_shell,
		t_cmd_state *state)
{
	int	tmp;

	if (s[state->i] == c)
		state->i++;
	tmp = state->i;
	while (s[tmp] == ' ')
		tmp++;
	if (s[tmp] == c)
		return (perr_redir(mn_shell, "|"), free_cmds(state->head), -1);
	if (s[tmp] == '\0')
		return (perr_redir(mn_shell, "newline"), free_cmds(state->head), -1);
	return (0);
}

static int	set_state(const char *s, char c, t_shell *mn_shell,
		t_cmd_state *state)
{
	t_cmd	*new;
	int		start;
	char	quote;

	quote = '\0';
	if (parse_empty(s, c, mn_shell, state) == -1)
		return (-1);
	start = state->i;
	state->i = next_pipe(s, state->i, c, &quote);
	if (quote != '\0')
		return (perr_shll(mn_shell, "Error: quote not closed", 1),
			free_cmds(state->head), -1);
	new = create_cmd(ft_substr(s, start, state->i - start), mn_shell,
			&state->head);
	if (!new)
		return (-1);
	if (!state->head)
		state->head = new;
	else
		state->curr->next = new;
	state->curr = new;
	return (1);
}

t_cmd	*parse_to_cmds(const char *s, char c, t_shell *mn_shell)
{
	t_cmd_state	state;
	int			res;

	state.head = NULL;
	state.curr = NULL;
	state.i = 0;
	while (s[state.i])
	{
		res = set_state(s, c, mn_shell, &state);
		if (res == -1)
			return (NULL);
		else if (res == 0)
			break ;
	}
	return (state.head);
}
