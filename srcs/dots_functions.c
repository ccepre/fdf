/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:30:17 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/30 16:48:51 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot *create_dot(int x, int y, int z)
{
	t_dot *new;

	if (!(new = malloc(sizeof(t_dot))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->next = NULL;
	return (new);
}

void	append_dot(t_dot **dots, t_dot *new)
{
	if (!new)
		return ;
	if (!(*dots))
	{
		*dots = new;
		return ;
	}
	new->next = *dots;
	(*dots) = new;
}

void	display_dots(t_dot *dots)
{
	int i;

	i = 0;
	if (!dots)
		printf("NULL\n");
	while (dots)
	{
		printf("----- dot : %d -----\n", i);
		printf("x : %d | y : %d | y : %d\n", dots->x, dots->y, dots->z);
		i++;
		dots = dots->next;
	}
}
