/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:17:33 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/01 15:49:19 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map_line	*create_map_line(int size, t_dot *dots)
{
	t_map_line *new;

	if (!(new = malloc(sizeof(t_map_line))))
		return (NULL);
	new->size = size;
	new->dots = dots;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	append_map_line(t_map_line **map_lines, t_map_line *new)
{
	t_map_line *current;

	if (!new)
		return ;
	if (!*map_lines)
	{
		*map_lines = new;
		(*map_lines)->prev = NULL;
		(*map_lines)->next= NULL;
		return ;
	}
	current = *map_lines;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
}

void	print_map_lines(t_map_line *map_line)
{
	int i;

	if (!map_line)
		printf("(null)\n");
	while (map_line)
	{
		i = -1;
		while (++i < map_line->size)
		{
			printf("(%.2f", map_line->dots[i].x);
			printf(" | %.2f", map_line->dots[i].y);
			printf(" | %.2f)", map_line->dots[i].z);
			if (i != map_line->size - 1)
				printf(", ");
		}
		printf("\n");
		map_line = map_line->next;
	}
}

void	print_map(t_map *map)
{
	if (!map)
		printf("NULL\n");
	print_map_lines(map->map_lines);
	printf("max : (%f, %f)\n", map->max.x, map->max.y);
	printf("min : (%f, %f)\n", map->min.x, map->min.y);
}

void	free_map(t_map_line **map_lines)
{
	t_map_line *tmp;

	while (*map_lines)
	{
		free((*map_lines)->dots);
		tmp = *map_lines;
		*map_lines = (*map_lines)->next;
	}
}
