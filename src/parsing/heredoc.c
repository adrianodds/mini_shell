/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:39:03 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 18:39:15 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*heredoc_tmp_name(void)
{
	static int	counter;
	char		*num;
	char		*tmp;
	char		*name;

	num = ft_itoa(counter++);
	tmp = ft_strjoin("/tmp/minishell_hd_", num);
	free(num);
	name = ft_strjoin(tmp, ".tmp");
	free(tmp);
	return (name);
}

static int	is_delimiter(char *line, char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, len) == 0
		&& line[len] == '\n')
		return (1);
	return (0);
}

static int	handle_line_flush(char *line, size_t len, int fd, char *delimiter)
{
	line[len] = '\0';
	if (is_delimiter(line, delimiter))
	{
		free(line);
		return (0);
	}
	write(fd, line, len);
	return (1);
}

static char	*heredoc_write_loop(int fd, char *delimiter)
{
	char	buffer[4096];
	char	*line;
	size_t	len;
	ssize_t	bytes;

	line = malloc(4096);
	if (!line)
		return (NULL);
	len = 0;
	bytes = read(STDIN_FILENO, buffer, 4096);
	while (bytes > 0)
	{
		if (len + 1 >= 4096)
			return (free(line), NULL);
		line[len++] = buffer[0];
		if (buffer[0] == '\n')
		{
			if (!handle_line_flush(line, len, fd, delimiter))
				return (NULL);
			len = 0;
		}
		bytes = read(STDIN_FILENO, buffer, 4096);
	}
	free(line);
	return (NULL);
}

char	*create_heredoc_file(char *delimiter)
{
	char	*name;
	int		fd;

	name = heredoc_tmp_name();
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (free(name), NULL);
	heredoc_write_loop(fd, delimiter);
	close(fd);
	return (name);
}
