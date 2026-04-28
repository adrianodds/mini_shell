/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:51 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:46:02 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*new_cmd(void)
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

t_cmd	*ensure_current_cmd(t_cmd **commands, t_cmd **last, t_cmd *current)
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

void	handle_word_token(t_shell *shell, t_cmd *current, t_token **token_iter)
{
	char	*processed_value;
	char	*expanded_value;

	processed_value = expand_variables(shell, (*token_iter)->value);
	expanded_value = remove_quotes(processed_value, 0, 0, 0);
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
