/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-18 17:38:43 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-18 17:38:43 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char d)
{
	int	i;
	int	in_word;
	int	words;

	i = 0;
	in_word = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != d && !in_word)
		{
			in_word = 1;
			words++;
		}
		else if (s[i] == d && in_word)
			in_word = 0;
		i++;
	}
	return (words);
}

static char	**free_all(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static int	append_word(const char *s, char c, char **result, size_t *index)
{
	index[1] = index[0];
	while (s[index[1]] && s[index[1]] != c)
		index[1]++;
	result[index[2]] = ft_substr(s, index[0], index[1] - index[0]);
	if (!result[index[2]])
		return (0);
	index[2]++;
	index[0] = index[1];
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	index[3];

	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result || !s)
		return (NULL);
	ft_bzero(index, sizeof(index));
	while (s[index[0]])
	{
		if (s[index[0]] != c)
		{
			if (!append_word(s, c, result, index))
				return (free_all(result, index[2]));
		}
		else
			index[0]++;
	}
	result[index[2]] = NULL;
	return (result);
}
/*index[0] = initial_position; index[1] = final_position, \
index[2] = index_new_word
int	main(void)
{
	char **split = ft_split(" semper congue, euismod non, mi.", 'i');
	int	i = 0;

	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}

} */