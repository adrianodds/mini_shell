/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:07:18 by carmoliv          #+#    #+#             */
/*   Updated: 2025/04/13 17:10:19 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}
/* #include <stdio.h>
int	main(void)
{
	int	i = 65;
	int result = ft_tolower(i);

	printf("%d\n", result);

} */