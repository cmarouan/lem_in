/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:16:22 by kmoussai          #+#    #+#             */
/*   Updated: 2019/09/29 21:31:13 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path		*addnode(t_path *path, int node)
{
	t_path *newnode;

	newnode = (t_path *)malloc(sizeof(t_path));
	newnode->node = node;
	newnode->size = 1;
	newnode->next = NULL;
	if (!path)
		return (newnode);
	newnode->next = path;
	newnode->size = ++path->size;
	return (newnode);
}

t_listpath	*addpath(t_listpath *paths, t_path *newpath, int nbrant)
{
	t_listpath *list;

	list = (t_listpath *)malloc(sizeof(t_listpath));
	newpath->nbr_inst = newpath->size - 2 + nbrant;
	newpath->all_prev_inst = 0;
	list->path = newpath;
	list->size = 1;
	list->v_node = newpath->size - 1;
	list->nbr_ant = 0;
	list->next = NULL;
	list->last = list;
	if (!paths)
		return (list);
	paths->last->next = list;
	list->size = ++paths->size;
	paths->last = list;
	return (paths);
}

t_group		*addgroup(t_group *grps, t_listpath *paths)
{
	t_group *newgroup;

	newgroup = (t_group *)malloc(sizeof(t_group));
	newgroup->next = NULL;
	newgroup->paths = paths;
	newgroup->last = newgroup;
	if (!grps)
		return (newgroup);
	grps->last->next = newgroup;
	grps->last = newgroup;
	return (grps);
}

void		freepath(t_path *newpath)
{
	t_path *tt;

	while (newpath)
	{
		tt = newpath;
		newpath = newpath->next;
		free(tt);
	}
}

void		ft_graphupdate(t_lemin *l, int u)
{
	int v;

	while (u != l->start)
	{
		if (l->checker[u])
			break ;
		l->checker[u] = 1;
		if (l->used[u])
			l->check++;
		if (u != l->goal && u != l->start)
			l->used[u] = 1;
		v = l->pred[u];
		l->graph[v][u]--;
		l->graph[u][v]++;
		u = v;
	}
}
