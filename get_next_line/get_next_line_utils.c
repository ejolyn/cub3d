/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:02:12 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 11:11:45 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strdup(const char *s1)
{
	char		*dupl;
	const char	*s2;

	s2 = s1;
	while (*s1)
		s1++;
	dupl = (char *)malloc(s1 - s2 + 1);
	s1 = dupl;
	if (dupl)
	{
		while (*s2)
			*dupl++ = *s2++;
		*dupl = '\0';
	}
	return ((char *)s1);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		len1;
	int		len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = (char *)malloc(len1 + len2 + 1);
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, s1, len1 + len2 + 1);
	ft_strlcat(s3, s2, len1 + len2 + 1);
	s3[len2 + len1] = '\0';
	return (s3);
}
