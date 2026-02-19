/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:07:43 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 21:17:36 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Returns the two concatenated strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (0);
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest [i + j] = '\0';
	return (dest);
}
/* int main()
{
    char    *name = "Carm";
    char    *name2 = "Oliv";
    char    *result;

    printf("String together: %s\n", result = ft_strjoin(name, name2));
} */