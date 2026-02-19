/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:51:21 by carmoliv          #+#    #+#             */
/*   Updated: 2025/11/17 21:34:54 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Returns a set of words defined by the delimiter
static int	c_word(char const *s, char c)
{
	size_t	word;
	size_t	count;

	word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && word == 0)
		{
			word = 1;
			count++;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (count);
}

static size_t	word_len(const char *s, char c)
{
	char	*end;

	end = ft_strchr(s, c);
	if (end)
		return (end - s);
	else
		return (ft_strlen(s));
}

static int	sub_free(char **arr, int i, const char *s, size_t len)
{
	arr[i] = ft_substr(s, 0, len);
	if (!arr[i])
	{
		while (i--)
			free(arr[i]);
		free(arr);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	size_t	len;

	i = 0;
	arr = (char **)malloc((c_word(s, c) + 1) * sizeof(char *));
	if (!s || !arr)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			len = word_len(s, c);
			if (!sub_free(arr, i, s, len))
				return (NULL);
			i++;
			s += len;
		}
	}
	arr[i] = NULL;
	return (arr);
}
/* int	main(void)
{
	char **split = ft_split("test test1 test2 test3 ", ' ');
	int	i = 0;

	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}

} */