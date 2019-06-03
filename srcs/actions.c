/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:54:54 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/01 16:21:50 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(int button, t_env *env, t_map *map)
{
	int	diff_max;
	int	diff_min;

	if (button == 4) 
		env->zoom = 0.9;
	else 
		env->zoom = 1.1;
//	diff_max = (map->max.x - map->max.x * env->zoom) / 2;
//	diff_min = (map->min.x - map->min.x * env->zoom) / 2;
	diff_max = (map->max.x - map->max.x * env->zoom);
	diff_min = (map->min.x - map->min.x * env->zoom);
	env->trans.x = (diff_max - diff_min) / 2;
//	env->trans.x = abs(diff_max) > abs(diff_min) ? diff_max : diff_min;
//	diff_max = (map->max.y - map->max.y * env->zoom) / 2;
//	diff_min = (map->min.y - map->min.y * env->zoom) / 2;
	diff_max = (map->max.y - map->max.y * env->zoom);
	diff_min = (map->min.y - map->min.y * env->zoom);
//	env->trans.y = abs(diff_max) > abs(diff_min) ? diff_max : diff_min;
	env->trans.y = (diff_max - diff_min) / 2;
	printf("trans : (%f, %f)\n", env->trans.x, env->trans.y);
	update_map(&env->map, env, 0);
	env->trans.x = 0;
	env->trans.y = 0;
	env->zoom = 0;
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	draw_map(&env->map, env);
	print_map(map);
}

int mouse_press(int button, int x, int y, void *param)
{
	t_env *env;
	t_key *mouse_button;

	printf("mouse press : %d\n", button);
	if (button != 1 && button != 4 && button != 5)
		return (0);
	env = (t_env*)param;
	if (button == 1)
	{
		if (!(mouse_button = create_key(button)))
			return (-1);
		append_key(&env->mouse_buttons, mouse_button);
		env->mouse_pos.x = x;
		env->mouse_pos.y = y;
	}
	else if (button == 4 || button == 5)
		zoom(button, env, &env->map);
	return (0);
}

int mouse_release(int button, int x, int y, void *param)
{
	t_env *env;

	if (button != 1 && button != 4 && button != 5)
		return (0);
	env = (t_env*)param;
	remove_elem(&env->mouse_buttons, button);
	return (0);
}

int mouse_move(int x, int y, void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (!env->mouse_buttons)
		return (0);
	printf("------------- MOUSE MOVE ------------\n");
	print_keys(env->mouse_buttons);
	if (search_key(env->mouse_buttons, 1))
	{
		env->trans.x = -(env->mouse_pos.x - x);
		env->trans.y = -(env->mouse_pos.y - y);
		update_map(&env->map, env, 0);
		env->trans.x = 0;
		env->trans.y = 0;
		env->mouse_pos.x = x;
		env->mouse_pos.y = y;
	}
	printf("update done\n");
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	draw_map(&env->map, env);
	return (0);
}

int key_press(int keycode, void *param)
{
	t_env *env;

	env = (t_env*)param;
//	if (keycode == 24)
//	{
//		env->relief
//	}
//	if (keycode == 27)
	return (0);
}


int key_release(int keycode, void *param)
{
	return (0);
}
