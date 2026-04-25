#include "../minishell.h"

int	builtin_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	newline;
	char	buf[4096];
	int	n;

	fprintf(stderr, "[DEBUG] builtin_echo called\n");
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
	fprintf(stderr, "[DEBUG] about to read from stdin\n");
	while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
	{
		fprintf(stderr, "[DEBUG] read %d bytes\n", n);
	}
	fprintf(stderr, "[DEBUG] finished reading\n");
	return (0);
	(void)shell;
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	cwd[4096];

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
	return (0);
	(void)cmd;
	(void)shell;
}

int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;

	i = 1;
	while (i < cmd->argc)
	{
		equal_sign = ft_strchr(cmd->args[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(cmd->args[i], equal_sign - cmd->args[i]);
			value = equal_sign + 1;
			set_env(shell, key, value);
			free(key);
		}
		else
			set_env(shell, cmd->args[i], "");
		i++;
	}
	return (0);
}

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (i < cmd->argc)
	{
		j = 0;
		while (shell->envp[j])
		{
			if (ft_strncmp(shell->envp[j], cmd->args[i], ft_strlen(cmd->args[i])) == 0
				&& shell->envp[j][ft_strlen(cmd->args[i])] == '=')
			{
				k = j;
				while (shell->envp[k])
				{
					shell->envp[k] = shell->envp[k + 1];
					k++;
				}
				j--;
			}
			j++;
		}
		i++;
	}
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
	return (0);
	(void)cmd;
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->argc > 1)
		exit_code = atoi(cmd->args[1]);
	(void)shell;
	exit(exit_code);
}
