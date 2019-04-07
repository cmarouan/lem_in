/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:33:40 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/07 16:26:36 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	size_t	i;
	char	*res;
	char	*t;

	t = (char *)src;
	i = 0;
	len = 0;
	while (t[len])
		len++;
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		*(res + i) = *(t + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}
