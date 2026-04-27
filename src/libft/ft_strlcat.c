/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-15 13:32:28 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-15 13:32:28 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	leng_dst;
	unsigned int	leng_src;
	size_t			i;

	i = 0;
	leng_dst = ft_strlen(dst);
	leng_src = ft_strlen(src);
	if (size == 0)
		return (leng_src);
	else if (size <= leng_dst)
		return (leng_src + size);
	while ((i < (size - leng_dst - 1)) && (src[i] != 0))
	{
		dst[leng_dst + i] = src[i];
		i++;
	}
	dst[leng_dst + i] = 0;
	return (leng_dst + leng_src);
}

/*int	main(void)
{
	char str1[] = "Hello!";
	char str2[] = "Hello!";
	char dest1[10] = "Adriano";
	char dest2[10] = "Adriano";

	printf("%d\n",ft_strlcat(dest2, str1, sizeof(dest2)));
	printf("%d\n", strlcat(dest1, str2, sizeof(dest1)));
	printf("ft_strlcat: %s\n", dest2);
	printf("strlcat: %s\n", dest1);
}*/