/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:59:31 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 21:05:05 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//add new node in beginning of list
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/* int	main()
{
	t_list	*test;
	
	int	value = 12;
	test = ft_lstnew(&value);
	for (int j = 0; j < 10; j++)
	{
		t_list *new;

		new = ft_lstnew(&j);
		ft_lstadd_front(&test, new);
	}

	t_list *tmp = test;
	while (tmp != NULL)
	{
		printf("Value: %d\n", *(int *)(tmp->content));
		tmp = tmp->next;
	}
} */