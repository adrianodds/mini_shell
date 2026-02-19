/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:28:24 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/03 17:13:51 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function to check if it is a alphabetical
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (c);
	}
	return (0);
}
/*#include <stdio.h>
 int main(void)
{
		int i = 0;
		printf("%i", i = ft_isalpha(80));
		return (0);
} */