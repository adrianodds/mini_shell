/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:32:48 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/05 21:03:33 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Receives a string and a function, the function iterates on the passed string
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* void	my_upper(unsigned int i, char *c)
{
	(void)i;
	*c = ft_toupper(*c);
}
int	main(void)
{
	char	s[] = "fghij";
	ft_striteri(s, my_upper);

	printf("String alter: %s", s);
} */