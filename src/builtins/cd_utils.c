/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpineda- <kpineda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:56:34 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/20 00:48:43 by kpineda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	update_env_var(char ***envp, const char *key, const char *value)
{
	char	*new_var;
	char	**env;
	int		i;
	int		len;

	new_var = ft_strjoin3(key, "=", value);
	len	= ft_strlen(key);
	env = *envp;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return ;
		}
		i++;
	}
	*envp = ft_realloc_env(*envp, new_var);
}

char	**ft_realloc_env(char **envp, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free_args(envp);
	return (new_env);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	if (!result)
		return (NULL);
	return (result);
}

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
