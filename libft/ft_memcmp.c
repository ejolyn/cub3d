/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:52:39 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 11:00:04 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *copy1;
	const unsigned char *copy2;

	copy1 = s1;
	copy2 = s2;
	while (n--)
	{
		if (*copy1++ != *copy2++)
			return (*--copy1 - *--copy2);
	}
	return (0);
}
