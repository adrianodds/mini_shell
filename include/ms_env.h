/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:26:32 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 17:28:07 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H

# include "ms_types.h"

char		*get_env(t_shell *shell, const char *key);
void		set_env(t_shell *shell, const char *key, const char *value);
char		**copy_envp(char **envp);
char		*expand_variables(t_shell *shell, const char *str);
char		*remove_quotes(const char *str, int len, int i, int j);

#endif
