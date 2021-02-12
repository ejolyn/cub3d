/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:28:07 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 10:48:27 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*a;
	const unsigned char	*b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (n)
	{
		while (n--)
		{
			if (*b != (unsigned char)c)
				*a++ = *b++;
			else
			{
				*a++ = *b++;
				return (a);
			}
		}
	}
	return (0);
}
