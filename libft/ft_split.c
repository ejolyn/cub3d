/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:12:21 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/18 12:56:50 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	int		ft_counter_str(char *s, char c)
{
	int str;

	str = 0;
	while (*s == c && c != '\0')
		s++;
	if (*s == '\0')
		return (0);
	if (c == '\0')
		return (1);
	while (*s)
	{
		while (*s != c && *s != '\0')
			s++;
		str++;
		while (*s == c)
			s++;
	}
	return (str);
}

static	char	*ft_allocation(char const *s, char c)
{
	int		size;
	char	*word;

	size = 0;
	word = 0;
	while (s[size] && (s[size] != c))
		size++;
	if (!(word = (char *)malloc(size + 1)))
		return (NULL);
	ft_strlcpy(word, s, size + 1);
	return (word);
}

static	char	**free_helper(char **divide, int i)
{
	while (--i >= 0)
		free(divide[i]);
	free(divide);
	return (0);
}

char			**ft_split(char const *s, char c)
{
	char	**divide;
	int		count;
	int		str;

	count = -1;
	if (!s)
		return (NULL);
	str = ft_counter_str((char *)s, c);
	divide = (char **)malloc((str + 1) * sizeof(char *));
	if (divide == NULL)
		return (NULL);
	while (++count < str)
	{
		while (*s == c)
			s++;
		if (!(divide[count] = ft_allocation(s, c)))
			return (free_helper(divide, count));
		s += ft_strlen(divide[count]);
	}
	divide[count] = NULL;
	return (divide);
}
