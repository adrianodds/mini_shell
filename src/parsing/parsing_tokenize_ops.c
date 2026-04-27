#include "../../minishell.h"

void	add_token(t_token **tokens, char *value, int len, int type);

void	add_word_token(t_token **tokens, char *start, char *end)
{
	if (end > start && *(end - 1) != ' ' && *(end - 1) != '\t'
		&& *(end - 1) != '\n')
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

int	handle_special_token(t_token **tokens, char **input, char **start,
		int in_quote)
{
	if (in_quote)
		return (0);
	if (**input == ' ' || **input == '\t' || **input == '\n')
		return (add_word_token(tokens, *start, *input), *start = ++(*input), 1);
	if (**input == '|')
		return (handle_pipe_token(tokens, input, start), 1);
	if (**input == '<')
		return (handle_lt_token(tokens, input, start), 1);
	if (**input == '>')
		return (handle_gt_token(tokens, input, start), 1);
	return (0);
}
