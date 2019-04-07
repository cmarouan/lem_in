/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:18:29 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/15 15:47:25 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int			i;
	long int	nbr;

	i = 0;
	nbr = 0;
	while (*str == '\t' || *str == '\n'
			|| *str == ' ' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		str++;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (str[0] == '-')
		nbr = nbr * -1;
	return ((int)nbr);
}
