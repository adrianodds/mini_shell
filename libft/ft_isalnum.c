/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:22:58 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/03 17:13:49 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function to check if it is a alphanumeric.
int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'))
		return (c);
	return (0);
}
/* int main(void)
{
	if (ft_isalnum('A'))
		printf("Is alphanumeric.");
	else
		printf("Not alphanumeric.");
	return (0);
} */