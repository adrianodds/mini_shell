/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:31 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 19:44:13 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

static void	free_redirections(t_redir *redir)
{
	t_redir	*next_redir;

	while (redir)
	{
		next_redir = redir->next;
		free(redir->file);
		free(redir);
		redir = next_redir;
	}
}

static void	free_cmd_args(t_cmd *current)
{
	int	i;

	i = 0;
	while (current->args[i])
		free(current->args[i++]);
	free(current->args);
}

void	free_commands(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		free_cmd_args(current);
		free_redirections(current->redirects);
		free(current);
		current = next;
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		free(shell->envp[i++]);
	free(shell->envp);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->commands)
		free_commands(shell->commands);
}
