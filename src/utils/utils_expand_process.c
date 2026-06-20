/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:10:00 by adduarte          #+#    #+#             */
/*   Updated: 2026/06/20 15:03:44 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../include/ms_expand.h"

static void	handle_var(t_expand_ctx *ctx)
{
	char	tmp[8192];
	int		k;

	k = handle_dollar(ctx, tmp);
	if (k == -1 && ctx->pos < 8191)
		ctx->result[ctx->pos++] = '$';
	else if (k >= 0)
	{
		tmp[k] = '\0';
		ctx->pos = copy_expanded(ctx->result, tmp, ctx->pos);
	}
}

static void	handle_quote(t_expand_ctx *ctx, char quote)
{
	ctx->result[ctx->pos++] = ctx->str[ctx->i++];
	if (quote == '"')
		ctx->quotes[0] = !ctx->quotes[0];
	else
		ctx->quotes[1] = !ctx->quotes[1];
}

static void	put_char(t_expand_ctx *ctx, char c)
{
	if (ctx->pos < 8191)
		ctx->result[ctx->pos++] = c;
}

static void	handle_escape(t_expand_ctx *ctx)
{
	ctx->i++;
	if (!ctx->str[ctx->i])
	{
		put_char(ctx, '\\');
		return ;
	}
	if (ctx->str[ctx->i] == '$' || ctx->str[ctx->i] == '"'
		|| ctx->str[ctx->i] == '\\' || ctx->str[ctx->i] == '`')
	{
		if (ctx->quotes[0] && ctx->str[ctx->i] == '"')
			put_char(ctx, '\\');
		put_char(ctx, ctx->str[ctx->i++]);
	}
	else
	{
		put_char(ctx, '\\');
		put_char(ctx, ctx->str[ctx->i++]);
	}
}

void	process_char(t_expand_ctx *ctx)
{
	if (ctx->str[ctx->i] == '"' && !ctx->quotes[1])
		handle_quote(ctx, '"');
	else if (ctx->str[ctx->i] == '\'' && !ctx->quotes[0])
		handle_quote(ctx, '\'');
	else if (ctx->str[ctx->i] == '\\' && !ctx->quotes[1])
		handle_escape(ctx);
	else if (ctx->str[ctx->i] == '$' && !ctx->quotes[1])
		handle_var(ctx);
	else
		ctx->result[ctx->pos++] = ctx->str[ctx->i++];
}
