/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 17:21:44 by cmarouan          #+#    #+#             */
/*   Updated: 2019/10/04 11:04:53 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*ft_concat(char *src, char *c)
{
	char	*new;
	int		size;

	size = ft_strlen(src);
	new = ft_strnew(size + 1);
	new = ft_strcpy(new, src);
	free(src);
	new[size] = *c;
	return (new);
}

int		get_next_line(const int fd, char **line)
{
	char *r;
	char *src;
	char c;

	src = ft_strnew(1);
	r = ft_strnew(1);
	while (read(fd, r, 1))
	{
		if (r[0] == '\n')
			break ;
		src = ft_concat(src, r);
	}
	c = r[0];
	free(r);
	*line = src;
	if (ft_strlen(src) > 0 || c == '\n')
		return (1);
	free(src);
	return (0);
}
