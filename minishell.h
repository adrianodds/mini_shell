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

/**************EXEC***************/
void	exec_line(char *line, char **envp);

/***************Utils*************/
void	free_args(char **args);

/****************Path*************/
char	*get_path(char **envp);
char	*find_cmd_path(char *cmd, char **envp);

#endif
