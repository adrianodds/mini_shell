#include "../minishell.h"

void	setup_pipes(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->next)
		return ;
	if (pipe(shell->pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	cmd->pipe_out = shell->pipe_fd[1];
	cmd->next->pipe_in = shell->pipe_fd[0];
	shell->last_pipe_out = shell->pipe_fd[1];
}

void	close_unused_pipes(t_shell *shell, t_cmd *commands, t_cmd *current_cmd)
{
	t_cmd	*cmd;

	cmd = commands;
	while (cmd)
	{
		if (cmd != current_cmd)
		{
			if (cmd->pipe_in != -1)
				close(cmd->pipe_in);
			if (cmd->pipe_out != -1)
				close(cmd->pipe_out);
		}
		cmd = cmd->next;
	}
	(void)shell;
}

void	close_pipes(t_shell *shell, t_cmd *commands)
{
	t_cmd	*current;

	current = commands;
	while (current)
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
		current = current->next;
	}
	(void)shell;
}

void	handle_redirections(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = -1;
		if (fd == -1 && redir->type != REDIR_HEREDOC)
		{
			perror(redir->file);
			exit(1);
		}
		if (redir->type == REDIR_IN && fd != -1)
			dup2(fd, STDIN_FILENO);
		else if ((redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			&& fd != -1)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
		redir = redir->next;
	}
	(void)shell;
}
