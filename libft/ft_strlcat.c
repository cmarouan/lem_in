/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 22:22:51 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/12 16:49:30 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	h;
	char	*s;

	h = 0;
	s = (char *)src;
	i = ft_strlen(dst);
	j = ft_strlen(s);
	if (i > size)
		j = j + size;
	else
		j = j + i;
	while (s[h] && (i + 1) < size)
	{
		dst[i] = s[h];
		h++;
		i++;
	}
	dst[i] = '\0';
	return (j);
}
