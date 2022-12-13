/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:21:37 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:21:38 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nb_of_memb, size_t size)
{
	void	*ptr;

	if (nb_of_memb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ptr = malloc(nb_of_memb * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, nb_of_memb * size);
	return (ptr);
}
