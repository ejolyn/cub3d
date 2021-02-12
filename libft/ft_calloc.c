/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 09:47:17 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/10 18:19:23 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*xx;
	size_t	size2;

	size2 = size * count;
	if (!(xx = malloc(size2)))
		return (NULL);
	if (xx)
		ft_bzero(xx, size2);
	return (xx);
}
