/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:27:39 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 20:57:12 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//function deletes all nodes from the list
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
/*
void    print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s ->",(char *)lst->content);
        lst=lst->next;
    }
    printf("NULL\n");
}

int main()
{
    t_list *n1 = ft_lstnew(ft_strdup("Node 1"));
    t_list *n2 = ft_lstnew(ft_strdup("Node 2"));

    n1->next = n2;

    printf("List before:\n");
    print_list(n1);

    ft_lstclear(&n1,free);

    printf("List after:\n");
    print_list(n1);

    return (0);
}*/