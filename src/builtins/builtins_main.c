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
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
		shell->exit_status = 2;
		return (0);
	}
	*exit_code = atoi(cmd->args[1]);
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

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int		exit_code;

	exit_code = 0;
	if (cmd->argc > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return (1);
	}
	if (!parse_exit_arg(shell, cmd, &exit_code))
		return (2);
	shell->exit_status = exit_code & 0xFF;
	return (shell->exit_status);
}
