/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 21:27:12 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-10 21:27:12 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (!size)
		return (j);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (j);
}

/*int	main(void)
{
	char str1[] = "Hello, World!";
	char str11[] = "Hello, World!";
	char str2[10];
	char str3[10];

	printf("%d\n",ft_strlcpy(str3, str1, 15));
	printf("%d\n", strlcpy(str2, str11, 15));
	printf("ft_strlcpy: %s\n", str3);
	printf("strlcpy: %s\n", str2);
}*/