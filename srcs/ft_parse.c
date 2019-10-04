/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 13:52:33 by cmarouan          #+#    #+#             */
/*   Updated: 2019/10/04 11:49:22 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lemin			*ft_readallnode(char **line, t_lemin *lemin)
{
	while (get_next_line(0, line))
	{
		lemin->lines = ft_addline(lemin->lines, *line);
		if (!ft_strcmp("##start", *line))
		{
			lemin = ft_readnode(NULL, START, lemin);
			lemin->fstart = 1;
		}
		else if (!ft_strcmp("##end", *line))
		{
			lemin = ft_readnode(NULL, END, lemin);
			lemin->fend = 1;
		}
		else if (!ft_strncmp("#", *line, 1))
			continue;
		else if (ft_linetype(*line) == ROOM)
			lemin = ft_readnode(*line, ROOM, lemin);
		else
			break ;
		lemin->size++;
	}
	return (lemin);
}

t_lemin			*ft_readnode(char *line, int node_name, t_lemin *lemin)
{
	char		**tab;
	int			i;

	if (!line)
	{
		if ((lemin->fend == 1 && node_name == END) ||
		(lemin->fstart == 1 && node_name == START))
			ft_outerror(DOUBLE_START_OR_END);
		get_next_line(0, &line);
		lemin->lines = ft_addline(lemin->lines, line);
	}
	if (ft_linetype(line) != ROOM)
		ft_outerror(NODE_DATA_ERR);
	tab = ft_strsplit(line, ' ');
	if (tab[0] == NULL || tab[1] == NULL || tab[2] == NULL
		|| tab[3] != NULL || tab[0][0] == 'L')
		ft_outerror(NODE_DATA_ERR);
	ft_add_node(&lemin->nodes, ft_create_node(node_name, ft_strdup(tab[0]),
				ft_atoli(tab[1]), ft_atoli(tab[2])));
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (lemin);
}

t_lemin			*ft_readlink(t_lemin *lemin, char *line)
{
	if (!line)
		ft_outerror(LINK_ERR);
	ft_fillgraph(lemin, line);
	while (get_next_line(0, &line))
	{
		lemin->lines = ft_addline(lemin->lines, line);
		if (!ft_strncmp("#", line, 1))
			continue;
		else
			ft_fillgraph(lemin, line);
	}
	return (lemin);
}

int				ft_linetype(char *line)
{
	int			c;
	int			c2;

	c = 0;
	c2 = 0;
	while (*line)
	{
		if (*line == ' ')
			c++;
		else if (*line == '-')
			c2++;
		line++;
	}
	if (c == 2 && c2 == 0)
		return (ROOM);
	else if (c2 == 1 && c == 0)
		return (LINK);
	else if (c != 0 || c2 != 0)
		ft_outerror((c != 0 ? NODE_DATA_ERR : LINK_ERR));
	return (ERROR);
}

int				ft_getindex(char *name, char **names, int size)
{
	int			i;
	int			c;
	int			index;

	i = 0;
	c = 0;
	if (!name)
		return (-1);
	while (i < size)
	{
		if (!ft_strcmp(name, names[i]))
		{
			c++;
			index = i;
		}
		i++;
	}
	if (c == 1)
		return (index);
	return (-1);
}
