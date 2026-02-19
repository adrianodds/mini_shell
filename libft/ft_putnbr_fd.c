/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:23:14 by carmoliv          #+#    #+#             */
/*   Updated: 2025/04/26 13:20:22 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function writes an integer to the desired output.
void	ft_putnbr_fd(int n, int fd)
{
	long	x;

	x = n;
	if (x < 0)
	{
		x *= -1;
		ft_putchar_fd('-', fd);
	}
	if (x > 9)
	{
		ft_putnbr_fd(x / 10, fd);
	}
	ft_putchar_fd(x % 10 + '0', fd);
}
/*int	main(void)
{
	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-5, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-57, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-987441, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-2147483648LL, 1);
}*/