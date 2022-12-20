/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:17:27 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:17:30 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tail;

	head = NULL;
	tail = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		tail = ft_lstnew((*f)(lst->content));
		if (!tail)
		{
			ft_lstclear(&head, del);
			head = NULL;
			return (NULL);
		}
		ft_lstadd_back(&head, tail);
		lst = lst->next;
	}
	return (head);
}
