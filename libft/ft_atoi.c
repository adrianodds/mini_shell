/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:00:20 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/03 16:36:38 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*Receive a number of the type string and return
a value of the interger*/
int	ft_atoi(const char *str)
{
	int	i;
	int	signal;
	int	result;

	signal = 1;
	result = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * signal);
}
/* int	main(void)
{
	char	value[40] = "+123";

	printf("%d\n",ft_atoi(value));
} */