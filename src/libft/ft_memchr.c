/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-15 17:55:39 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-15 17:55:39 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*p;
	unsigned char			d;

	p = s;
	d = c;
	i = 0;
	while (i < n)
	{
		if (p[i] == d)
			return ((void *)&p[i]);
		i++;
	}
	return (0);
}

/* int	main(void) {
	char str[] = {1, 1, 2 ,3 ,4 ,5};

	char *result = (char *)(ft_memchr(str, 0, 1));

	if (result != 0) {
		printf("Caractere encontrado: %c\n", *result);
		printf("Posição: %ld\n", result - str);
	} else {
		printf("Caractere não encontrado.\n");
	}

	return (0);
} */