/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:38:33 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/11 14:39:51 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	int nbr;

	nbr = nb;
	if (nbr >= 0)
		if (nbr / 10 == 0)
			ft_putchar((char)((nbr % 10) + 48));
		else
		{
			ft_putnbr(nbr / 10);
			ft_putchar((char)((nbr % 10) + 48));
		}
	else
	{
		ft_putchar('-');
		if (nbr == -2147483648)
		{
			ft_putnbr(nbr / 10 * -1);
			ft_putchar('8');
		}
		else
			ft_putnbr(nbr * -1);
	}
}
