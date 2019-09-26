/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choosegroup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:18:47 by cmarouan          #+#    #+#             */
/*   Updated: 2019/09/26 20:01:48 by cmarouan         ###   ########.fr       */
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

t_group			*verifyoneg(t_group *bestg, t_vargrp var, int nb, t_group *grp)
{
	t_listpath	*tmp;
	double		antintr;

	tmp = grp->paths;
	while (tmp)
	{
		if (tmp->path)
			var.nbnode += tmp->path->size;
		antintr = (double)(nb + var.nbnode - ++var.count * 2);
		tmp->path->all_prev_inst = ceil(antintr / (double)var.count);
		if (var.m > tmp->path->all_prev_inst)
		{
			grp->stop = var.count;
			var.m = tmp->path->all_prev_inst;
		}
		tmp = tmp->next;
	}
	grp->best = var.m;
	antintr = (double)((var.nbnode + nb) - (var.nbpath * 2));
	grp->instr = ceil(antintr / (double)var.nbpath);
	if (bestg == NULL)
		bestg = grp;
	else if (bestg->best > grp->best)
		bestg = grp;
	return (bestg);
}

t_group			*best_groups(t_group *grps, int nb_ants)
{
	t_group		*bestg;
	t_group		*grp;
	t_vargrp	var;

	bestg = NULL;
	grp = grps;
	while (grp)
	{
		var.nbnode = 0;
		var.nbpath = grp->paths->size;
		var.m = INT_MAX;
		var.count = 0;
		bestg = verifyoneg(bestg, var, nb_ants, grp);
		grp = grp->next;
	}
	return (bestg);
}
