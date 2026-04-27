/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-19 14:04:41 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-19 14:04:41 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_int(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n = -n;
		i = 1;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	fill_digits(char *index, long number, int lenght)
{
	if (number == 0)
		index[lenght] = '0';
	while (number)
	{
		index[lenght--] = (number % 10) + '0';
		number = number / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*index;
	int		lenght;
	long	number;

	number = n;
	lenght = count_int(number);
	index = (char *)malloc(lenght + 1);
	if (!index)
		return (NULL);
	index[lenght--] = 0;
	if (number < 0)
	{
		number = -number;
		index[0] = '-';
	}
	fill_digits(index, number, lenght);
	return (index);
}
/*
If you pass a 0, the index[l] = n + '0'; \
ensure that zero is returned since in the \
10 conversion condition it does so while \
is greater than zero.
#include <stdio.h>
 int	main(void)
{
	printf("%s\n", ft_itoa(-15489565));
}*/