/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:38:52 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 18:38:53 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	redir_type_from_token(int token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

static void	add_redirection(t_cmd *cmd, char *file, int type)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->file = file;
	new->type = type;
	new->next = NULL;
	if (!cmd->redirects)
		cmd->redirects = new;
	else
	{
		tmp = cmd->redirects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static char	*get_redir_file(t_shell *shell, t_token *token, int type)
{
	char	*processed;
	char	*file;

	if (type == REDIR_HEREDOC)
	{
		processed = remove_quotes(token->value, 0, 0, 0);
		file = create_heredoc_file(processed);
		free(processed);
	}
	else
	{
		processed = expand_variables(shell, token->value);
		file = remove_quotes(processed, 0, 0, 0);
		free(processed);
	}
	return (file);
}

void	parse_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens)
{
	t_token	*cur;
	int		type;
	char	*file;

	cur = *tokens;
	type = redir_type_from_token(cur->type);
	cur = cur->next;
	if (cur && cur->type == TOKEN_WORD)
	{
		file = get_redir_file(shell, cur, type);
		add_redirection(cmd, file, type);
		cur = cur->next;
	}
	*tokens = cur;
}
