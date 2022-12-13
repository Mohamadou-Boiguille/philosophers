/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:20:54 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:55 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		size;

	sub = NULL;
	size = ft_strlen(s) - start;
	if (size <= 0)
		size = 0;
	else if (size > (int)len)
		size = len;
	sub = ft_calloc(size + 1, sizeof(char));
	if (!sub)
		return (NULL);
	if (size)
		ft_strlcpy(sub, (s + start), size + 1);
	return (sub);
}
