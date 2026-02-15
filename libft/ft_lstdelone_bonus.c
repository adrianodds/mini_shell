/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:25:08 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 21:05:02 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Remove the content of list
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
void    print_lst(t_list *lst)
{
    while (lst)
    {
        printf("%s - >",(char *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main()
{
 
    t_list *n1 = ft_lstnew(ft_strdup("Node 1"));
    t_list *n2 = ft_lstnew(ft_strdup("Node 2"));
    t_list *n3 = ft_lstnew(ft_strdup("Node 3"));

    n1->next = n2;
    n2->next = n3;

    printf("List original:\n");
    print_lst(n1);

    t_list *temp = n2;
    n1->next = n2->next;
    ft_lstdelone(temp, free);

    printf("After remove:\n");
    print_lst(n1);

    ft_lstdelone(n1, free);
    ft_lstdelone(n3, free);
    
return (0);
}*/