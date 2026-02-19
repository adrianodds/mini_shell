/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:57:33 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 20:40:39 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Add one new node in final of list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
/*int main ()
{
	t_list *test = NULL;
	int	value = 12;
	test = ft_lstnew(&value);
	for (int j = 0; j < 10; j++)
	{
		int	*val;
		val = malloc(sizeof(int));
		if (!val)
			return (1);
		*val = j;
		t_list *new;
		new = ft_lstnew(val);
		ft_lstadd_back(&test, new);
		//ft_lstadd_front(&test, new);
	}
	t_list *temp = test;
	int i = 0;
	while (temp != NULL)
	{
		printf("Value %d position %d\n",*(int *)(temp->content), i);
		temp = temp->next;
		i++;
	}
	 t_list *tmp;
	while (test)
	{
		tmp = test->next;
		free(test->content);
		free(test);
		test = tmp;
	}
}*/