/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:04 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:22:44 by adduarte         ###   ########.fr       */
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

void	set_env(t_shell *shell, const char *key, const char *value)
{
	int		i;
	char	*new_var;

	if (update_env_value(shell, key, value))
		return ;
	i = env_len(shell->envp);
	shell->envp = realloc(shell->envp, sizeof(char *) * (i + 2));
	new_var = join_env_var(key, value);
	if (!new_var)
		return ;
	shell->envp[i] = new_var;
	shell->envp[i + 1] = NULL;
}
