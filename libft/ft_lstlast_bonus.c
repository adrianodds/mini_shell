/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:28:50 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 21:04:57 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function return the last node of the list
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/* int	main()
{
	t_list *list = NULL;
	int	*value;

	for (int i = 0; i < 5; i++)
	{
		value = malloc(sizeof(int));
		if (!value)
			return (1);
		*value = i;
		t_list *node = ft_lstnew(value);
		ft_lstadd_front(&list, node);
	}
	t_list *last = ft_lstlast(list);
	if (last)
		printf("Last value of the list: %d\n", *(int *)(last->content));
	else
		printf("The list is empty");
	t_list *temp;
	while(list)
	{
		temp = list->next;
		free(list->content);
		free(list);
		list = temp;
	}
	return (0);
} */