/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:37:27 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/15 09:43:27 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*t;

	if (!alst)
		return ;
	if (*alst && del)
	{
		t = *alst;
		while (t)
		{
			tmp = t->next;
			ft_lstdelone(&t, del);
			t = tmp;
		}
		free(t);
		*alst = 0;
	}
}
