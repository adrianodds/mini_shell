/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:26:39 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 17:31:52 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXPAND_H
# define MS_EXPAND_H

# include "ms_types.h"

typedef struct s_expand_ctx
{
	t_shell		*shell;
	const char	*str;
	int			i;
	char		*result;
	int			pos;
	int			quotes[2];
}	t_expand_ctx;

int			handle_dollar(t_expand_ctx *ctx, char *tmp);
int			copy_expanded(char *result, char *tmp, int j);
void		process_char(t_expand_ctx *ctx);

#endif
