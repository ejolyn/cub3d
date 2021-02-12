/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:30:12 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/05 11:03:02 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*a;
	const unsigned char	*b;

	a = dst;
	b = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src < dst)
	{
		a += len;
		b += len;
		while (len--)
			*--a = *--b;
	}
	else
		while (len--)
			*a++ = *b++;
	return (dst);
}
