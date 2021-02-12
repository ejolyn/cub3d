/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:45:38 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/08 14:55:47 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		checker(char const chr, char const *set)
{
	while (*set != '\0')
	{
		if (*set++ == chr)
			return (1);
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (checker(s1[end], set))
		if (end)
			end--;
		else
			break ;
	end++;
	while (checker(s1[start], set))
		++start;
	if ((size_t)(start) == ft_strlen(s1))
		return (ft_substr("", 0, 1));
	else
		return (ft_substr(s1, start, end - start));
}
