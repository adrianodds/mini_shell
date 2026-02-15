/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:07:04 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 22:37:12 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function copies n bytes of memory from src to dest
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d_dest;
	const unsigned char	*s_src;

	if (!dest && !src)
		return (0);
	d_dest = (unsigned char *)dest;
	s_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d_dest[i] = s_src[i];
		i++;
	}
	return (dest);
}
/* #include <stdio.h>

int	main(void)
{
	char	name1[40] = "";
	char	name2[] = "Oliveira";
	size_t value = 3;

	ft_memcpy(name1, name2, value);
	printf("%s \n", name1);
	return (0);
} */