/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 11:58:55 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/07 17:16:04 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*t;

	s = (unsigned char *)s1;
	t = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s[i] != t[i])
			return (s[i] - t[i]);
		i++;
	}
	return (0);
}
