/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:52:56 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/07 19:42:04 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Returns a sub-string of the content "S"
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	len_s;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	i = 0;
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/* int main()
{
	//printf("%s", ft_substr("Carmoliv", 2, ft_strlen("Carmoliv")));
	printf("%s", ft_substr("", 0, 0));
} */