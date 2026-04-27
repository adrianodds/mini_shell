/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-17 18:04:14 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-17 18:04:14 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_trim(char str, const char *tr)
{
	int	i;

	if (!tr)
		return (0);
	i = 0;
	while (tr[i])
	{
		if (tr[i] == str)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (start < end && check_trim(s1[start], set))
		start++;
	while (end > start && check_trim(s1[end - 1], set))
		end--;
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}

/* int	main(void)
{
	char *str;
	str = "lorem \n ipsum \t dolor \n sit \t amet";
	printf("%s\n", ft_strtrim("   xxx   xxx", " x"));
} */