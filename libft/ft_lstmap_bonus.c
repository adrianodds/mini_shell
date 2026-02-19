/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:21:34 by carmoliv          #+#    #+#             */
/*   Updated: 2025/05/07 20:22:59 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*new_content;

	new_lst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
/* void    *to_upper(void *content)
{
    char    *str;
    int     i;

    str = (char *)content;
    i = 0;
    while (str[i])
    {
        str[i] = (char)ft_toupper(str[i]);
        i++;
    }
    return content;
}

void    delet(void *content)
{
    free(content);
}

int main()
{
    t_list  *n1;
    t_list  *n2;
    t_list  *n3;
    t_list  *new;

    n1 = ft_lstnew(ft_strdup("node 1"));
    n2 = ft_lstnew(ft_strdup("node 2"));
    n3 = ft_lstnew(ft_strdup("node 3"));

    n1->next = n2;
    n2->next = n3;

    // Mapear a lista original para a nova lista
    new = ft_lstmap(n1, to_upper, delet);

    // Verificar e imprimir os resultados
    while (new)  // Corrigindo a iteração pela lista resultante
    {
        printf("%s\n", (char *)new->content);
        new = new->next;
    }

    // Liberar a memória da lista original
    ft_lstclear(&n1, delet);

    return 0;
} */