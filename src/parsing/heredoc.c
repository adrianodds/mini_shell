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


static char	*heredoc_write_loop(int fd, char *delimiter)
{
	char	*line;
	size_t	dlen;

	dlen = ft_strlen(delimiter);
	while (1)
	{
		line = read_line_from_fd(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, dlen) == 0 &&
			(line[dlen] == '\n' || line[dlen] == '\0'))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
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
