/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:48:25 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 22:38:29 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Move data and avoids overwriting
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d_dest;
	const unsigned char	*s_src;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d_dest = (unsigned char *)dest;
	s_src = (const unsigned char *)src;
	if (d_dest > s_src && d_dest < s_src + n)
	{
		i = n;
		while (i-- > 0)
			d_dest[i] = s_src[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d_dest[i] = s_src[i];
			i++;
		}
	}
	return (dest);
}
/*#include <stdio.h>

int	main(void)
{
	char	dest[40] = "Carmoliv";
	char	src[] = "test";
	size_t i = 4;

	ft_memmove(dest + 2, src, i);
	printf("%s \n", dest);
	return (0);
}*/