/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:04:06 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 10:47:36 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*dupl;
	const char	*s2;

	s2 = s1;
	while (*s1++)
		;
	dupl = (char *)malloc(s1 - s2);
	s1 = dupl;
	if (dupl)
	{
		while (*s2)
			*dupl++ = *s2++;
		*dupl = '\0';
	}
	return ((char *)s1);
}
