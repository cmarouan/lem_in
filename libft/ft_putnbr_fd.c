/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:50:04 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/11 14:52:46 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int nbr;

	nbr = nb;
	if (nbr >= 0)
		if (nbr / 10 == 0)
			ft_putchar_fd((char)((nbr % 10) + 48), fd);
		else
		{
			ft_putnbr_fd(nbr / 10, fd);
			ft_putchar_fd((char)((nbr % 10) + 48), fd);
		}
	else
	{
		ft_putchar_fd('-', fd);
		if (nbr == -2147483648)
		{
			ft_putnbr_fd(nbr / 10 * -1, fd);
			ft_putchar_fd('8', fd);
		}
		else
			ft_putnbr_fd(nbr * -1, fd);
	}
}
