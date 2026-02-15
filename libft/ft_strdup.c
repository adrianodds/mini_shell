/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:12:56 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 20:58:07 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Creates a new string in the heap with the content passed as a parameter
char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}
/*int	main()
{
	const char *original = "Carmelo";
	char *copy;

	copy = ft_strdup(original);
	if (copy)
	{
		printf("String original: %s\n",original);
		printf("String copy: %s\n", copy);
		copy[0] = 'X';
		printf("String modified: %s\n", copy);
		printf("String original: %s\n", original);
		free(copy);
	}
	else
		printf("Error function.");
	return (0);
}*/