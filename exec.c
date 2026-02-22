#include "minishell.h"

static  char    **temp_parse(char *line)
{
    return (ft_split(line, ' '));
}

static void expand_args(char **args, char **envp)
{
	int	i;
	char	*expanded;

	i = 0;
	while (args[i])
	{
		expanded = expand_variables(args[i], envp);
		if (expanded && expanded != args[i])
		{
			free(args[i]);
			args[i] = expanded;
		}
		else if (expanded)
			free(expanded);
		i++;
	}
}

void exec_line(char *line, char ***envp)
{
    char    **args;
    pid_t   pid;
    int     status;
    char    *cmd_path;

    args = temp_parse(line);
    if (args[0] == NULL)
    {
        free_args(args);
        return ;
    }
	expand_args(args, *envp);
    if (is_builtin(args[0]))
    {
        exec_builtin(args, envp);
        free_args(args);
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        cmd_path = find_cmd_path(args[0], *envp);
        if (!cmd_path)
        {
            ft_putstr_fd("minishell: command not found\n", 2);
            exit(127);
        }
        execve(cmd_path,args,*envp);
        perror("minishell: execve");
        exit(EXIT_FAILURE);
    }
    waitpid(pid, &status, 0);
    free_args(args);
}

int	exec_builtin(char **args, char ***envp)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (builtin_echo(args));
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (builtin_cd(args, *envp));
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (builtin_env(*envp));
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (builtin_exit(args));
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (builtin_export(args, envp));
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (builtin_unset(args, envp));
	return (0);
}