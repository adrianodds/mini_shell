/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:21:07 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 18:21:24 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define BUFFER_SIZE 4096

static int	read_into_buffer(int fd, char *buffer,
	size_t *pos, ssize_t *bytes)
{
	*bytes = read(fd, buffer, BUFFER_SIZE);
	*pos = 0;
	if (*bytes < 0)
		return (-1);
	return (*bytes);
}

static int	process_char(t_reader *r, char c)
{
	char	*tmp;

	if (r->len >= r->cap)
	{
		r->cap *= 2;
		tmp = malloc(r->cap + 1);
		if (!tmp)
			return (0);
		ft_memcpy(tmp, r->res, r->len);
		free(r->res);
		r->res = tmp;
	}
	r->res[r->len++] = c;
	return (1);
}

static char	*handle_read_end(t_reader *r, ssize_t bytes)
{
	if (bytes < 0)
		return (reader_fail(r->res));
	if (r->len == 0)
		return (reader_fail(r->res));
	return (reader_end(r->res, r->len));
}

char	*read_line_from_fd(int fd)
{
	static char		buffer[BUFFER_SIZE];
	static size_t	pos;
	static ssize_t	bytes;
	t_reader		r;

	r.res = reader_init(&r.cap);
	if (!r.res)
		return (NULL);
	r.len = 0;
	while (1)
	{
		if (pos >= (size_t)bytes)
		{
			bytes = read_into_buffer(fd, buffer, &pos, &bytes);
			if (bytes <= 0)
				return (handle_read_end(&r, bytes));
		}
		if (!process_char(&r, buffer[pos]))
			return (reader_fail(r.res));
		if (buffer[pos++] == '\n')
			return (reader_end(r.res, r.len));
	}
}
