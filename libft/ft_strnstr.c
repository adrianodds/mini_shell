/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:29:02 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 22:05:10 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Looks for the first occurrence of needle and returns the rest.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (0);
	while (i < len)
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			while (needle[j] && (i + j) < len && haystack[i + j] == needle[j])
			{
				if (haystack[i + j] != needle[j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
/* int	main(void)
{
	char	stack[] = "Hello";
	char	need[] = "ca";
	int	i = 6;

	char *result = ft_strnstr(stack, need, i);
	if (result)
		printf("Found %s\n", result);
	else
		printf("Not found %s", result);
	return (0);
} */