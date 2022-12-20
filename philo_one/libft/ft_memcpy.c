/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:19:04 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:19:05 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, int l)
{
	char	*dest;

	dest = d;
	if (!d && !s)
		return (d);
	while (l--)
	{
		*(char *)d++ = *(char *)s++;
	}
	return (dest);
}
