#include "../minishell.h"

char	*process_token_content(t_shell *shell, char *token_str, int quote_type)
{
	char	*result;
	int		len;
	int		i;
	int		j;
	char	quote_char;
	int		current_quote;

	if (!token_str || !*token_str)
		return (ft_strdup(""));
	
	len = ft_strlen(token_str) * 2;
	result = malloc(len + 1);
	i = 0;
	j = 0;
	
	while (token_str[i] && j < len)
	{
		current_quote = 0;
		if (token_str[i] == '"' || token_str[i] == '\'')
		{
			quote_char = token_str[i];
			current_quote = (quote_char == '\'') ? 1 : 2;
			i++;
			
			while (token_str[i] && token_str[i] != quote_char)
			{
				if (current_quote == 2 && token_str[i] == '$' && token_str[i + 1])
				{
					char var_name[256];
					int var_len = 0;
					char *var_value;
					
					i++;
					if (token_str[i] == '?')
					{
						var_value = ft_itoa(shell->exit_status);
						i++;
					}
					else
					{
						while (token_str[i] && (ft_isalnum(token_str[i]) || token_str[i] == '_') && var_len < 255)
							var_name[var_len++] = token_str[i++];
						var_name[var_len] = '\0';
						var_value = get_env_var(shell, var_name);
					}
					var_len = ft_strlen(var_value);
					if (j + var_len <= len)
					{
						ft_strcpy(result + j, var_value);
						j += var_len;
					}
					free(var_value);
				}
				else
				{
					result[j++] = token_str[i++];
				}
			}
			if (token_str[i])
				i++;
		}
		else if (token_str[i] == '$' && token_str[i + 1] && quote_type != 1)
		{
			char var_name[256];
			int var_len = 0;
			char *var_value;
			
			i++;
			if (token_str[i] == '?')
			{
				var_value = ft_itoa(shell->exit_status);
				i++;
			}
			else
			{
				while (token_str[i] && (ft_isalnum(token_str[i]) || token_str[i] == '_') && var_len < 255)
					var_name[var_len++] = token_str[i++];
				var_name[var_len] = '\0';
				var_value = get_env_var(shell, var_name);
			}
			var_len = ft_strlen(var_value);
			if (j + var_len <= len)
			{
				ft_strcpy(result + j, var_value);
				j += var_len;
			}
			free(var_value);
		}
		else
		{
			result[j++] = token_str[i++];
		}
	}
	result[j] = '\0';
	return (result);
}

char	*remove_quotes(char *str)
{
	int	dummy;
	return (remove_quotes_and_track(str, &dummy));
}

char	*get_env_var(t_shell *shell, char *var_name)
{
	int	i;
	int	len;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	i = 0;
	len = ft_strlen(var_name);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], var_name, len) == 0 
			&& shell->envp[i][len] == '=')
			return (ft_strdup(shell->envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_variables(t_shell *shell, char *str, int expand)
{
	if (!expand || !str || !*str)
		return (ft_strdup(str ? str : ""));
	return (process_token_content(shell, str, 0));
}

void	parse_input(t_shell *shell, char *input)
{
	shell->tokens = tokenize(shell, input);
	if (!shell->tokens)
		return ;
	shell->commands = parse_tokens(shell, shell->tokens);
}

char	*remove_quotes_and_track(char *str, int *has_single_quotes)
{
	char	*result;
	int		len;
	int		i;
	int		j;
	char	quote_char;

	if (!str || !*str)
	{
		*has_single_quotes = 0;
		return (ft_strdup(""));
	}
	len = ft_strlen(str);
	result = malloc(len + 1);
	i = 0;
	j = 0;
	*has_single_quotes = 0;
	while (i < len)
	{
		if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
		{
			quote_char = str[i];
			if (quote_char == '\'')
				*has_single_quotes = 1;
			i++;
			while (i < len && (str[i] != quote_char || (i > 0 && str[i - 1] == '\\')))
			{
				if (str[i] == '\\' && i + 1 < len && str[i + 1] == quote_char)
					i++;
				result[j++] = str[i++];
			}
			if (i < len)
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
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
			{
				char *raw_token = ft_strndup(start, input - start);
				char *processed_token = remove_quotes(raw_token);
				char *expanded_token = expand_variables(shell, processed_token, 1);
				add_token(&tokens, expanded_token, ft_strlen(expanded_token), TOKEN_WORD);
				free(raw_token);
				free(processed_token);
				free(expanded_token);
			}
			start = input + 1;
			input++;
		}
		else if (!in_quote && *input == '|')
		{
			if (input > start && *(input - 1) != ' ' && *(input - 1) != '\t' && *(input - 1) != '\n')
			{
				char *raw_token = ft_strndup(start, input - start);
				char *processed_token = remove_quotes(raw_token);
				char *expanded_token = expand_variables(shell, processed_token, 1);
				add_token(&tokens, expanded_token, ft_strlen(expanded_token), TOKEN_WORD);
				free(raw_token);
				free(processed_token);
				free(expanded_token);
			}
			add_token(&tokens, "|", 1, TOKEN_PIPE);
			start = input + 1;
			input++;
		}
		else if (!in_quote && *input == '<')
		{
			if (input > start && *(input - 1) != ' ' && *(input - 1) != '\t' && *(input - 1) != '\n')
			{
				char *raw_token = ft_strndup(start, input - start);
				char *processed_token = remove_quotes(raw_token);
				char *expanded_token = expand_variables(shell, processed_token, 1);
				add_token(&tokens, expanded_token, ft_strlen(expanded_token), TOKEN_WORD);
				free(raw_token);
				free(processed_token);
				free(expanded_token);
			}
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
			{
				char *raw_token = ft_strndup(start, input - start);
				char *processed_token = remove_quotes(raw_token);
				char *expanded_token = expand_variables(shell, processed_token, 1);
				add_token(&tokens, expanded_token, ft_strlen(expanded_token), TOKEN_WORD);
				free(raw_token);
				free(processed_token);
				free(expanded_token);
			}
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
	{
		char *raw_token = ft_strndup(start, input - start);
		char *processed_token = remove_quotes(raw_token);
		char *expanded_token = expand_variables(shell, processed_token, 1);
		add_token(&tokens, expanded_token, ft_strlen(expanded_token), TOKEN_WORD);
		free(raw_token);
		free(processed_token);
		free(expanded_token);
	}
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
			current->args[current->argc] = ft_strdup(token_iter->value);
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
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = ft_strdup(token_iter->value);
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
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = ft_strdup(token_iter->value);
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
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = ft_strdup(token_iter->value);
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
			new_redir = malloc(sizeof(t_redir));
			new_redir->file = ft_strdup(token_iter->value);
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
