/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:03:25 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 10:28:24 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const char	*dst2;
	const char	*src2;
	size_t		dstsize2;
	size_t		dst_len;

	dst2 = dst;
	src2 = src;
	dstsize2 = dstsize;
	while (dstsize2-- != 0 && *dst != '\0')
		dst++;
	dst_len = dst - dst2;
	dstsize2 = dstsize - dst_len;
	if (dstsize2-- == 0)
		return (dst_len + ft_strlen(src));
	while (*src != '\0')
	{
		if (dstsize2 != 0)
		{
			*dst++ = *src;
			dstsize2--;
		}
		src++;
	}
	*dst = '\0';
	return (dst_len + (src - src2));
}
