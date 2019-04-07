/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nextindexof.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 10:48:52 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/17 09:27:12 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nextindexof(char const *str, size_t index, char charset)
{
	size_t	i;

	i = index;
	while (str[i] == charset)
		i++;
	while (str[i] != '\0' && str[i] != charset)
		i++;
	return (i);
}
