#include "../minishell.h"

void	parse_input(t_shell *shell, char *input)
{
	shell->tokens = tokenize(shell, input);
	if (!shell->tokens)
		return ;
	shell->commands = parse_tokens(shell, shell->tokens);
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
		if (!in_quote && (*input == '\'' || *input == '"'))
		{
			in_quote = 1;
			quote_char = *input;
			input++;
		}
		else if (in_quote && *input == quote_char)
		{
			in_quote = 0;
			input++;
		}
		else if (!in_quote && (*input == ' ' || *input == '\t' || *input == '\n'))
		{
			if (input > start && *(input - 1) != ' ' && *(input - 1) != '\t' && *(input - 1) != '\n')
				add_token(&tokens, start, input - start, TOKEN_WORD);
			start = input + 1;
			input++;
		}
		else if (!in_quote && *input == '|')
		{
			if (input > start && *(input - 1) != ' ' && *(input - 1) != '\t' && *(input - 1) != '\n')
				add_token(&tokens, start, input - start, TOKEN_WORD);
			add_token(&tokens, "|", 1, TOKEN_PIPE);
			start = input + 1;
			input++;
		}
		else if (!in_quote && *input == '<')
		{
			if (input > start && *(input - 1) != ' ' && *(input - 1) != '\t' && *(input - 1) != '\n')
				add_token(&tokens, start, input - start, TOKEN_WORD);
			if (*(input + 1) == '<')
			{
				add_token(&tokens, "<<", 2, TOKEN_HEREDOC);
				input += 2;
			}
			else
			{
				add_token(&tokens, "<", 1, TOKEN_REDIR_IN);
				input++;
			}
			start = input;
		}
		else if (!in_quote && *input == '>')
		{
			if (input > start && *(input - 1) != ' ' && *(input - 1) != '\t' && *(input - 1) != '\n')
				add_token(&tokens, start, input - start, TOKEN_WORD);
			if (*(input + 1) == '>')
			{
				add_token(&tokens, ">>", 2, TOKEN_REDIR_APPEND);
				input += 2;
			}
			else
			{
				add_token(&tokens, ">", 1, TOKEN_REDIR_OUT);
				input++;
			}
			start = input;
		}
		else
			input++;
	}
	if (input > start && *start)
		add_token(&tokens, start, input - start, TOKEN_WORD);
	return (tokens);
	(void)shell;
}

void	add_token(t_token **tokens, char *value, int len, int type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	new_token->value = ft_strndup(value, len);
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

t_cmd	*parse_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*current;
	t_cmd	*last;
	t_token	*token_iter;
	char	*processed_value;
	char	*expanded_value;

	commands = NULL;
	current = NULL;
	last = NULL;
	token_iter = tokens;
	while (token_iter)
	{
		if (token_iter->type == TOKEN_WORD)
		{
			if (!current)
			{
				current = malloc(sizeof(t_cmd));
				current->args = malloc(sizeof(char *) * MAX_TOKENS);
				current->argc = 0;
				current->redirects = NULL;
				current->pipe_in = -1;
				current->pipe_out = -1;
				current->next = NULL;
				if (!commands)
					commands = current;
				else if (last)
					last->next = current;
			}
			processed_value = expand_variables(shell, token_iter->value);
			expanded_value = remove_quotes(processed_value);
			current->args[current->argc] = expanded_value;
			free(processed_value);
			current->argc++;
			token_iter = token_iter->next;
		}
		else if (token_iter->type == TOKEN_REDIR_IN 
			|| token_iter->type == TOKEN_REDIR_OUT 
			|| token_iter->type == TOKEN_REDIR_APPEND 
			|| token_iter->type == TOKEN_HEREDOC)
		{
			if (!current)
			{
				current = malloc(sizeof(t_cmd));
				current->args = malloc(sizeof(char *) * MAX_TOKENS);
				current->argc = 0;
				current->redirects = NULL;
				current->pipe_in = -1;
				current->pipe_out = -1;
				current->next = NULL;
				if (!commands)
					commands = current;
				else if (last)
					last->next = current;
			}
			parse_redirections(shell, current, &token_iter);
		}
		else if (token_iter->type == TOKEN_PIPE)
		{
			if (current)
				current->args[current->argc] = NULL;
			last = current;
			token_iter = token_iter->next;
			current = NULL;
		}
		else
			token_iter = token_iter->next;
	}
	if (current)
		current->args[current->argc] = NULL;
	return (commands);
}

void	parse_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens)
{
	t_redir	*new_redir;
	t_redir	*current;
	t_token	*token_iter;

	token_iter = *tokens;
	if (token_iter->type == TOKEN_REDIR_IN)
	{
		token_iter = token_iter->next;
		if (token_iter && token_iter->type == TOKEN_WORD)
		{
			char *processed = expand_variables(shell, token_iter->value);
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = remove_quotes(processed);
			free(processed);
			new_redir->type = REDIR_IN;
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
			token_iter = token_iter->next;
		}
	}
	else if (token_iter->type == TOKEN_REDIR_OUT)
	{
		token_iter = token_iter->next;
		if (token_iter && token_iter->type == TOKEN_WORD)
		{
			char *processed = expand_variables(shell, token_iter->value);
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = remove_quotes(processed);
			free(processed);
			new_redir->type = REDIR_OUT;
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
			token_iter = token_iter->next;
		}
	}
	else if (token_iter->type == TOKEN_REDIR_APPEND)
	{
		token_iter = token_iter->next;
		if (token_iter && token_iter->type == TOKEN_WORD)
		{
			char *processed = expand_variables(shell, token_iter->value);
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = remove_quotes(processed);
			free(processed);
			new_redir->type = REDIR_APPEND;
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
			token_iter = token_iter->next;
		}
	}
	else if (token_iter->type == TOKEN_HEREDOC)
	{
		token_iter = token_iter->next;
		if (token_iter && token_iter->type == TOKEN_WORD)
		{
			char *processed = expand_variables(shell, token_iter->value);
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = remove_quotes(processed);
			free(processed);
			new_redir->type = REDIR_HEREDOC;
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
			token_iter = token_iter->next;
		}
	}
	*tokens = token_iter;
	(void)shell;
}
