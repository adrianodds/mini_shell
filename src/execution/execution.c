/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:37 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 15:24:32 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static pid_t	spawn_commands(t_shell *shell, t_cmd *commands);
void			close_current_pipes(t_cmd *current);

static int	count_exec_cmds(t_cmd *commands)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = commands;
	while (current)
	{
		if (current->argc > 0)
			count++;
		current = current->next;
	}
	return (count);
}

static void	wait_children(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	waited_pid;

	while (1)
	{
		waited_pid = wait(&status);
		if (waited_pid <= 0)
			break ;
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
	}
}

static int	handle_single_builtin(t_shell *shell, t_cmd *commands,
		int cmd_count)
{
	if (cmd_count == 1 && commands->argc > 0
		&& ft_strncmp(commands->args[0], "exit", 5) == 0)
	{
		handle_builtin(shell, commands);
		exit(shell->exit_status);
	}
	if (cmd_count == 1 && commands->argc > 0 && is_builtin(commands->args[0])
		&& !commands->redirects)
	{
		handle_builtin(shell, commands);
		return (1);
	}
	return (0);
}

void	execute_commands(t_shell *shell, t_cmd *commands)
{
	int		cmd_count;
	pid_t	last_pid;

	if (!commands)
		return ;
	cmd_count = count_exec_cmds(commands);
	if (cmd_count == 0)
		return ;
	if (handle_single_builtin(shell, commands, cmd_count))
		return ;
	last_pid = spawn_commands(shell, commands);
	wait_children(shell, last_pid);
}

static pid_t	spawn_commands(t_shell *shell, t_cmd *commands)
{
	t_cmd	*current;
	pid_t	pid;
	pid_t	last_pid;

	current = commands;
	last_pid = -1;

	 while (current)
	{
		if (current->argc > 0)
		{
			setup_pipes(shell, current);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				exec_child_process(shell, commands, current);
			}
			if (pid > 0)
				last_pid = pid;
		}
		close_current_pipes(current);
		current = current->next;
	}

	return (last_pid);
}
