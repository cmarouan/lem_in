/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:30:27 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/07 22:30:56 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*t;
	char	*t2;

	t2 = (char *)src;
	t = (char *)dst;
	i = 0;
	while (i < n)
	{
		t[i] = t2[i];
		i++;
	}
	return (dst);
}
