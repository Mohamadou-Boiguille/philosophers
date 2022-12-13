/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:20:49 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:50 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		start;
	int		end;
	int		size;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	size = 0;
	trimmed = NULL;
	while (ft_strchr(set, s1[start]) && start < end)
		start++;
	while (ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	size = end - start;
	trimmed = ft_calloc(size + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (i < size)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	return (trimmed);
}
