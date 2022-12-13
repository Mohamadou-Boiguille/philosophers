/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:20:27 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:20:29 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*mapped;

	i = 0;
	mapped = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!mapped)
		return (NULL);
	while (s[i])
	{
		mapped[i] = (*f)(i, s[i]);
		i++;
	}
	return (mapped);
}
