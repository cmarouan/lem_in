/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 13:13:24 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/07 19:48:12 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*s;

	s = (unsigned char *)s2;
	i = ft_strlen(s1);
	j = 0;
	while (s[j] && j < n)
	{
		s1[i] = s[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
