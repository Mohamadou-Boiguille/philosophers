/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:17:57 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:17:59 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_next;

	if (lst && *lst && del)
	{
		while (*lst)
		{
			temp_next = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp_next;
		}
	}
}
