/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:18:53 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:18:54 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem, int c, size_t size)
{
	char	*m;
	size_t	i;

	m = (char *)mem;
	i = 0;
	while (i < size)
	{
		if (m[i] == (char)c)
			return (&m[i]);
		i++;
	}
	return (0);
}
