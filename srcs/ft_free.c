/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:44:15 by cmarouan          #+#    #+#             */
/*   Updated: 2019/09/27 13:46:11 by cmarouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			freelines(t_line *lines)
{
	t_line		*tmp;
	t_line		*last;

	last = lines->last;
	while (lines)
	{
		free(lines->line);
		tmp = lines;
		free(tmp);
		lines = lines->next;
	}
}

void			freenodes(t_nodes *nodes)
{
	t_nodes		*tmp;

	while (nodes)
	{
		free(nodes->name);
		tmp = nodes;
		nodes = nodes->next;
		free(tmp);
	}
}

void			freetab(char **names, int size)
{
	int			i;

	i = 0;
	while (i < size)
		free(names[i++]);
	free(names);
}

void			freeadj(t_adj **adj, int size)
{
	t_adj		*tmp;
	t_adj		*t;
	int			i;

	i = 0;
	while (i < size)
	{
		tmp = adj[i];
		while (tmp)
		{
			t = tmp;
			tmp = tmp->next;
			free(t);
		}
		i++;
	}
	free(adj);
}

void			freegroups(t_group *grps, t_group *temp)
{
	t_path		*ptemp;
	t_path		*pt2;
	t_listpath	*ltemp;
	t_listpath	*lt2;

	while (grps)
	{
		ltemp = grps->paths;
		temp = grps;
		while (ltemp)
		{
			ptemp = ltemp->path;
			lt2 = ltemp;
			while (ptemp)
			{
				pt2 = ptemp;
				ptemp = ptemp->next;
				free(pt2);
			}
			ltemp = ltemp->next;
			free(lt2);
		}
		grps = grps->next;
		free(temp);
	}
}
