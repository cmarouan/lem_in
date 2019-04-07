/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 22:22:44 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/07 13:22:44 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;
	int h;

	i = 0;
	if (!to_find[i])
		return ((char *)str);
	while (str[i])
	{
		h = i;
		j = 0;
		while (str[h] == to_find[j] && to_find[j])
		{
			h++;
			j++;
		}
		if (!to_find[j])
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
