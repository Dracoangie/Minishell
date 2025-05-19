/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:56:34 by kpineda-          #+#    #+#             */
/*   Updated: 2025/05/19 15:46:46 by angnavar         ###   ########.fr       */
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
	len = ft_strlen(key);
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
	free(new_var);
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
