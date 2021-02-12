/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:28:38 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 11:08:13 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	numb;

	i = 0;
	numb = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == 48)
		i++;
	while (str[i] > 47 && str[i] < 58)
		if (numb < 9223372036854775807 / 10 - (str[i] - 48) - 1)
			numb = numb * 10 + (str[i++] - 48);
		else if ((numb > 9223372036854775807 / 10 - (str[i] - 48) - 1)
				&& sign == -1)
			return (0);
		else
			return (-1);
	return ((int)numb * sign);
}
