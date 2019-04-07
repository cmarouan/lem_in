/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 13:08:20 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/07 17:06:15 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*s;

	s = (char *)s2;
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s[j])
	{
		s1[i] = s[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
