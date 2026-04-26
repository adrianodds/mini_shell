#include "../minishell.h"

void	handle_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		shell->exit_status = builtin_echo(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		shell->exit_status = builtin_cd(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		shell->exit_status = builtin_pwd(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		shell->exit_status = builtin_export(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		shell->exit_status = builtin_unset(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		shell->exit_status = builtin_env(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(shell, cmd);
}

int	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
