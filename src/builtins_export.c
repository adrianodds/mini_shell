#include "../minishell.h"

static int	is_valid_identifier(const char *arg)
{
	int	i;

	if (!arg || !*arg || !ft_isalpha(arg[0]))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_with_equal(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*key;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	key = ft_substr(arg, 0, equal_sign - arg);
	if (!key)
		return (1);
	set_env(shell, key, equal_sign + 1);
	free(key);
	return (0);
}

static int	print_export_error(char *arg)
{
	fprintf(stderr, "minishell: export: '%s': not a valid identifier\n", arg);
	return (1);
}

int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	has_error;

	i = 1;
	has_error = 0;
	while (i < cmd->argc)
	{
		if (!is_valid_identifier(cmd->args[i]))
			has_error = print_export_error(cmd->args[i]);
		else if (ft_strchr(cmd->args[i], '='))
			has_error |= export_with_equal(shell, cmd->args[i]);
		else
			set_env(shell, cmd->args[i], "");
		i++;
	}
	return (has_error);
}

static void	unset_one_var(t_shell *shell, char *name)
{
	int	j;
	int	k;

	j = 0;
	while (shell->envp[j])
	{
		if (ft_strncmp(shell->envp[j], name, ft_strlen(name)) == 0
			&& shell->envp[j][ft_strlen(name)] == '=')
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
}

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->argc)
	{
		unset_one_var(shell, cmd->args[i]);
		i++;
	}
	return (0);
}
