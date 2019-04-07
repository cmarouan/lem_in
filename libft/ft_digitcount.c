/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digitcount.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 12:00:52 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/11 12:16:11 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_digitcount(unsigned int n)
{
	size_t c;

	c = 0;
	while (n / 10 != 0)
	{
		c++;
		n = n / 10;
	}
	return (++c);
}
