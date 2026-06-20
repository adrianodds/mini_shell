/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:14:35 by adduarte          #+#    #+#             */
/*   Updated: 2026/06/20 17:00:22 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	valid_exit_arg(char *str)
{
	int	i;

	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_exit_arg(t_shell *shell, t_cmd *cmd, int *exit_code)
{
	if (cmd->argc <= 1)
		return (1);
	if (!valid_exit_arg(cmd->args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
		shell->exit_status = 2;
		return (0);
	}
	*exit_code = ft_atoi(cmd->args[1]);
	return (1);
}

int	builtin_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->argc > 1 && ft_strncmp(cmd->args[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (i < cmd->argc)
	{
		printf("%s", cmd->args[i]);
		if (i < cmd->argc - 1)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	(void)shell;
	return (0);
}

char	*get_cd_path(t_shell *shell, t_cmd *cmd, int *is_oldpwd)
{
	char	*oldpwd;

	*is_oldpwd = 0;
	if (cmd->argc == 1)
		return (get_env(shell, "HOME"));
	if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		oldpwd = get_env(shell, "OLDPWD");
		if (!oldpwd)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		*is_oldpwd = 1;
		return (oldpwd);
	}
	return (cmd->args[1]);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int		exit_code;

	exit_code = 0;
	if (cmd->argc > 2)
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return (1);
	}
	if (!parse_exit_arg(shell, cmd, &exit_code))
		return (2);
	shell->exit_status = exit_code & 0xFF;
	return (shell->exit_status);
}
