#ifndef MS_EXECUTION_H
# define MS_EXECUTION_H

# include "ms_types.h"

void		execute_commands(t_shell *shell, t_cmd *commands);
void		execute_single_cmd(t_shell *shell, t_cmd *cmd);
void		handle_builtin(t_shell *shell, t_cmd *cmd);
void		exec_child_process(t_shell *shell, t_cmd *commands, t_cmd *current);
int			is_builtin(const char *cmd);

void		setup_pipes(t_shell *shell, t_cmd *cmd);
void		close_pipes(t_shell *shell, t_cmd *commands);
void		close_unused_pipes(t_shell *shell, t_cmd *commands, t_cmd *current_cmd);
void		handle_redirections(t_shell *shell, t_cmd *cmd);

#endif
