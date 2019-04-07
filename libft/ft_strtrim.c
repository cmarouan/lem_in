/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 21:19:38 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/15 19:00:30 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lastchar(char *s)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n')
			j = i;
		s++;
		i++;
	}
	return (j);
}

char			*ft_strtrim(char const *str)
{
	char			*s;
	char			*p;
	unsigned int	i;
	size_t			j;

	p = NULL;
	if (str)
	{
		i = 0;
		s = (char *)str;
		while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
			i++;
		if (!s[i])
			return (ft_strdup(""));
		j = ft_lastchar(s) + 1;
		if ((p = (char *)malloc(j - i + 1)) == NULL)
			return (NULL);
		ft_memcpy(p, s + i, j - i);
		p[j - i] = 0;
	}
	return (p);
}
