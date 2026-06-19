/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:56 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:59:52 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void		parse_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens,
				int redir_type);
void		handle_word_token(t_shell *shell, t_cmd *current,
				t_token **token_iter);
t_cmd		*ensure_current_cmd(t_cmd **commands, t_cmd **last, t_cmd *current);

static int	is_redirection(int type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

static void	handle_pipe_separator(t_cmd **current, t_cmd **last,
		t_token **token_iter)
{
	if (*current)
		(*current)->args[(*current)->argc] = NULL;
	*last = *current;
	*current = NULL;
	*token_iter = (*token_iter)->next;
}

static int	validate_pipes(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!prev || prev->type == TOKEN_PIPE)
			{
				ft_putstr_fd("minishell: syntax error: pipe\n", 2);
				return (0);
			}
			if (!current->next || current->next->type == TOKEN_PIPE)
			{
				ft_putstr_fd("minishell: syntax error: pipe\n", 2);
				return (0);
			}
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

static void	handle_parse_token(t_parse_ctx *ctx)
{
	if ((*ctx->token_iter)->type == TOKEN_WORD)
	{
		*ctx->current = ensure_current_cmd(ctx->commands, ctx->last,
				*ctx->current);
		handle_word_token(ctx->shell, *ctx->current, ctx->token_iter);
	}
	else if (is_redirection((*ctx->token_iter)->type))
	{
		*ctx->current = ensure_current_cmd(ctx->commands, ctx->last,
				*ctx->current);
		parse_redirections(ctx->shell, *ctx->current, ctx->token_iter, 0);
	}
	else if ((*ctx->token_iter)->type == TOKEN_PIPE)
		handle_pipe_separator(ctx->current, ctx->last, ctx->token_iter);
	else
		*ctx->token_iter = (*ctx->token_iter)->next;
}

t_cmd	*parse_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd		*commands;
	t_cmd		*current;
	t_cmd		*last;
	t_token		*token_iter;
	t_parse_ctx	ctx;

	if (!validate_pipes(tokens))
		return (NULL);
	commands = NULL;
	current = NULL;
	last = NULL;
	token_iter = tokens;
	ctx.shell = shell;
	ctx.commands = &commands;
	ctx.current = &current;
	ctx.last = &last;
	ctx.token_iter = &token_iter;
	while (token_iter)
		handle_parse_token(&ctx);
	if (current)
		current->args[current->argc] = NULL;
	return (commands);
}
