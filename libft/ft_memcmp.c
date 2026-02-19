/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:41:35 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/03 18:25:46 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function compare byte a byte memory regions
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
/* int main ()
{
	char	name[] = "a";
	char	name2[] = "rmelo";
	size_t	len = 3;
	int	result;

	result = ft_memcmp(name, name2, len);
	if (result < 0)
		printf("%d, value negative if first byte S1 different of S2", result);
	else if (result > 0)
		printf("%d, value positive if first byte S1 different of S2", result);
	else
		printf("%d, If this blocks are the same, S1 and S2", result);
} */