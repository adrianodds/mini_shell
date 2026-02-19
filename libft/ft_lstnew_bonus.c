/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:17:45 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/06 21:08:00 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Creates and initializes a new node
t_list	*ft_lstnew(void *content)
{
	t_list	*cont;

	cont = (t_list *)malloc(sizeof(*cont));
	if (!cont)
		return (NULL);
	cont->content = content;
	cont->next = NULL;
	return (cont);
}
/*int	main(void)
{
	int num = 42;
	t_list *node = ft_lstnew(&num);

	if (node)
		printf("The value in list: %d",*(int*)(node->content));
	else
		printf("Not have value");

	char *name = strdup("Carmoliv");
    if (!name)
    {
        printf("Error creator string");
        return (1);
    }
    
    t_list *node = ft_lstnew(name);
    if (name)
        printf("Value in node: %s\n",(char *)(node->content));
    else
    printf("Value not store");
    free(name);
    free(node);
}*/