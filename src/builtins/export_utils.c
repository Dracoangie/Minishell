/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpineda- <kpineda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 02:07:36 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/21 03:43:38 by kpineda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_sorted_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			printf("declare -x %s\n", envp[i]);
		}
		else
			printf("%s\n", envp[i]);
		i++;
	}
}

void	handle_export_arg(t_shell *mn_shell, char *arg)
{
	char	*equal_pos;

	if (!is_valid_identifier(arg))
	{
		perr_export(mn_shell, arg);
		return ;
	}
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		*equal_pos = '\0';
		update_env_var(&(mn_shell->envp), arg, equal_pos + 1);
		*equal_pos = '=';
	}
	else if (!get_env_value(arg, mn_shell->envp))
	{
		update_env_var(&(mn_shell->envp), arg, "");
	}
}
