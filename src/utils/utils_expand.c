/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:27 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:57:04 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../include/ms_expand.h"

void	process_char(t_expand_ctx *ctx);

char	*expand_variables(t_shell *shell, const char *str)
{
	char			result[8192];
	t_expand_ctx	ctx;

	if (!str)
		return (NULL);
	ctx.shell = shell;
	ctx.str = str;
	ctx.i = 0;
	ctx.result = result;
	ctx.pos = 0;
	ctx.quotes[0] = 0;
	ctx.quotes[1] = 0;
	while (ctx.str[ctx.i] && ctx.pos < 8191)
		process_char(&ctx);
	ctx.result[ctx.pos] = '\0';
	return (ft_strdup(ctx.result));
}
