/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:21:04 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 18:21:27 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define BUFFER_SIZE 4096

char	*reader_init(size_t *cap)
{
	char	*res;

	*cap = BUFFER_SIZE;
	res = malloc(*cap + 1);
	return (res);
}

char	*reader_fail(char *res)
{
	free(res);
	return (NULL);
}

char	*reader_end(char *res, size_t len)
{
	res[len] = '\0';
	return (res);
}
