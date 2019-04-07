/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:59:22 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/10 21:17:09 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s_len1;
	char	*p;

	p = NULL;
	if (s1 && s2)
	{
		s_len1 = ft_strlen(s1);
		p = (char*)malloc(1 + s_len1 + ft_strlen(s2));
		if (p == NULL)
			return (NULL);
		ft_strcpy(p, s1);
		while (*s2)
			p[s_len1++] = *s2++;
		p[s_len1] = '\0';
	}
	return (p);
}
