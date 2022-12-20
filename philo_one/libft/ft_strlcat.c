/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:20:12 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:13 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	j;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	j = 0;
	if (dlen < size)
	{
		while ((dlen + j < size - 1) && src[j])
		{
			dst[dlen + j] = src[j];
			j++;
		}
		dst[dlen + j] = '\0';
		return (dlen + slen);
	}
	return (slen + size);
}
