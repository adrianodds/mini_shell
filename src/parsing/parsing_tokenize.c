/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:11 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 19:26:25 by adduarte         ###   ########.fr       */
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
