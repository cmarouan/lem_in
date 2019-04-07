/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 22:26:22 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/15 15:22:42 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *t, size_t len)
{
	size_t			i;
	size_t			j;
	size_t			h;
	unsigned char	*to_find;
	unsigned char	*str;

	str = (unsigned char *)s;
	to_find = (unsigned char *)t;
	i = 0;
	if (!to_find[i] || to_find == str)
		return ((char *)str);
	while (str[i] && i < len)
	{
		h = i;
		j = 0;
		while (str[h] == to_find[j] && to_find[j])
		{
			h++;
			j++;
		}
		if (!to_find[j] && (i + j) <= len)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
