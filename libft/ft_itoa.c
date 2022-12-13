/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:21:06 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:21:07 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int nb)
{
	int	len;

	len = 1;
	while (nb / 10 != 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

void	parse(char *s, long nb, int i)
{
	i--;
	if (nb / 10 != 0)
		parse(s, nb / 10, i);
	s[i] = (nb % 10) + 48;
}

char	*ft_itoa(int n)
{
	long	nb;
	int		isneg;
	int		len;
	char	*s;

	nb = n;
	isneg = 0;
	len = 0;
	if (n < 0)
	{
		isneg = 1;
		nb *= -1;
	}
	len += get_len(nb);
	s = ft_calloc(len + 1 + isneg, sizeof(char));
	if (!s)
		return (NULL);
	if (n < 0)
		s[0] = '-';
	parse(s + isneg, nb, len);
	return (s);
}
