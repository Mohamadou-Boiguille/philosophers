/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:19:59 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:00 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	size;

	size = (ft_strlen(s) + 1);
	d = malloc(size);
	if (!d)
		return (NULL);
	ft_memcpy((void *)d, (const void *)s, size);
	return (d);
}
