/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funcions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:01:37 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/03 15:13:44 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	fpart(double x)
{
	return (x - floor(x));
}

double	normal_distribution(double x, double theta, double mu)
{
	if (!theta)
		return (0);
	return ((1 / sqrt(2 * M_PI * theta)) * exp(pow(x-mu, 2) / -(2 * theta)));
}

int		grey_color(double opacity)
{
	int result;
	int value;
	
	opacity = normal_distribution(opacity, 0.3, 1);
	value = opacity * 255;
	result = value + (value << 8) + (value << 16);
	return (result);
}

void	adapt_dots(int *steep, int *rev, t_dot *a, t_dot *b)
{
	if (*rev)
	{
		ft_swap(&a->x, &b->x);
		ft_swap(&a->y, &b->y);
	}
	if (*steep)
	{
		ft_swap(&b->y, &b->x);
		ft_swap(&a->y, &a->x);
	}
	if (a->x > b->x && !*rev)
	{
		ft_swap(&a->x, &b->x);
		ft_swap(&a->y, &b->y);
		*rev = 1;
	}
}

void	put_dot(t_env *env, int x, int y, int color)
{
	size_t start;
	static int i = 0;

	if (x < 0 || x > SCREEN_WIDTH - 1 || y < 0 || y > SCREEN_HEIGHT - 1)
		return ;
	start = y * env->img.size_line + x * (env->img.bits_per_pixel / 8);
	env->img.image[start] = (color & 0xFF0000) >> 16;
	env->img.image[start + 1] = (color & 0xFF00) >> 8;
	env->img.image[start + 2] = color & 0xFF;
}

void	plot_line(t_env *env, t_dot a, t_dot b)
{
	int		steep;
	int		rev;
	double	gradient;
	double	intery;
	int x;

	steep = (fabs(b.y - a.y) > fabs(b.x - a.x));
	rev = 0;
	adapt_dots(&steep, &rev, &a, &b);
	gradient = b.x - a.x == 0 ?  0 : (double)(b.y - a.y) / (double)(b.x - a.x);
	x = a.x;
	intery = a.y;
	while (x++ < b.x)
	{
		if (steep)
		{
			put_dot(env, floor(intery), x, grey_color(1 - fpart(intery)));
			put_dot(env, floor(intery) + 1, x, grey_color(fpart(intery)));
		}
		else
		{
			put_dot(env, x, floor(intery), grey_color(1 - fpart(intery)));
			put_dot(env, x, floor(intery) + 1, grey_color(fpart(intery)));
		}
		intery += gradient;
	}
	adapt_dots(&steep, &rev, &a, &b);
}

void	draw_map(t_map *map, t_env *env)
{
	t_map_line	*current;
	int			i;

	env->img.img_ptr = mlx_new_image (env->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	env->img.image = mlx_get_data_addr(env->img.img_ptr,\
			&env->img.bits_per_pixel, &env->img.size_line, &env->img.endian );
	current = map->map_lines;
	while (current)
	{
		i = -1;
		while (++i < current->size)
		{
			if (i > 0)
				plot_line(env, current->dots[i - 1], current->dots[i]);
			if (i < current->size - 1)
				plot_line(env, current->dots[i], current->dots[i + 1]);
			if (current->prev)
				plot_line(env, current->prev->dots[i], current->dots[i]);
			if (current->next)
				plot_line(env, current->dots[i], current->next->dots[i]);
		}
		current = current->next;
	}
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.img_ptr, 0, 0);
}
