/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 19:35:17 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-10 19:35:17 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 19:05:31 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-10 19:05:31 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_reverse(void *dest, const void *str, unsigned int num)
{
	unsigned char		*p;
	const unsigned char	*s = str;
	unsigned int		i;

	p = dest;
	i = num;
	while (i > 0)
	{
		p[i - 1] = s[i - 1];
		i--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *str, size_t num)
{
	unsigned char		*p;
	const unsigned char	*s = str;

	p = dest;
	if (!dest && !str)
		return (NULL);
	if (p < s || p >= (s + num))
	{
		return (ft_memcpy(dest, str, num));
	}
	else
	{
		return (ft_memcpy_reverse(dest, str, num));
	}
}
/*(p < s) checks whether the start of "dest" occurs before the start of "str",\
 or if (p >= (s + num) the start of "dest" occurs after the end of "str". \
 Thus ensuring that there will be no memory overlap at the time of copying.*/
/*
int	main(void)
{
	char dest[50];
	char str[] = "abcde";
	ft_memmove(str+1, str, 3);
	//memmove(str+1, str, 0);
	printf("%s\n", str);
}*/