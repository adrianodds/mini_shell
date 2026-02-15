/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:03:41 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 21:41:54 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function count number of char
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
/* #include <stdio.h>
int	main(void)
{
	char	name[] = "Carmelo";
	int	result;

	result = ft_strlen(name);
	printf("%d\n", result);
	return (0);
} */