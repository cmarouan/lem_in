/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:54:37 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/07 13:03:44 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t	i;
	char	*s;

	s = (char *)src;
	i = 0;
	while (i < len && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	while (i < len)
		dest[i++] = '\0';
	return (dest);
}
