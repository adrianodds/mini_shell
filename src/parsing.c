#include "../minishell.h"

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static void	add_token(t_token **tokens, char *value, int len, int type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	new_token->value = ft_substr(value, 0, len);
	new_token->type = type;
	new_token->next = NULL;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

static void	add_word_token(t_token **tokens, char *start, char *end)
{
	if (end > start && !is_blank(*(end - 1)))
		add_token(tokens, start, end - start, TOKEN_WORD);
}

static void	handle_pipe_token(t_token **tokens, char **input, char **start)
{
	add_word_token(tokens, *start, *input);
	add_token(tokens, "|", 1, TOKEN_PIPE);
	*input += 1;
	*start = *input;
}

static void	handle_lt_token(t_token **tokens, char **input, char **start)
{
	add_word_token(tokens, *start, *input);
	if (*(*input + 1) == '<')
	{
		add_token(tokens, "<<", 2, TOKEN_HEREDOC);
		*input += 2;
	}
	else
	{
		add_token(tokens, "<", 1, TOKEN_REDIR_IN);
		*input += 1;
	}
	*start = *input;
}

static void	handle_gt_token(t_token **tokens, char **input, char **start)
{
	add_word_token(tokens, *start, *input);
	if (*(*input + 1) == '>')
	{
		add_token(tokens, ">>", 2, TOKEN_REDIR_APPEND);
		*input += 2;
	}
	else
	{
		add_token(tokens, ">", 1, TOKEN_REDIR_OUT);
		*input += 1;
	}
	*start = *input;
}

static int	handle_quote_state(int *in_quote, char *quote_char, char **input)
{
	if (!*in_quote && (**input == '\'' || **input == '"'))
	{
		*in_quote = 1;
		*quote_char = **input;
		(*input)++;
		return (1);
	}
	if (*in_quote && **input == *quote_char)
	{
		*in_quote = 0;
		(*input)++;
		return (1);
	}
	return (0);
}

static int	handle_special_token(t_token **tokens, char **input, char **start,
		int in_quote)
{
	if (in_quote)
		return (0);
	if (is_blank(**input))
		return (add_word_token(tokens, *start, *input), *start = ++(*input), 1);
	if (**input == '|')
		return (handle_pipe_token(tokens, input, start), 1);
	if (**input == '<')
		return (handle_lt_token(tokens, input, start), 1);
	if (**input == '>')
		return (handle_gt_token(tokens, input, start), 1);
	return (0);
}

t_token	*tokenize(t_shell *shell, char *input)
{
	t_token	*tokens;
	char	*start;
	int		in_quote;
	char	quote_char;

	tokens = NULL;
	start = input;
	in_quote = 0;
	quote_char = 0;
	while (*input)
	{
		if (handle_quote_state(&in_quote, &quote_char, &input))
			continue ;
		if (handle_special_token(&tokens, &input, &start, in_quote))
			continue ;
		input++;
	}
	add_word_token(&tokens, start, input);
	(void)shell;
	return (tokens);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * MAX_TOKENS);
	cmd->argc = 0;
	cmd->redirects = NULL;
	cmd->pipe_in = -1;
	cmd->pipe_out = -1;
	cmd->next = NULL;
	return (cmd);
}

static t_cmd	*ensure_current_cmd(t_cmd **commands, t_cmd **last, t_cmd *current)
{
	if (current)
		return (current);
	current = new_cmd();
	if (!*commands)
		*commands = current;
	else if (*last)
		(*last)->next = current;
	return (current);
}

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
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	new_redir->file = file;
	new_redir->type = type;
	new_redir->next = NULL;
	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		current = cmd->redirects;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

static void	parse_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens)
{
	t_token	*token_iter;
	char	*processed;
	char	*file;
	int		redir_type;

	token_iter = *tokens;
	redir_type = redir_type_from_token(token_iter->type);
	token_iter = token_iter->next;
	if (token_iter && token_iter->type == TOKEN_WORD)
	{
		processed = expand_variables(shell, token_iter->value);
		file = remove_quotes(processed);
		free(processed);
		add_redirection(cmd, file, redir_type);
		token_iter = token_iter->next;
	}
	*tokens = token_iter;
}

static void	handle_word_token(t_shell *shell, t_cmd *current, t_token **token_iter)
{
	char	*processed_value;
	char	*expanded_value;

	processed_value = expand_variables(shell, (*token_iter)->value);
	expanded_value = remove_quotes(processed_value);
	if (expanded_value && *expanded_value)
	{
		current->args[current->argc] = expanded_value;
		current->argc++;
	}
	else
		free(expanded_value);
	free(processed_value);
	*token_iter = (*token_iter)->next;
}

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

void	parse_input(t_shell *shell, char *input)
{
	shell->tokens = tokenize(shell, input);
	if (!shell->tokens)
		return ;
	shell->commands = parse_tokens(shell, shell->tokens);
}
