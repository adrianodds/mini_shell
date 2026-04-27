/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-17 15:48:37 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-17 15:48:37 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;

	dup = ((char *)malloc(ft_strlen(str) + 1));
	if (!dup)
		return (free(dup), NULL);
	ft_strlcpy(dup, str, ft_strlen(str) + 1);
	return (dup);
}

/*int	main(void)
{
	const char *str = "Adriano";
	printf("%s\n", ft_strdup(str));
}*/