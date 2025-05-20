/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:56:34 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/20 22:10:13 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	cd_to_home(t_shell *mn_shell, char *oldpwd)
{
	char	cwd[PATH_MAX];
	char	*target;

	target = get_env_value("HOME", mn_shell->envp);
	if (!target)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		free(oldpwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	update_env_var(&(mn_shell->envp), "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(&(mn_shell->envp), "PWD", cwd);
	else
		perror("getcwd");
	free(oldpwd);
	return (0);
}

int	cd_to_oldpwd(t_shell *mn_shell, char *oldpwd)
{
	char	cwd[PATH_MAX];
	char	*target;

	target = get_env_value("OLDPWD", mn_shell->envp);
	if (!target)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		free (oldpwd);
		return (1);
	}
	printf("%s\n", target);
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	update_env_var(&(mn_shell->envp), "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(&(mn_shell->envp), "PWD", cwd);
	else
		perror("getcwd");
	free(oldpwd);
	return (0);
}

int	cd_to_path(t_shell *mn_shell, char *path, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	update_env_var(&(mn_shell->envp), "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(&(mn_shell->envp), "PWD", cwd);
	else
		perror("getcwd");
	free(oldpwd);
	return (0);
}
