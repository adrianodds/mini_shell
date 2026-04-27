/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 16:48:41 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-10 16:48:41 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	val;

	p = ptr;
	val = value;
	i = 0;
	while (i != num)
	{
		p[i] = val;
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	char str[50] = "Adriano";
	printf("%s\n", ft_memset(str, 'Y', sizeof(str)));
}*/