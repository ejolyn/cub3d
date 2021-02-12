/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:09:39 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 13:14:11 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list *copy;

	copy = *lst;
	if (*lst != NULL)
	{
		while (copy != NULL)
		{
			del((*lst)->content);
			copy = (*lst)->next;
			free(*lst);
			*lst = copy;
		}
	}
}
