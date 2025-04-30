/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/03 16:14:12 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstrecursive(t_list *lst, void (*del)(void*))
{
	if (lst->next)
		ft_lstrecursive (lst->next, del);
	ft_lstdelone_bonus (lst, del);
}

void	ft_lstclear_bonus(t_list **lst, void (*del)(void*))
{
	if (!lst || !*lst || !del)
		return ;
	ft_lstrecursive (*lst, del);
	*lst = NULL;
}
/*
int main()
{
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));

    node1->content = ft_strdup("hello!");
    node1->next = node2;
    node2->content = ft_strdup("world!");
    node2->next = NULL;

    ft_lstclear(&node1, free);

    return 0;
}*/
