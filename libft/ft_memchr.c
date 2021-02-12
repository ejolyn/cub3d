/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:44:54 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 10:53:02 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *a;

	a = s;
	if (n)
	{
		while (n--)
		{
			if (*a++ == (unsigned char)c)
				return ((void *)(a - 1));
		}
	}
	return (NULL);
}
