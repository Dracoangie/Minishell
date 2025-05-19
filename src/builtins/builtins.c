/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpineda- <kpineda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:59:14 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/20 00:52:08 by kpineda-         ###   ########.fr       */
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

char	**execute_unset(char **envp, char *command)
{
	int		i;
	char	**out;

	out = ft_split(command, ' ');
	if (!out)
		return (NULL);
	if (!out[1])
	{
		free_args(out);
		return (envp);
	}
	i = 1;
	while (out[i])
	{
		envp = delete_env_var(envp, out[i]);
		i++;
	}
	free_args(out);
	return (envp);
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
	if (!args[1])
		return (cd_to_home(mn_shell, oldpwd));
	if (ft_strcmp(args[1], "-") == 0)
		return (cd_to_oldpwd(mn_shell, oldpwd));
	return (cd_to_path(mn_shell, args[1], oldpwd));
}

int	execute_export(t_shell *mn_shell, char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal_pos;

	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			i++;
			continue ;
		}
		if (equal_pos)
		{
			*equal_pos = '\0';
			key = args[i];
			value = equal_pos + 1;
			update_env_var(&(mn_shell->envp), key, value);
			*equal_pos = '=';
		}
		else if (!get_env_value(args[i], mn_shell->envp))
			update_env_var(&(mn_shell->envp), args[i], "");
		i++;
	}
	return (0);
}
