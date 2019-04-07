/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:48:55 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/12 17:02:25 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	size_t			j;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)(s + i));
	if (j + 1)
		return ((char *)(s + j));
	return (NULL);
}
