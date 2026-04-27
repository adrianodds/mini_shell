/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 19:05:31 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-10 19:05:31 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *str, size_t num)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*d;

	p = dest;
	d = (unsigned char *)str;
	i = 0;
	if (!dest && !str)
		return (NULL);
	while (i < num)
	{
		p[i] = d[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char dest[50];
	char str[] = "Adriano";
	ft_memcpy(dest, str, 9);
	//memcpy(dest, str, 9);
	printf("%s\n", dest);
}*/