/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:25:22 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/12 17:24:29 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	p = ft_strnew(len);
	if (s && len)
	{
		if (p == NULL)
			return (NULL);
		i = 0;
		while (i < len)
		{
			p[i] = s[start];
			i++;
			start++;
		}
		p[i] = '\0';
	}
	return (p);
}
