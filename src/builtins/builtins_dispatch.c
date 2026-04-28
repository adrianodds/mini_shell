/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:12:51 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:17:01 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		shell->exit_status = builtin_echo(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		shell->exit_status = builtin_cd(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		shell->exit_status = builtin_pwd(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		shell->exit_status = builtin_export(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		shell->exit_status = builtin_unset(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		shell->exit_status = builtin_env(shell, cmd);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		builtin_exit(shell, cmd);
}

int	is_builtin(const char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}
