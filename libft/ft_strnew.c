/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:36:39 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/12 15:53:51 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s;

	s = (char *)ft_memalloc(sizeof(char) * (size + 1));
	if (s == NULL)
		return (NULL);
	ft_bzero(s, size + 1);
	return (s);
}
