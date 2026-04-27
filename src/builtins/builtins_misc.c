#include "../../minishell.h"

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
