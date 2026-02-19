/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:25:52 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 21:05:00 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Apply function to each node content
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void    print_lst(void *content)
{
    printf("%s\n",(char*)content);
}
int main()
{
    t_list *n1 = ft_lstnew(ft_strdup("node 1"));
    t_list *n2 = ft_lstnew(ft_strdup("node 2"));
    t_list *n3 = ft_lstnew(ft_strdup("node 3"));

    n1->next = n2;
    n2->next = n3;

    printf("List content:\n");
    ft_lstiter(n1,print_lst);

    ft_lstdelone(n1, free);
    ft_lstdelone(n2, free);
    ft_lstdelone(n3, free);

    return (0);
}*/