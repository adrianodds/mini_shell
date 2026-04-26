#include "../minishell.h"

int	builtin_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->argc > 1 && ft_strcmp(cmd->args[1], "-n") == 0)
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
	fflush(stdout);
	(void)shell;
	return (0);
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	cwd[4096];

	if (cmd->argc > 2)
	{
		fprintf(stderr, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (cmd->argc == 1)
		path = get_env(shell, "HOME");
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		perror(path);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env(shell, "PWD", cwd);
	return (0);
}

int	builtin_pwd(t_shell *shell, t_cmd *cmd)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
	(void)cmd;
	(void)shell;
	return (0);
}

int	builtin_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	(void)cmd;
	return (0);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int		exit_code;
	int		i;
	char	*str;

	exit_code = 0;
	if (cmd->argc > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return (1);
	}
	if (cmd->argc > 1)
	{
		str = cmd->args[1];
		if (*str == '+' || *str == '-')
			str++;
		if (*str == '\0')
		{
			fprintf(stderr,
				"minishell: exit: %s: numeric argument required\n",
				cmd->args[1]);
			shell->exit_status = 2;
			return (2);
		}
		i = 0;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
			{
				fprintf(stderr,
					"minishell: exit: %s: numeric argument required\n",
					cmd->args[1]);
				shell->exit_status = 2;
				return (2);
			}
			i++;
		}
		exit_code = atoi(cmd->args[1]);
	}
	shell->exit_status = exit_code & 0xFF;
	return (shell->exit_status);
}
