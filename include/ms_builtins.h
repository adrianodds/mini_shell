/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:26:29 by carmoliv          #+#    #+#             */
/*   Updated: 2026/06/20 17:50:11 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void		print_export(t_shell *shell);
char		*get_cd_path(t_shell *shell, t_cmd *cmd, int *is_oldpwd);

#endif
