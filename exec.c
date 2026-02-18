#include "minishell.h"

static  char    **temp_parse(char *line)
{
    return (ft_split(line, ' '));
}

void exec_line(char *line, char **envp)
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
    if (is_builtin(args[0]))
    {
        exec_builtin(args, envp);
        free_args(args);
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        cmd_path = find_cmd_path(args[0], envp);
        if (!cmd_path)
        {
            ft_putstr_fd("minishell: command not found\n", 2);
            exit(127);
        }
        execve(cmd_path,args,envp);
        perror("minishell: execve");
        exit(EXIT_FAILURE);
    }
    waitpid(pid, &status, 0);
    free_args(args);
}

