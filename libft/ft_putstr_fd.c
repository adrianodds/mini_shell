/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:54:03 by carmoliv          #+#    #+#             */
/*   Updated: 2025/04/22 22:13:17 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Write a string full character by character
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}
/* int	main(void)
{
	char	*name = "Carmelo";
	
	ft_putstr_fd(name, 1);
} */