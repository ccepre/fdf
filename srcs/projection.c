/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:49:12 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/03 16:12:45 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	compare_extremities(t_map *map, double x, double y, int initialized)
{
	if (!initialized)
	{
		map->max.x = x;
		map->min.x = x;
		map->min.y = y;
		map->max.y = y;
		return ;
	}
	map->max.x = x > map->max.x ? x : map->max.x;
	map->min.x = x < map->min.x ? x : map->min.x;
	map->min.y = y < map->min.y ? y : map->min.y;
	map->max.y = y > map->max.y ? y : map->max.y;
}

void	center_map(t_env *env, t_dot *center, t_dot *min, t_dot *max)
{
	env->trans.x = center->x - (min->x + (max->x - min->x) / 2);
	env->trans.y = center->y - (min->y + (max->y - min->y) / 2);
}

void	isometric_projection(t_dot *dot)
{
	int x;
	int y;

	x = dot->x;
	y = dot->y;
	dot->x = (x - y) * cos(0.523599);
	dot->y = (x + y) * sin(0.523599) - dot->z;
}

void	cancel_isometric_projection(t_dot *dot)
{
	int x;
	int y;

	x = dot->x;
	y = dot->y;
	dot->y = ((y + dot->z) / sin(0.523599) - x / cos(0.523599)) / 2;
	dot->x = x / cos(0.523599) + dot->y;
}

void	map_cancel_iso(t_map *map)
{
	int i;
	t_map_line	*current;
	int			initialized;

	current = map->map_lines;
	initialized = 0;
	while (current)
	{
		i = -1;
		while (++i < current->size)
		{
			cancel_isometric_projection(&current->dots[i]);
			compare_extremities(map, current->dots[i].x,\
					current->dots[i].y, initialized);
			if (!current->prev && i == 0)
				initialized = 1;
		}
		current = current->next;
	}
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
	int			initialized;

	current = map->map_lines;
	initialized = 0;
	while (current)
	{
		i = -1;
		while (++i < current->size)
		{
			current->dots[i].x += x_trans;
			current->dots[i].y += y_trans;
			compare_extremities(map, current->dots[i].x,\
					current->dots[i].y, initialized);
			if (!current->prev && i == 0)
				initialized = 1;
		}
		current = current->next;
	}
}

void	update_map(t_map *map, t_env *env, int iso_proj)
{
	int i;
	t_map_line	*current;
	int			initialized;

	current = map->map_lines;
	initialized = 0;
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
			compare_extremities(map, current->dots[i].x,\
					current->dots[i].y, initialized);
			if (!current->prev && i == 0)
				initialized = 1;
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
	print_map(map);
	update_map(map, env, 1);
	print_map(map);
	env->zoom = 0;
	trans_x = (SCREEN_WIDTH - map->max.x + map->min.x) / 2;
	trans_x = map->min.x < 0 ? trans_x - map->min.x : trans_x;
	trans_y = (SCREEN_HEIGHT- map->max.y + map->min.y) / 2;
	trans_y = map->min.y < 0 ? trans_y - map->min.y : trans_y;
	translation(map, trans_x, trans_y);
//	print_map(map);
}
