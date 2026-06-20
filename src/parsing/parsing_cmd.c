/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:51 by adduarte          #+#    #+#             */
/*   Updated: 2026/06/20 16:43:13 by adduarte         ###   ########.fr       */
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

static int	is_assignment(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	if (s[i] != '=')
		return (0);
	return (1);
}

static int	handle_assignment(t_shell *shell, t_cmd *current, char *expanded_value)
{
	char	*eq_pos;

	if (current->argc != 0 || !is_assignment(expanded_value))
		return (0);
	eq_pos = ft_strchr(expanded_value, '=');
	if (!eq_pos)
		return (0);
	*eq_pos = '\0';
	set_env(shell, expanded_value, eq_pos + 1);
	return (1);
}

void	handle_word_token(t_shell *shell, t_cmd *current, t_token **token_iter)
{
	char	*processed_value;
	char	*expanded_value;

	processed_value = expand_variables(shell, (*token_iter)->value);
	expanded_value = remove_quotes(processed_value, 0, 0, 0);
	if (expanded_value && *expanded_value)
	{
		if (handle_assignment(shell, current, expanded_value))
		{
			free(processed_value);
			free(expanded_value);
			*token_iter = (*token_iter)->next;
			return ;
		}
		current->args[current->argc] = expanded_value;
		current->argc++;
	}
	else
		free(expanded_value);
	free(processed_value);
	*token_iter = (*token_iter)->next;
}
