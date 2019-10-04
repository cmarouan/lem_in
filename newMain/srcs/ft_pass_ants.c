/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:21:29 by cmarouan          #+#    #+#             */
/*   Updated: 2019/09/29 13:16:08 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			*getname(t_lemin *lemin, t_path *path, int index)
{
	int			i;
	char		*name;
	t_path		*temp;

	temp = path;
	i = 0;
	while (temp)
	{
		if (i == index)
		{
			name = lemin->names[temp->node];
			return (name);
		}
		i++;
		temp = temp->next;
	}
	return (NULL);
}

void			passallants(int ants, t_lemin *lemin, t_path *path)
{
	int			i;

	i = 0;
	while (i < ants)
	{
		i++;
		ft_putstr("L");
		ft_putnbr(i);
		ft_putstr("-");
		ft_putstr(getname(lemin, path, 1));
		if (i != ants)
			ft_putstr(" ");
	}
	ft_putstr("\n");
}

void			ft_print(int ant, t_lemin *lemin, t_listpath *paths, int size)
{
	ft_putstr("L");
	ft_putnbr(ant);
	ft_putstr("-");
	ft_putstr(getname(lemin, paths->path, size + 1));
	ft_putstr(" ");
}

t_passant		onemove(t_lemin *l, t_listpath *p, t_passant var, t_arrays *s)
{
	while (var.size > 0)
	{
		if (s->patharray[var.size] != 0)
		{
			if (var.size == s->size - 2)
				s->patharray[var.size + 1] += 1;
			else
			{
				s->patharray[var.size + 1] = s->patharray[var.size];
				ft_print(s->patharray[var.size + 1], l, p, var.size);
			}
			s->patharray[var.size] = 0;
		}
		var.size--;
		if (var.size == 0 && s->patharray[var.size] > 0)
		{
			s->patharray[var.size + 1] = var.nameant;
			var.nameant++;
			ft_print(s->patharray[var.size + 1], l, p, var.size);
			s->patharray[var.size] -= 1;
		}
	}
	return (var);
}

void			pass_ants(t_arrays *s, int n_ant, t_lemin *l, t_listpath *p)
{
	t_passant	var;
	t_arrays	*temp;
	t_listpath	*temppath;

	var.nameant = 1;
	temp = s;
	temppath = p;
	var.done = 0;
	var.nb = n_ant;
	while (var.done < n_ant)
	{
		while (s)
		{
			var.size = s->size - 2;
			s->patharray[var.size + 1] = var.done;
			var = onemove(l, p, var, s);
			var.done = s->patharray[s->size - 1];
			p = p->next;
			s = s->next;
		}
		s = temp;
		p = temppath;
		if (var.done != n_ant)
			ft_putstr("\n");
	}
}
