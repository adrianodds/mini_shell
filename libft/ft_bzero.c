/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:20:13 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/03 16:50:11 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function to reset a memory block byte by byte.
void	ft_bzero(void *s, size_t len)
{
	unsigned char	*n;
	size_t			i;

	i = 0;
	n = (unsigned char *)s;
	while (i < len)
	{
		n[i] = 0;
		i++;
	}
}
/* #include <stdio.h>
int	main(void)
{
	char	name[] = "Carmoliv";
	ft_bzero(name, 8);
	printf("%s \n",name);
} */