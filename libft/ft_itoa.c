/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:18:21 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/05 10:26:15 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_reverse(char *str, int len)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (len >= i)
	{
		c = str[i];
		str[i] = str[len];
		str[len] = c;
		i++;
		len--;
	}
	return (str);
}

static	int		counter(int n)
{
	int len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	int				n2;
	int				len;
	char			*str;
	unsigned int	nbr;

	len = counter(n);
	nbr = (n < 0) ? (unsigned int)n * -1 : n;
	n2 = (n < 0) ? 1 : 0;
	len = (n < 0) ? len + 1 : len;
	str = (char *)malloc(len + 1);
	len = 0;
	if (str == NULL)
		return (str);
	if (n == 0)
		str[len++] = '0';
	while (nbr)
	{
		str[len++] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n2)
		str[len++] = '-';
	str[len] = '\0';
	str = ft_reverse(str, len - 1);
	return (str);
}
