/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 09:50:21 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/15 10:43:05 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*t;
	t_list	*tmp;
	t_list	*iter;

	t = NULL;
	if (lst && f)
	{
		tmp = f(lst);
		if ((t = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
			return (NULL);
		iter = t;
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst);
			iter->next = ft_lstnew(tmp->content, tmp->content_size);
			if (iter->next == NULL)
				return (NULL);
			lst = lst->next;
			iter = iter->next;
		}
	}
	return (t);
}
