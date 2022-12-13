/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:20:41 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:42 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *buff, const char *searched, int size)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(searched);
	if (!j)
		return ((char *)buff);
	if (size == -1)
		size = ft_strlen(buff);
	while (buff[i] != '\0' && i + j < size)
	{
		if (buff[i] == searched[0])
		{
			if (!ft_strncmp(buff + i, searched, j))
				return ((char *)buff + i);
		}
		i++;
	}
	return (NULL);
}
