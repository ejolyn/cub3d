/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:28:24 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 10:42:48 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	const char	*src2;

	i = dstsize;
	src2 = src;
	if (dst == NULL || src == NULL)
		return (0);
	if (dstsize != 0)
	{
		while (--i != 0)
		{
			if (*src != '\0')
				*dst++ = *src++;
			else
				break ;
		}
	}
	if (dstsize != 0)
		*dst = '\0';
	while (*src++)
		;
	return (src - src2 - 1);
}
