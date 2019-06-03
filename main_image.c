/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:30:30 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/03 16:14:12 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int main()
{
	t_env	env;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*image;
	int i;
	unsigned int		color;

	if (!(env.mlx_ptr = mlx_init()))
		return (-1); 
	if (!(env.win_ptr = mlx_new_window(env.mlx_ptr, 500, 500, "super title")))
		return (-1); 
	img_ptr = mlx_new_image (env.mlx_ptr, 500, 500);
	image = mlx_get_data_addr (img_ptr, &bits_per_pixel, &size_line, &endian );
	printf("--- IMAGE PARAMS ----\n");
	printf("bits_per_pixel : %d | size_line : %d | endian : %d\n", bits_per_pixel, size_line, endian);
	color = 16777215;
	printf("color : %d\n", color);
	color = mlx_get_color_value (env.mlx_ptr, color);
	printf("color : %d\n", color);
	i = 0;
	while(i < 22000 -4)
	{
		printf("while\n");
		image[i] = (char)254;
		image[i + 1] = (char)254;
		image[i + 2] = (char)254;
		image[i + 3] = 0;
		i += 4;
	}
	i = 19999;
	while (++i < 20020)
		printf("char : %hhu\n", *(image + i));
	mlx_put_image_to_window (env.mlx_ptr, env.win_ptr, img_ptr, 0, 0);
	mlx_loop(env.mlx_ptr);
	return (0);
}
