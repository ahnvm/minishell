/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:25:29 by acan              #+#    #+#             */
/*   Updated: 2023/07/15 14:09:44 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmplst;
	t_list	*ret;

	if (!lst || !f || !del)
		return (0);
	tmplst = ft_lstnew(f(lst->content));
	if (!tmplst)
		return (0);
	ret = tmplst;
	lst = lst->next;
	while (lst)
	{
		tmplst->next = ft_lstnew(f(lst->content));
		if (!tmplst->next)
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		tmplst = tmplst->next;
		lst = lst->next;
	}
	tmplst->next = NULL;
	return (ret);
}
