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

static void	exec_child_process(t_shell *shell, t_cmd *commands, t_cmd *current)
{
	t_redir	*redir;
	int		has_stdout_redirect;

	if (current->pipe_in != -1)
	{
		dup2(current->pipe_in, STDIN_FILENO);
		close(current->pipe_in);
	}
	handle_redirections(shell, current);
	if (current->pipe_out != -1)
	{
		redir = current->redirects;
		has_stdout_redirect = 0;
		while (redir)
		{
			if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
				has_stdout_redirect = 1;
			redir = redir->next;
		}
		if (!has_stdout_redirect)
		{
			dup2(current->pipe_out, STDOUT_FILENO);
			close(current->pipe_out);
		}
	}
	close_unused_pipes(shell, commands, current);
	if (is_builtin(current->args[0]))
	{
		handle_builtin(shell, current);
		exit(shell->exit_status);
	}
	execvp(current->args[0], current->args);
	if (errno == EACCES || errno == EISDIR)
	{
		perror(current->args[0]);
		exit(126);
	}
	perror(current->args[0]);
	exit(127);
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

void	execute_commands(t_shell *shell, t_cmd *commands)
{
	t_cmd	*current;
	pid_t	pid;
	pid_t	last_pid;
	int		cmd_count;

	if (!commands)
		return ;
	cmd_count = count_exec_cmds(commands);
	if (cmd_count == 0)
		return ;
	if (cmd_count == 1 && commands->argc > 0 && is_builtin(commands->args[0])
		&& !commands->redirects)
		return ((void)handle_builtin(shell, commands));
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
	wait_children(shell, last_pid);
}
