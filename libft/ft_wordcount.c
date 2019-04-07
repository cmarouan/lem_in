/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 10:25:34 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/11 15:05:42 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount(char const *str, char charset)
{
	size_t	it[2];
	size_t	index;
	size_t	wordcount;

	it[0] = 0;
	it[1] = 0;
	index = 0;
	wordcount = 0;
	while (str[it[0]])
		it[0]++;
	while (it[1] < it[0])
	{
		while (str[it[1]] == charset)
			it[1]++;
		index = ft_nextindexof(str, it[1], charset);
		if (index - it[1] != 0)
			wordcount++;
		it[1] = index + 1;
	}
	return (wordcount);
}
