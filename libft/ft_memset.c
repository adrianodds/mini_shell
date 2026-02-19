/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:38:19 by carmoliv          #+#    #+#             */
/*   Updated: 2025/04/13 12:30:10 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Fill a block of memory with a value specific
void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*pt;

	i = 0;
	pt = (unsigned char *)ptr;
	while (i < num)
	{
		pt[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
/*#include <stdio.h>
int	main(void)
{
	char	name[40] = "Carmelo";
	ft_memset(name, 'i', 2);
	printf("%s \n", name);
	return (0);
}*/