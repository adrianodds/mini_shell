/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:00 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:46:49 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*heredoc_tmp_name(void)
{
	static int	counter;
	char		*num;
	char		*name;
	char		*tmp;

	num = ft_itoa(counter++);
	tmp = ft_strjoin("/tmp/minishell_hd_", num);
	free(num);
	name = ft_strjoin(tmp, ".tmp");
	free(tmp);
	return (name);
}

static char	*create_heredoc_file(char *delimiter)
{
	char	*name;
	char	*line;
	int		fd;
	size_t	cap;

	name = heredoc_tmp_name();
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	line = NULL;
	cap = 0;
	while (getline(&line, &cap, stdin) != -1)
	{
		if ((line[ft_strlen(line) - 1] == '\n' && ft_strncmp(line, delimiter,
					ft_strlen(line) - 1) == 0
				&& ft_strlen(delimiter) == ft_strlen(line) - 1)
			|| ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
	}
	free(line);
	close(fd);
	return (name);
}

static int	redir_type_from_token(int token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

static void	add_redirection(t_cmd *cmd, char *file, int type)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	new_redir->file = file;
	new_redir->type = type;
	new_redir->next = NULL;
	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		current = cmd->redirects;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

void	parse_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens,
		int redir_type)
{
	t_token	*token_iter;
	char	*processed;
	char	*file;

	token_iter = *tokens;
	redir_type = redir_type_from_token(token_iter->type);
	token_iter = token_iter->next;
	if (token_iter && token_iter->type == TOKEN_WORD)
	{
		if (redir_type == REDIR_HEREDOC)
		{
			processed = remove_quotes(token_iter->value, 0, 0, 0);
			file = create_heredoc_file(processed);
			free(processed);
		}
		else
		{
			processed = expand_variables(shell, token_iter->value);
			file = remove_quotes(processed, 0, 0, 0);
			free(processed);
		}
		add_redirection(cmd, file, redir_type);
		token_iter = token_iter->next;
	}
	*tokens = token_iter;
}
