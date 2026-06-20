/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:36 by adduarte          #+#    #+#             */
/*   Updated: 2026/06/20 15:08:21 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*alloc_remove_quotes(const char *str, int *len)
{
	char	*result;

	if (!str)
		return (NULL);
	*len = ft_strlen(str);
	result = malloc(*len + 1);
	return (result);
}

static void	process_char(const char *str, char *result, t_rq *ctx)
{
	if (!ctx->quote_char && (str[ctx->i] == '\'' || str[ctx->i] == '"'))
		ctx->quote_char = str[ctx->i++];
	else if (ctx->quote_char && str[ctx->i] == ctx->quote_char)
	{
		ctx->quote_char = 0;
		ctx->i++;
	}
	else if (ctx->quote_char == '"' && str[ctx->i] == '\\' && str[ctx->i + 1]
		&& (str[ctx->i + 1] == '"' || str[ctx->i + 1] == '\\' || str[ctx->i
				+ 1] == '$' || str[ctx->i + 1] == '`'))
	{
		ctx->i++;
		result[ctx->j++] = str[ctx->i++];
	}
	else
		result[ctx->j++] = str[ctx->i++];
}

char	*remove_quotes(const char *str, int len, int i, int j)
{
	char	*result;
	t_rq	ctx;

	(void)i;
	(void)j;
	result = alloc_remove_quotes(str, &len);
	if (!result)
		return (NULL);
	ctx.i = 0;
	ctx.j = 0;
	ctx.quote_char = 0;
	while (ctx.i < len)
		process_char(str, result, &ctx);
	result[ctx.j] = '\0';
	return (result);
}
