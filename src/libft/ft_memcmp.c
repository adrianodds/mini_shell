/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 15:26:38 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-16 15:26:38 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*st1;
	const unsigned char		*st2;

	i = 0;
	st1 = s1;
	st2 = s2;
	while (i < n)
	{
		if (st1[i] != st2[i])
		{
			return (st1[i] - st2[i]);
		}
		i++;
	}
	return (0);
}

/* int	main(void)
{
	char str1[] = "Adriano Duarte";
	char str2[] = "Adrian Duarte";
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};

	int result = ft_memcmp(s2, s3, 4);

	printf("Resultado: %d\n", result);

	return (0);
} */