/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:16:36 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 14:49:38 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*alloc_remove_quotes(const char *str, int *len)
{
	char	*result;

	if (!str)
		return (NULL);
	*len = ft_strlen(str);
	result = malloc(*len + 1);
	return (result);
}

char	*remove_quotes(const char *str, int len, int i, int j)
{
	char	*result;
	char	quote_char;

	result = alloc_remove_quotes(str, &len);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote_char = 0;
	while (i < len)
	{
		if (!quote_char && (str[i] == '\'' || str[i] == '"'))
			quote_char = str[i++];
		else if (quote_char && str[i] == quote_char)
		{
			quote_char = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	return (result[j] = '\0', result);
}
