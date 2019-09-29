/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 17:21:44 by cmarouan          #+#    #+#             */
/*   Updated: 2019/09/29 18:48:16 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		back_n(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	if (i == 0 && s[0] != '\n' && s[0] != '\0')
		return (ft_strlen(s));
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char	*s;
	char	buff[BUFF_SIZE + 1];
	int		i;
	char	*temp;
	int		rd;

	rd = 0;
	s = NULL;
	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	s = ft_strnew(1);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		temp = s;
		s = ft_strjoin(s, buff);
		free(temp);
		if (fd == 0 && back_n(s))
			break ;
	}
	if ((i = back_n(s)) != 0)
		rd = 1;
	*line = ft_strsub(s, 0, i);
	free(s);
	return (rd);
}
