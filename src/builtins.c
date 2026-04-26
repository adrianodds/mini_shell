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
	return (0);
	(void)shell;
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
	int		j;
	int		has_error;

	i = 1;
	has_error = 0;
	while (i < cmd->argc)
	{
		equal_sign = ft_strchr(cmd->args[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(cmd->args[i], equal_sign - cmd->args[i]);
			if (!key || *key == '\0' || !ft_isalpha(key[0]))
			{
				fprintf(stderr, "minishell: export: '%s': not a valid identifier\n", 
					cmd->args[i]);
				free(key);
				has_error = 1;
				i++;
				continue;
			}
			j = 1;
			while (key[j])
			{
				if (!ft_isalnum(key[j]) && key[j] != '_')
				{
					fprintf(stderr, "minishell: export: '%s': not a valid identifier\n", 
						cmd->args[i]);
					free(key);
					has_error = 1;
					i++;
					goto next_export;
				}
				j++;
			}
			value = equal_sign + 1;
			set_env(shell, key, value);
			free(key);
		}
		else
		{
			if (*cmd->args[i] == '\0' || !ft_isalpha(cmd->args[i][0]))
			{
				fprintf(stderr, "minishell: export: '%s': not a valid identifier\n", 
					cmd->args[i]);
				has_error = 1;
				i++;
				continue;
			}
			j = 1;
			while (cmd->args[i][j])
			{
				if (!ft_isalnum(cmd->args[i][j]) && cmd->args[i][j] != '_')
				{
					fprintf(stderr, "minishell: export: '%s': not a valid identifier\n", 
						cmd->args[i]);
					has_error = 1;
					i++;
					goto next_export;
				}
				j++;
			}
			set_env(shell, cmd->args[i], "");
		}
next_export:
		i++;
	}
	return (has_error);
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
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", 
				cmd->args[1]);
			exit(2);
		}
		i = 0;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
			{
				fprintf(stderr, "minishell: exit: %s: numeric argument required\n", 
					cmd->args[1]);
				exit(2);
			}
			i++;
		}
		exit_code = atoi(cmd->args[1]);
	}
	free_shell(shell);
	exit(exit_code & 0xFF);
	return (0);
}
