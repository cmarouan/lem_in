/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:39:32 by kmoussai          #+#    #+#             */
/*   Updated: 2019/09/26 20:23:55 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_inittab(t_lemin *l)
{
	int i;

	i = 0;
	while (i < l->size)
	{
		l->pred[i] = -1;
		l->visited[i] = 0;
		l->checker[i] = 0;
		i++;
	}
	l->visited[l->start] = 1;
	l->pred[l->start] = -1;
}

int			bfs(t_lemin *l, int i, int v, t_adj *tmp)
{
	ft_inittab(l);
	l->queue = ft_enqueue(NULL, ft_createelm(l->start));
	while (l->queue)
	{
		l->queue = ft_dequeue(l->queue, &v);
		tmp = l->adj[v];
		while (tmp)
		{
			i = tmp->node;
			if (!l->visited[i] && l->tmp[v][i] == '1' && i != 0)
			{
				if (l->used[v] && !l->used[l->pred[v]] && !l->used[i])
					l->visited[v] = 0;
				else
				{
					l->visited[i] = 1;
					l->pred[i] = v;
					l->queue = ft_enqueue(l->queue, ft_createelm(i));
				}
			}
			tmp = tmp->next;
		}
	}
	return (l->visited[l->goal] == 1);
}

char		**fordfulkerson(t_lemin *l)
{
	t_listpath	*paths;
	t_path		*newpath;

	paths = NULL;
	l->check = 1;
	while (bfs(l, 0, 0, NULL))
	{
		l->nopath = 1;
		l->check = 0;
		newpath = ft_pathbuilder(l, NULL, l->goal);
		if (l->check == 0)
			paths = addpath(paths, newpath, l->n_ant);
		else
			freepath(newpath);
	}
	if (l->nopath == 0)
		ft_outerror();
	l->groups = addgroup(l->groups, paths);
	return (l->tmp);
}
