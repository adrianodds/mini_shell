#include "../minishell.h"

static int	count_exec_cmds(t_cmd *commands)
{
	int	count;
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

static void	close_current_pipes(t_cmd *current)
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

static void	exec_external(t_cmd *current)
{
	execvp(current->args[0], current->args);
	if (errno == EACCES || errno == EISDIR)
	{
		perror(current->args[0]);
		exit(126);
	}
	perror(current->args[0]);
	exit(127);
}

static void	exec_child_process(t_shell *shell, t_cmd *commands, t_cmd *current)
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
	exec_external(current);
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
		if (waited_pid == last_pid && WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}

static int	handle_single_builtin(t_shell *shell, t_cmd *commands, int cmd_count)
{
	if (cmd_count == 1 && commands->argc > 0 && is_builtin(commands->args[0])
		&& !commands->redirects)
	{
		handle_builtin(shell, commands);
		return (1);
	}
	return (0);
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
				exec_child_process(shell, commands, current);
			if (pid > 0)
				last_pid = pid;
		}
		close_current_pipes(current);
		current = current->next;
	}
	return (last_pid);
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
