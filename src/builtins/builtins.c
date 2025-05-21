/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpineda- <kpineda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:59:14 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/21 03:43:32 by kpineda-         ###   ########.fr       */
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
	if (index == -1 && ft_strcmp(command, "/bin/env") != 0)
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

void	execute_unset(t_shell *mn_shell, t_cmd *command)
{
	int	i;

	if (!command)
		return ;
	i = 1;
	while (command->args[i])
	{
		mn_shell->envp = delete_env_var(mn_shell->envp, command->args[i]);
		i++;
	}
}

int	execute_cd(t_shell *mn_shell, char **args)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("getcwd"), 1);
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (perror("malloc"), 1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (cd_to_home(mn_shell, oldpwd));
	if (ft_strcmp(args[1], "-") == 0)
		return (cd_to_oldpwd(mn_shell, oldpwd));
	return (cd_to_path(mn_shell, args[1], oldpwd));
}

int	execute_export(t_shell *mn_shell, char **args)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		print_sorted_env(mn_shell->envp);
		return (mn_shell->last_exit_code);
	}
	while (args[i])
	{
		handle_export_arg(mn_shell, args[i]);
		i++;
	}
	return (mn_shell->last_exit_code);
}
