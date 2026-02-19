/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:30:48 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/03 17:13:52 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function to check if it is a value table ascii
int	ft_isascii(int c)
{
	if (!c)
		return (1);
	if (c >= 0 && c <= 127)
		return (c);
	return (0);
}
/* int	main()
{
	if (ft_isascii('a'))
		printf("Is value table ascii");
	else
		printf("Not value table ascii");
	return (0);
} */