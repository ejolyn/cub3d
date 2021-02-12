/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:53:29 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 10:46:39 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*s2;
	char		c2;

	c2 = (char)c;
	s2 = s;
	if (*s2 == '\0' && c == '\0')
		return ((char *)s2);
	while (*s2)
	{
		if (*s2++ == c2)
			return ((char *)--s2);
	}
	if (*s2 == '\0' && c == '\0')
		return ((char *)s2);
	return (NULL);
}
