/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 09:47:49 by kmoussai          #+#    #+#             */
/*   Updated: 2018/10/12 17:11:23 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *str, char charset)
{
	size_t	wordcount;
	char	**res;
	size_t	i;
	size_t	index;

	if (str)
	{
		wordcount = ft_wordcount(str, charset) + 1;
		i = 0;
		if ((res = (char **)malloc(wordcount * 8)) == NULL)
			return (NULL);
		while (i < wordcount - 1)
		{
			while (*str == charset)
				str++;
			index = ft_nextindexof(str, 0, charset);
			if ((res[i] = ft_strnew(index)) == NULL)
				return (NULL);
			ft_strncpy(*(res + i++), str, index);
			str = str + index;
		}
		res[i] = 0;
		return (res);
	}
	return (NULL);
}
