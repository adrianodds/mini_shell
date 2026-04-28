/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:27:33 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 18:36:44 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
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

char	*read_shell_input(void);
void	handle_input(t_shell *shell, char *input);
char	*read_line_from_fd(int fd);
char	*reader_end(char *res, size_t len);
char	*reader_fail(char *res);
char	*reader_init(size_t *cap);
char	*create_heredoc_file(char *delimiter);

#endif
