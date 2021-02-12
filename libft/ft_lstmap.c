/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@stud.21-school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:33:08 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/04 16:24:24 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_lst;
	t_list *root;
	t_list **flag;

	if (lst == NULL)
		return (lst);
	root = ft_lstnew(f(lst->content));
	new_lst = NULL;
	flag = &root;
	lst = lst->next;
	while (lst)
	{
		if (f(lst->content))
		{
			new_lst = ft_lstnew(f(lst->content));
			ft_lstadd_back(&root, new_lst);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(flag, del);
			break ;
		}
	}
	return (*flag);
}
