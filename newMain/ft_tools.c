/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:46:24 by cmarouan          #+#    #+#             */
/*   Updated: 2019/09/29 21:29:00 by kmoussai         ###   ########.fr       */
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


void	solve(t_lemin *lemin)
{
	t_path		*newpath;
	t_listpath	*paths;

	lemin->check = 0;
	while (bfs_sp(lemin, 0, 0, NULL))
	{
		lemin->check = 1;
		ft_graphupdate(lemin, lemin->goal);
		copy_graph(lemin);
		paths = NULL;
		while (bfs_nulledge(lemin, 0, 0, NULL))
		{
			lemin->check_used = 0;
			newpath = ft_pathbuilder_nulledge(lemin, NULL, lemin->goal);
			if (lemin->check_used == 0)
				paths = addpath(paths, newpath, lemin->n_ant);
			else
				freepath(newpath);
		}
		lemin->groups = addgroup(lemin->groups, paths);
	}
	if (!lemin->check)
		ft_err("NO Path");
}
