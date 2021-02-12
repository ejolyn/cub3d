/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:19:58 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/08 14:52:14 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *substr;
	char *flag;

	if (s == NULL)
		return (NULL);
	substr = (char *)malloc(len + 1);
	flag = substr;
	if (substr == NULL || ((size_t)start >= ft_strlen(s)))
		return (substr);
	while (start--)
		s++;
	while (len-- && *s != '\0')
		*substr++ = *s++;
	*substr = '\0';
	return (flag);
}
