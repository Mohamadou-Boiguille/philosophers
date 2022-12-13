/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:17:44 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:17:48 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new_)
{
	t_list	*last;

	if (alst && *alst)
	{
		last = ft_lstlast(*alst);
		last->next = new_;
	}
	else if (*alst == NULL)
	{
		*alst = new_;
	}
}
