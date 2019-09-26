/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:15:47 by kmoussai          #+#    #+#             */
/*   Updated: 2019/09/26 20:27:17 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*ft_createelm(int node)
{
	t_queue *elm;

	elm = (t_queue *)malloc(sizeof(t_queue));
	elm->next = NULL;
	elm->node = node;
	return (elm);
}

t_queue		*ft_enqueue(t_queue *queue, t_queue *new)
{
	t_queue *tmp;

	tmp = queue;
	if (!tmp)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (queue);
}

t_queue		*ft_dequeue(t_queue *queue, int *v)
{
	t_queue *tmp;

	*v = -1;
	if (!queue)
		return (NULL);
	*v = queue->node;
	tmp = queue;
	queue = queue->next;
	free(tmp);
	return (queue);
}
