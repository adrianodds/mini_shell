/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 16:45:17 by adduarte          #+#    #+#             */
/*   Updated: 2025/05/10 15:38:30 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char str)
{
	if ((str >= 9 && str <= 13) || (str == 32))
		return (1);
	return (0);
}

static int	is_signal(char str)
{
	if (str == '-' || str == '+')
		return (1);
	return (0);
}

static int	is_number(char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		signal;
	long	result;

	i = 0;
	signal = 1;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (is_signal(str[i]))
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (is_number(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signal);
}
/*
int	main(void)
{
	//const char *rep_number;
	//rep_number = "             +1";
	printf("%d\n", ft_atoi("\t\n\r\v\f  469 \n")));
}*/
