/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:31:52 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/12 15:52:05 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*p;
	size_t	i;
	size_t	c;

	p = NULL;
	i = 0;
	if (s && f)
	{
		c = ft_strlen(s);
		p = (char *)malloc(c + 1);
		if (p == NULL)
			return (NULL);
		while (i < c)
		{
			p[i] = f(s[i]);
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}
