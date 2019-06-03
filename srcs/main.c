/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:31:22 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/03 14:41:58 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	env_initialization(t_env *env)
{
	env->keys = NULL;
	env->zoom = 0;
	env->relief = 0;
	env->trans.x = 0;
	env->trans.y = 0;
	env->mouse_buttons = NULL;
	env->map.map_lines = NULL;
}

int main(int ac, char **av)
{
	t_env	env;
	int ret;

	if (ac != 2)
		return (0);
	env_initialization(&env);
	if ((ret = parsing(&env.map, av[1])))
		return (ret);
	if (!(env.mlx_ptr = mlx_init()))
		return (-1); 
	if (!(env.win_ptr = mlx_new_window(env.mlx_ptr, SCREEN_WIDTH,\
					SCREEN_HEIGHT, "super title")))
		return (-1); 
	init_map(&(env.map), &env);
	draw_map(&env.map, &env);
	mlx_hook(env.win_ptr, 4, 0, &mouse_press, (void*)&env);
	mlx_hook(env.win_ptr, 5, 0, &mouse_release, (void*)&env);
	mlx_hook(env.win_ptr, 6, 0, &mouse_move, (void*)&env);
	mlx_hook(env.win_ptr, 2, 0, &key_press, (void*)&env);
	mlx_hook(env.win_ptr, 3, 0, &key_release, (void*)&env);
	mlx_loop(env.mlx_ptr);
	free_map(&(env.map.map_lines));
	return (0);
}
