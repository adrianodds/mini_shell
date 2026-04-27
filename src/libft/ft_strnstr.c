/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 15:58:38 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-16 15:58:38 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j] && (i + j) < len && big[i
				+ j] == little[j])
			j++;
		if (j == len_little)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/* int	main(void) {
	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";
	char * empty = (char*)"";
	if (ft_strnstr(haystack, needle, -1) != NULL) {
		printf("Substring encontrada: %s\n", ft_strnstr(haystack, needle, -1));
	} else {
		printf("Substring não encontrada.\n");
	}

	return (0);
} */