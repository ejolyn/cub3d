/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:13:50 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 10:40:56 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	s2 = (char *)malloc(ft_strlen(s) + 1);
	if (s2 == NULL)
		return (NULL);
	while (*s)
	{
		s2[i] = f(i, *s++);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
