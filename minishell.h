#ifndef MINISHELL_H
#define MINISHELL_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <ctype.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

/**************EXEC***************/
void	exec_line(char *line, char **envp);

/***************Utils*************/
void	free_args(char **args);

/****************Path*************/
char	*get_path(char **envp);
char	*find_cmd_path(char *cmd, char **envp);

/**************Builtins***********/
int		builtin_pwd(void);
int		builtin_env(char **envp);
int		builtin_echo(char **args);
int		builtin_cd(char **args, char **envp);
int		builtin_exit(char **args);
int		is_builtin(char *cmd);
int		exec_builtin(char **args, char **envp);

#endif
