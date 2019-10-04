/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:46:24 by cmarouan          #+#    #+#             */
/*   Updated: 2019/10/04 10:44:09 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_adj		*ft_addadj(t_adj *l, int node)
{
	t_adj	*t;

	t = (t_adj *)malloc(sizeof(t_adj));
	t->node = node;
	t->next = NULL;
	if (!l)
		return (t);
	t->next = l;
	return (t);
}

t_group		*dispatchant(t_group *teemp, t_lemin *lemin)
{
	int			i;
	int			nbrant;
	t_listpath	*ansr;
	t_listpath	*it;

	nbrant = lemin->n_ant;
	i = 0;
	while (nbrant)
	{
		i = 0;
		it = teemp->paths;
		ansr = it;
		while (it)
		{
			if (ansr->v_node > it->v_node)
				ansr = it;
			it = it->next;
			i++;
		}
		ansr->v_node++;
		ansr->nbr_ant++;
		nbrant--;
	}
	return (teemp);
}
