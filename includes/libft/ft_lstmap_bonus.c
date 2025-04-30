/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:33:46 by angnavar          #+#    #+#             */
/*   Updated: 2024/10/05 16:33:36 by angnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_renode(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;

	node = ft_lstnew_bonus(f(lst->content));
	if (!node)
		return (NULL);
	if (!node->content)
		del (node->content);
	if (lst->next)
		node->next = ft_renode (lst->next, f, del);
	else
		node->next = NULL;
	return (node);
}

t_list	*ft_lstmap_bonus(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	if (!lst || !f || !del)
		return (NULL);
	return (ft_renode(lst, f, del));
}
/*
void	*ft_transform(void *content)
{
	int	*i = (int *)malloc(sizeof(int));
	if (!i)
		return (NULL);
	*i = *(int *)content + 1;
	return i;
}
void	ft_del(void *content)
{
	free(content);
}

int	main(void)
{
	int a = 1, b = 2, c = 3;
	t_list *list = ft_lstnew(&a);
	list->next = ft_lstnew(&b);
	list->next->next = ft_lstnew(&c);
	t_list *temp = list;
	printf("Original list:\n");
	while (temp)
	{
		printf("%d\n", *(int *)temp->content);
		temp = temp->next;
	}

	t_list *new_list = ft_lstmap(list, ft_transform, ft_del);

	printf("\nTransformed list:\n");
	temp = new_list;
	while (temp)
	{
		printf("%d\n", *(int *)temp->content);
		temp = temp->next;
	}

	return (0);
}*/
