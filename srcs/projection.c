/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:49:12 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/01 15:51:04 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_dot *dot)
{
	int x;
	int y;

	x = dot->x;
	y = dot->y;
//	dot->x = (x - dot->z) * cos(0.46365);
//	dot->y = y + (x + dot->z) * sin(0.46365);
	dot->x = (x - y) * cos(0.523599);
	dot->y = (x + y) * sin(0.523599) - dot->z;
}

void	spacing(t_dot *dot, double gap, double z_gap)
{
	if (gap)
	{
		dot->x *= gap;
		dot->y *= gap;
	}
	if (z_gap)
		dot->z *= z_gap;
}

void	translation(t_map *map, int x_trans, int y_trans)
{
	int i;
	t_map_line	*current;

	current = map->map_lines;
	while (current)
	{
		i = -1;
		while (++i < current->size)
		{
			current->dots[i].x += x_trans;
			current->dots[i].y += y_trans;
		}
		current = current->next;
	}
	printf("translation : %d | %d\n", x_trans, y_trans);
}

void	compare_extremities(t_map *map, double x, double y)
{
	map->max.x = x > map->max.x ? x : map->max.x;
	map->min.x = x < map->min.x ? x : map->min.x;
	map->min.y = y < map->min.y ? y : map->min.y;
	map->max.y = y > map->max.y ? y : map->max.y;
}

void	update_map(t_map *map, t_env *env, int iso_proj)
{
	int i;
	t_map_line	*current;

	map->max.x = map->map_lines->dots[0].x;
	map->max.y = map->map_lines->dots[0].y;
	map->min.x = map->map_lines->dots[0].x;
	map->min.y = map->map_lines->dots[0].y;
	current = map->map_lines;
	while (current)
	{
		i = -1;
		while (++i < current->size)
		{
			spacing(&current->dots[i], env->zoom, env->zoom / 10);
			if (iso_proj)
				isometric_projection(&current->dots[i]);
			current->dots[i].x += env->trans.x;
			current->dots[i].y += env->trans.y;
			compare_extremities(map, current->dots[i].x, current->dots[i].y);
		}
		current = current->next;
	}
}

void	init_map(t_map *map, t_env *env)
{
	int i;
	int trans_x;
	int trans_y;

	env->zoom = ((double)4 / 10 * SCREEN_WIDTH) / map->map_lines->size;
//	ATENTION depend que de la taille du premier + que de la width
	update_map(map, env, 1);
	env->zoom = 0;
	trans_x = (SCREEN_WIDTH - map->max.x + map->min.x) / 2;
	trans_x = map->min.x < 0 ? trans_x - map->min.x : trans_x;
	trans_y = (SCREEN_HEIGHT- map->max.y + map->min.y) / 2;
	trans_y = map->min.y < 0 ? trans_y - map->min.y : trans_y;
	translation(map, trans_x, trans_y);
}


