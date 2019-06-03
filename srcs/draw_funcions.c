/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funcions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:01:37 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/01 16:42:40 by ccepre           ###   ########.fr       */
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

/*
void	plot_parallelogram(t_env *env, int width, int height, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
			mlx_pixel_put(env->mlx_ptr, env->win_ptr, env->x + i, env->y + j, color);
	}
}
*/

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

void	plot_dots(t_env *env, int steep, double intery, double x)
{
	if (steep)
	{
		mlx_pixel_put(env->mlx_ptr, env->win_ptr, floor(intery), x,\
				grey_color(1 - fpart(intery)));
		mlx_pixel_put(env->mlx_ptr, env->win_ptr, floor(intery) + 1, x,\
				grey_color(fpart(intery)));
	}
	else
	{
		mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, floor(intery),\
				grey_color(1 - fpart(intery)));
		mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, floor(intery) + 1,\
				grey_color(fpart(intery)));
	}
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
		plot_dots(env, steep, intery, x);
		intery += gradient;
	}
	adapt_dots(&steep, &rev, &a, &b);
}

void	draw_map(t_map *map, t_env *env)
{
	t_map_line	*current;
	int			i;

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
}
