/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:19:09 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:19:11 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst, const void *src, int size)
{
	char	*d;
	char	*s;
	int		i;

	d = dst;
	s = (char *)src;
	i = 0;
	if (!d && !s)
		return (dst);
	if (d > s)
	{
		while (size--)
			*(d + size) = *(s + size);
	}
	else
	{
		while (i < size)
		{
			*(d + i) = *(s + i);
			i++;
		}
	}
	return (dst);
}
