/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:36:08 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 22:28:30 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Compares the two strings and returns 
//positive if s1 is greater,
//negative if s1 is less and 0 if they are equal.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/* #include <stdio.h>

int	main(void)
{
	char	s1[] = "Carmlo";
	char	s2[] = "Carmelo";
	size_t	i = 2;
	int		result;

	result = ft_strncmp(s1, s2, i);
	if (result > 0)
		printf("Value %d, S1 is greater than S2.\n", result);
	else if (result == 0)
		printf("Value %d, S1 e S2 are the same.\n", result);
	else
		printf("Value %d, S1 is lass than S2.\n", result);

	return (0);
} */