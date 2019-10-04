/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:34:55 by cmarouan          #+#    #+#             */
/*   Updated: 2019/10/04 11:10:57 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_outerror(void)
{
	ft_putstr("ERROR\n");
	exit(ERROR);
}

void	freearrays(t_arrays *arr)
{
	t_arrays	*temp;

	while (arr)
	{
		temp = arr;
		arr = arr->next;
		free(temp->patharray);
		free(temp);
	}
}

void	allfreefunction(t_lemin *lemin, t_arrays *s)
{
	freelines(lemin->lines);
	freenodes(lemin->nodes);
	freetab(lemin->names, lemin->size);
	freetab(lemin->graph, lemin->size);
	freetab(lemin->tmp, lemin->size);
	freeadj(lemin->adj, lemin->size);
	free(lemin->used);
	free(lemin->visited);
	free(lemin->pred);
	free(lemin->checker);
	freegroups(lemin->groups, NULL);
	freearrays(s);
	free(lemin);
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
		ft_outerror();
}

int		main(void)
{
	t_lemin			*lemin;
	t_group			*teemp;
	t_listpath		*p;

	lemin = initlemin(NULL);
	initfunct(lemin, 0, -1, -1);
	solve(lemin);
	teemp = best_groups(lemin);
	teemp->stop = 0;
	p = teemp->paths;
	while (p)
	{
		p = p->next;
		teemp->stop++;
	}
	ft_printlines(lemin->lines);
	if (teemp->paths->path->size == 2)
	{
		passallants(lemin->n_ant, lemin, teemp->paths->path);
		return (0);
	}
	lemin->arrays = createarrays(teemp);
	pass_ants(lemin->arrays, lemin->n_ant, lemin, teemp->paths);
	allfreefunction(lemin, lemin->arrays);
	return (0);
}
