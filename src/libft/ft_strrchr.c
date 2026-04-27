/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-15 17:10:50 by adduarte          #+#    #+#             */
/*   Updated: 2025-04-15 17:10:50 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int			i;
	const char	*last;
	char		ch;

	i = 0;
	last = str;
	ch = (unsigned char)c;
	while (str[i] != 0)
	{
		if (str[i] == ch)
			last = &str[i];
		i++;
	}
	if ((last != str) || str[0] == ch)
		return ((char *)last);
	if (!ch)
		return ((char *)&str[i]);
	return (NULL);
}

/* int	main(void)
{
	//char	*str = "Adriano Duarte da Silva";
	char	*result = ft_strrchr("teste", 1024 + 'e');
	if (result != 0)
		printf("%s\n", result);
	else
		printf("%s\n", "Caractere nao encontrado.");
} */