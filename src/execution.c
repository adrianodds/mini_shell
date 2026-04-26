#include "../minishell.h"

void	execute_commands(t_shell *shell, t_cmd *commands)
{
	t_cmd	*current;
	int		cmd_count;
	int		i;
	int		status;

	if (!commands)
		return ;
	cmd_count = 0;
	current = commands;
	while (current)
	{
		cmd_count++;
		current = current->next;
	}
	if (cmd_count == 1 && is_builtin(commands->args[0]) && !commands->redirects)
	{
		handle_builtin(shell, commands);
		return ;
	}
	current = commands;
	i = 0;
	while (current)
	{
		setup_pipes(shell, current);
		if (fork() == 0)
		{
			if (current->pipe_in != -1)
			{
				dup2(current->pipe_in, STDIN_FILENO);
				close(current->pipe_in);
			}
			handle_redirections(shell, current);
			if (current->pipe_out != -1)
			{
				t_redir *redir = current->redirects;
				int has_stdout_redirect = 0;
				while (redir)
				{
					if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
					{
						has_stdout_redirect = 1;
						break;
					}
					redir = redir->next;
				}
				if (!has_stdout_redirect)
				{
					dup2(current->pipe_out, STDOUT_FILENO);
					close(current->pipe_out);
				}
			}
			if (is_builtin(current->args[0]))
			{
				handle_builtin(shell, current);
				exit(shell->exit_status);
			}
			execvp(current->args[0], current->args);
			perror(current->args[0]);
			exit(127);
		}
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
		i++;
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}

void	setup_pipes(t_shell *shell, t_cmd *cmd)
{
	if (cmd->next)
	{
		if (shell->last_pipe_out != -1)
			close(shell->last_pipe_out);
		if (pipe(shell->pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		cmd->pipe_out = shell->pipe_fd[1];
		cmd->next->pipe_in = shell->pipe_fd[0];
		shell->last_pipe_out = shell->pipe_fd[1];
	}
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
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				perror(redir->file);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(redir->file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(redir->file);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	(void)shell;
}

void	handle_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		shell->exit_status = builtin_echo(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		shell->exit_status = builtin_cd(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		shell->exit_status = builtin_pwd(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		shell->exit_status = builtin_export(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		shell->exit_status = builtin_unset(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		shell->exit_status = builtin_env(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(shell, cmd);
}

int	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
