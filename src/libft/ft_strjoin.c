/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-17 16:32:46 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-17 16:32:46 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cp;
	int		l_s1;
	int		l_s2;

	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	cp = (char *)ft_calloc((l_s1 + l_s2 + 1), sizeof(char));
	if (!cp)
		return (NULL);
	ft_strlcat(cp, s1, l_s1 + 1);
	ft_strlcat(cp, s2, l_s1 + l_s2 + 1);
	return (cp);
}

/* int	main(void)
{
	char const *s1;
	char const *s2;

	s1 = "lorem ipsum";
	s2 = "dolor sit amet";

	printf("%s\n", ft_strjoin(s1, s2));
} */