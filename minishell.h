#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "src/libft/libft.h"

# include "include/ms_types.h"
# include "include/ms_parsing.h"
# include "include/ms_execution.h"
# include "include/ms_builtins.h"
# include "include/ms_env.h"
# include "include/ms_utils.h"
# include "include/ms_signals.h"

#endif
