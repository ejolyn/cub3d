/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:08:55 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/05 13:03:21 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*s2;
	char		c2;

	c2 = (char)c;
	s2 = s + ft_strlen(s) + 1;
	while (s2-- >= s)
	{
		if (*s2 == c2)
			return ((char *)s2);
	}
	return (NULL);
}
