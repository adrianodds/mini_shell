/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:16:28 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/07 21:07:41 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function to alocation block memory with zero using malloc.
void	*ft_calloc(size_t count, size_t size)
{
	void		*ptr;
	size_t		max;

	max = count * size;
	if (size && ((max / size) != count))
		return (NULL);
	ptr = (int *)malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
/* int	main()
{
	char *i;

	i = (char *)ft_calloc(10, sizeof(int));
	int j = 0;
	while(j < 40)
	{
		printf("%d - %d \n",i[j], j);
		j++;
	}
} */