#include "../../minishell.h"

int		handle_quote_state(int *in_quote, char *quote_char, char **input);
int		handle_special_token(t_token **tokens, char **input, char **start,
			int in_quote);
void	add_word_token(t_token **tokens, char *start, char *end);

void	add_token(t_token **tokens, char *value, int len, int type)
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

int	handle_quote_state(int *in_quote, char *quote_char, char **input)
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

t_token	*tokenize(t_shell *shell, char *input)
{
	t_token	*tokens;
	char	*start;
	int		in_quote;
	char	quote_char;

	(void)shell;
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
	return (tokens);
}
