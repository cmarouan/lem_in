/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 11:49:12 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/11 14:54:47 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int			s;
	size_t		len;
	char		*p;
	long int	nbr;

	nbr = (long int)n;
	s = -1;
	if (nbr < 0)
	{
		s = 0;
		nbr = nbr * -1;
	}
	len = ft_digitcount(nbr);
	if ((p = ft_strnew(len + s + 1)) == NULL)
		return (NULL);
	while (nbr / 10 != 0)
	{
		p[len + s] = (nbr % 10) + 48;
		nbr = nbr / 10;
		len--;
	}
	p[len-- + s] = nbr + 48;
	if (!s)
		p[len + s] = '-';
	return (p);
}
