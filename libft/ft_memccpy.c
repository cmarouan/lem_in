/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 13:04:33 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/15 18:58:04 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*t2;

	t2 = (unsigned char *)src;
	t = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		t[i] = t2[i];
		if (t2[i] == (unsigned char)c)
			break ;
		i++;
	}
	if (i != n)
		return (t + i + 1);
	else
		return (NULL);
}
