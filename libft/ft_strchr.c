/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:06:34 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/12 17:00:11 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)(s + i));
	return (NULL);
}
