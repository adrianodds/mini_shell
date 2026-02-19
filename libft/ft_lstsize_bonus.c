/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:04:01 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 21:08:49 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Returns the size of the list
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/* int	main()
{
	int	result;
	t_list *test = NULL;

	for (int i = 0; i < 5; i++)
	{
		int *val = malloc(sizeof(int));
		if (!val)
			return (1);
		*val = i;
		t_list *node = ft_lstnew(val);
		ft_lstadd_front(&test, node);
	}
	result = ft_lstsize(test);
	printf("Size of list: %d", result);

	t_list	*temp;
	while (test)
	{
		temp = test->next;
		free(test->content);
		free(test)
		test = temp;
	}
} */