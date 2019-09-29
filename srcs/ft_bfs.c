/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:39:32 by kmoussai          #+#    #+#             */
/*   Updated: 2019/09/29 21:33:27 by kmoussai         ###   ########.fr       */
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

int			bfs_sp(t_lemin *l, int i, int v, t_adj *tmp)
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
			if (!l->visited[i] && i != 0 && l->graph[v][i] >= '1')
			{
				l->visited[i] = 1;
				l->pred[i] = v;
				l->queue = ft_enqueue(l->queue, ft_createelm(i));
			}
			tmp = tmp->next;
		}
	}
	return (l->visited[l->goal] == 1);
}

int			bfs_nulledge(t_lemin *l, int i, int v, t_adj *tmp)
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
			if (!l->visited[i] && l->tmp[v][i] == '0' && i != 0)
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

t_path		*ft_pathbuilder_nulledge(t_lemin *l, t_path *newpath, int u)
{
	int v;

	while (u != l->start)
	{
		if (l->checker[u])
			break ;
		l->checker[u] = 1;
		if (l->used[u])
			l->check_used++;
		newpath = addnode(newpath, u);
		if (u != l->goal && u != l->start)
			l->used[u] = 1;
		v = l->pred[u];
		l->tmp[v][u]++;
		u = v;
	}
	if (u == l->start)
		newpath = addnode(newpath, u);
	return (newpath);
}

void		copy_graph(t_lemin *lemin)
{
	int		u;
	t_adj	*tmp;

	u = 0;
	while (u < lemin->size)
	{
		tmp = lemin->adj[u];
		lemin->used[u] = 0;
		while (tmp)
		{
			lemin->tmp[u][tmp->node] = lemin->graph[u][tmp->node];
			tmp = tmp->next;
		}
		u++;
	}
}
