/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-17 16:10:52 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-17 16:10:52 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cp;
	int		i;
	size_t	len_str;

	i = 0;
	len_str = ft_strlen(s);
	if (start >= len_str)
		return (ft_strdup(""));
	if (len > len_str - start)
		len = len_str - start;
	cp = (char *)malloc(len + 1);
	if (!cp)
		return (free(cp), NULL);
	while (len--)
	{
		cp[i] = s[start++];
		i++;
	}
	cp[i] = 0;
	return (cp);
}

/* int	main(void)
{
	char * s = ft_substr("tripouille", 0, 42000)
	char str[] = "lorem ipsum dolor sit amet";
	printf("%s\n", ft_substr(str, 7, 10));
} */