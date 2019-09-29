/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choosegroup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:18:47 by cmarouan          #+#    #+#             */
/*   Updated: 2019/09/29 21:26:46 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				*ft_bzero_me(int *s, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

t_arrays		*addtoarray(t_arrays *arr, int size, int nbrant)
{
	t_arrays	*new;

	new = (t_arrays *)malloc(sizeof(t_arrays));
	new->size = size;
	new->patharray = (int *)malloc(sizeof(int) * size);
	new->patharray = ft_bzero_me(new->patharray, size);
	new->patharray[0] = nbrant;
	new->last = new;
	new->next = NULL;
	if (!arr)
		return (new);
	arr->last->next = new;
	arr->last = new;
	return (arr);
}

t_arrays		*createarrays(t_group *grps)
{
	t_arrays	*arrays;
	int			nbr_nodes;
	int			stop;
	t_group		*grp;
	t_listpath	*temp;

	nbr_nodes = 0;
	arrays = NULL;
	stop = grps->stop;
	grp = grps;
	temp = grp->paths;
	while (temp && stop > 0)
	{
		stop--;
		nbr_nodes = temp->path->size + 1;
		arrays = addtoarray(arrays, nbr_nodes, temp->nbr_ant);
		temp = temp->next;
	}
	return (arrays);
}

t_group			*best_groups(t_lemin *lemin)
{
	t_group		*bestg;
	t_group		*grp;
	int			ansr;

	ansr = -1;
	grp = lemin->groups;
	while (grp)
	{
		grp = dispatchant(grp, lemin);
		if (ansr == -1)
		{
			ansr = (grp->paths->nbr_ant + grp->paths->path->size - 2);
			bestg = grp;
		}
		else if (ansr > (grp->paths->nbr_ant + grp->paths->path->size - 2))
		{
			ansr = (grp->paths->nbr_ant + grp->paths->path->size - 2);
			bestg = grp;
		}
		grp = grp->next;
	}
	bestg->instr = ansr;
	bestg->stop = 0;
	return (bestg);
}
