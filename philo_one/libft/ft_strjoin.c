/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:20:08 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:09 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	if (ft_strlen(s1))
	{
		ft_strlcpy(str, s1, size);
		ft_strlcat(str, s2, size);
	}
	else
		ft_strlcpy(str, s2, size);
	return (str);
}
