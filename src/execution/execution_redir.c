/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:15:30 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:15:31 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_redir_fd(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == REDIR_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (redir->type == REDIR_HEREDOC)
		return (open(redir->file, O_RDONLY));
	return (-1);
}

static void	apply_redir_fd(t_redir *redir, int fd)
{
	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		dup2(fd, STDOUT_FILENO);
}

void	handle_redirections(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirects;
	while (redir)
	{
		fd = open_redir_fd(redir);
		if (fd == -1)
		{
			perror(redir->file);
			exit(1);
		}
		apply_redir_fd(redir, fd);
		close(fd);
		if (redir->type == REDIR_HEREDOC)
			unlink(redir->file);
		redir = redir->next;
	}
	(void)shell;
}
