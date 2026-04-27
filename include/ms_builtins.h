#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include "ms_types.h"

int			builtin_echo(t_shell *shell, t_cmd *cmd);
int			builtin_cd(t_shell *shell, t_cmd *cmd);
int			builtin_pwd(t_shell *shell, t_cmd *cmd);
int			builtin_export(t_shell *shell, t_cmd *cmd);
int			builtin_unset(t_shell *shell, t_cmd *cmd);
int			builtin_env(t_shell *shell, t_cmd *cmd);
int			builtin_exit(t_shell *shell, t_cmd *cmd);

#endif
