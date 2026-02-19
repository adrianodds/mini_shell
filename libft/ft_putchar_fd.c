/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:50:01 by carmoliv          #+#    #+#             */
/*   Updated: 2025/04/26 13:12:52 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Write to the output desired
void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
/* int	main(void)
{
	int	i;

	i = 0;
	while (i <= 47)
	{
		ft_putchar_fd(i + '0', 1);
	 	i++;
	}
} */