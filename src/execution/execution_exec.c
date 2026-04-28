/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:14 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:15:15 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*resolve_executable(t_shell *shell, char *cmd);

void	close_current_pipes(t_cmd *current)
{
	if (current->pipe_in != -1)
	{
		close(current->pipe_in);
		current->pipe_in = -1;
	}
	if (current->pipe_out != -1)
	{
		close(current->pipe_out);
		current->pipe_out = -1;
	}
}

static int	has_stdout_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static void	set_pipe_output(t_cmd *current)
{
	if (current->pipe_out != -1 && !has_stdout_redir(current->redirects))
	{
		dup2(current->pipe_out, STDOUT_FILENO);
		close(current->pipe_out);
	}
}

static void	exec_external(t_shell *shell, t_cmd *current)
{
	char	*path;

	path = resolve_executable(shell, current->args[0]);
	if (!path)
	{
		printf("minishell: %s: command not found\n", current->args[0]);
		exit(127);
	}
	execve(path, current->args, shell->envp);
	free(path);
	if (errno == EACCES || errno == EISDIR)
	{
		perror(current->args[0]);
		exit(126);
	}
	perror(current->args[0]);
	exit(127);
}

void	exec_child_process(t_shell *shell, t_cmd *commands, t_cmd *current)
{
	if (current->pipe_in != -1)
	{
		dup2(current->pipe_in, STDIN_FILENO);
		close(current->pipe_in);
	}
	handle_redirections(shell, current);
	set_pipe_output(current);
	close_unused_pipes(shell, commands, current);
	if (is_builtin(current->args[0]))
	{
		handle_builtin(shell, current);
		exit(shell->exit_status);
	}
	exec_external(shell, current);
}
