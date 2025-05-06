/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpineda- <kpineda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:59:14 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/06 22:02:00 by kpineda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	execute_pwd(void)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}

void	execute_env(char **envp, char *command)
{
	int	i;
	int	index;
	
	i = 0;
	index = find_env_line(envp, "PATH");
	if	(index == -1 && ft_strcmp(command, "/bin/env") != 0)
	{
		ft_putstr_fd("env: command not found\n", 2);
		return ;
	}
	else
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	
}

char **execute_unset(char **envp, char *command)
{
	int		i;
	char	**out;

	out = ft_split(command, ' ');
	if (!out)
		return (NULL);
	if (!out[1])
	{
		Free_args(out);
		return (envp);		
	}
	i = 1;
	while (out[i])
	{
		envp = delete_env_var(envp, out[i]);
		i++;
	}
	Free_args(out);
	return (envp);
}