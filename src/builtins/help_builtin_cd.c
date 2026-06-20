/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 16:58:31 by adduarte          #+#    #+#             */
/*   Updated: 2026/06/20 17:50:39 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_pwd_env(t_shell *shell, char *old_cwd)
{
	char	new_cwd[4096];

	set_env(shell, "OLDPWD", old_cwd);
	if (getcwd(new_cwd, sizeof(new_cwd)))
		set_env(shell, "PWD", new_cwd);
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	old_cwd[4096];
	char	*path;
	int		is_oldpwd;

	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!getcwd(old_cwd, sizeof(old_cwd)))
		return (1);
	path = get_cd_path(shell, cmd, &is_oldpwd);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror(path);
		return (1);
	}
	if (is_oldpwd)
		printf("%s\n", path);
	update_pwd_env(shell, old_cwd);
	return (0);
}
