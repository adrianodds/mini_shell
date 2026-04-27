/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 18:02:24 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-10 18:02:24 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *ptr, size_t num)
{
	size_t			i;
	unsigned char	*p;

	p = ptr;
	i = 0;
	while (i != num)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}