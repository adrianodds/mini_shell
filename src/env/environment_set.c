/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:04 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 17:35:05 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*join_env_var(const char *key, const char *value)
{
	char	*tmp;
	char	*new_var;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	return (new_var);
}

static int	update_env_value(t_shell *shell, const char *key, const char *value)
{
	int		key_len;
	int		i;
	char	*new_var;

	key_len = ft_strlen(key);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, key_len) == 0
			&& shell->envp[i][key_len] == '=')
		{
			new_var = join_env_var(key, value);
			if (!new_var)
				return (1);
			free(shell->envp[i]);
			shell->envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	env_len(char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

static char	**create_new_env(char **old_env, int env_size)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (env_size + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < env_size)
	{
		new_envp[i] = old_env[i];
		i++;
	}
	return (new_envp);
}

void	set_env(t_shell *shell, const char *key, const char *value)
{
	int		env_size;
	char	*new_var;
	char	**new_envp;

	if (update_env_value(shell, key, value))
		return ;
	env_size = env_len(shell->envp);
	new_envp = create_new_env(shell->envp, env_size);
	if (!new_envp)
		return ;
	new_var = join_env_var(key, value);
	if (!new_var)
	{
		free(new_envp);
		return ;
	}
	new_envp[env_size] = new_var;
	new_envp[env_size + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
}
