/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:59:14 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/18 21:47:19 by angnavar         ###   ########.fr       */
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
	char	*target;
	char	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return 1;
	}
	oldpwd = ft_strdup(cwd);

	if (args[1] == NULL)
	{
		target = get_env_value("HOME", mn_shell->envp);
		if (target == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return 1;
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value("OLDPWD", mn_shell->envp);
		if (target == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return 1;
		}
		printf("%s\n", target);
	}
	else
		target = args[1];
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return 1;
	}
	//to do
	update_env_var(&(mn_shell->envp), "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_var(&(mn_shell->envp), "PWD", cwd);
	else
		perror("getcwd");
	free(oldpwd);
	return 0;
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
			continue;
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
	return 0;
}
