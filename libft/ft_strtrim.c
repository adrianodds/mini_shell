/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:24:29 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 22:14:17 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Remove the characters of the begin and of the end.
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	dest = ft_substr(s1, start, end - start);
	if (!dest)
		return (NULL);
	return (dest);
}
/* int main(void)
{
	char	*s1 = "  !:.Car:melo.:!  ";
	char	*set = " !:";

	printf("String trimmed:%s", ft_strtrim(s1, set));
	return(0);
} */