/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:11 by adduarte          #+#    #+#             */
/*   Updated: 2026/06/20 14:57:04 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		handle_quote_state(int *in_quote, char *quote_char, char **input);
int		handle_special_token(t_token **tokens, char **input, char **start,
			int in_quote);
void	add_word_token(t_token **tokens, char *start, char *end);

void	add_token(t_token **tokens, char *value, int len, int type)
{
	t_token	*new_token;
	t_token	*current;

	if (!value || len < 0)
		return ;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = malloc(len + 1);
	if (!new_token->value)
		return (free(new_token));
	ft_strlcpy(new_token->value, value, len + 1);
	new_token->type = type;
	new_token->next = NULL;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
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

static int	handle_backslash(t_quote *quote, char **input)
{
	if (**input == '\\' && (!quote->in_quote || quote->quote_char == '"'))
	{
		if (*(*input + 1))
			*input += 2;
		else
			(*input)++;
		return (1);
	}
	return (0);
}

static void	tokenize_loop(t_token **tokens, char **start,
			char **input, t_quote *quote)
{
	while (**input)
	{
		if (handle_backslash(quote, input))
			continue ;
		if (handle_quote_state(&quote->in_quote, &quote->quote_char, input))
			continue ;
		if (handle_special_token(tokens, input, start, quote->in_quote))
			continue ;
		(*input)++;
	}
}

t_token	*tokenize(t_shell *shell, char *input)
{
	t_token	*tokens;
	char	*start;
	t_quote	quote;

	(void)shell;
	tokens = NULL;
	start = input;
	quote.in_quote = 0;
	quote.quote_char = 0;
	tokenize_loop(&tokens, &start, &input, &quote);
	add_word_token(&tokens, start, input);
	if (quote.in_quote)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
