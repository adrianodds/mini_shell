#include "../../minishell.h"

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
