#include "../../minishell.h"

void	parse_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens);
void	handle_word_token(t_shell *shell, t_cmd *current, t_token **token_iter);
t_cmd	*ensure_current_cmd(t_cmd **commands, t_cmd **last, t_cmd *current);

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

static void	handle_parse_token(t_shell *shell, t_cmd **commands,
		t_cmd **current, t_cmd **last, t_token **token_iter)
{
	if ((*token_iter)->type == TOKEN_WORD)
	{
		*current = ensure_current_cmd(commands, last, *current);
		handle_word_token(shell, *current, token_iter);
	}
	else if (is_redirection((*token_iter)->type))
	{
		*current = ensure_current_cmd(commands, last, *current);
		parse_redirections(shell, *current, token_iter);
	}
	else if ((*token_iter)->type == TOKEN_PIPE)
		handle_pipe_separator(current, last, token_iter);
	else
		*token_iter = (*token_iter)->next;
}

t_cmd	*parse_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*current;
	t_cmd	*last;
	t_token	*token_iter;

	commands = NULL;
	current = NULL;
	last = NULL;
	token_iter = tokens;
	while (token_iter)
		handle_parse_token(shell, &commands, &current, &last, &token_iter);
	if (current)
		current->args[current->argc] = NULL;
	return (commands);
}
