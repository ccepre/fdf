/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:56:59 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/03 15:03:24 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

typedef struct	s_dot
{
	double			x;
	double			y;
	double			z;
}				t_dot;

typedef struct	s_map_line
{
	int					size;
	t_dot				*dots;
	struct s_map_line	*next;
	struct s_map_line	*prev;
}				t_map_line;

typedef struct	s_map
{
	t_map_line	*map_lines;
	t_dot		max;
	t_dot		min;
}				t_map;

typedef struct	s_key
{
	int 			keycode;
	struct s_key	*next;
}				t_key;

typedef struct	s_image
{
	void	*img_ptr;
	int 	bits_per_pixel;
	int		size_line;
	int		endian;
	char	*image;
}				t_image;

typedef struct	s_env
{
		void 	*mlx_ptr;
		void 	*win_ptr;
		t_key	*mouse_buttons;
		t_key	*keys;
		t_dot	mouse_pos;
		t_dot	trans;
		double	zoom;
		double	relief;
		t_map	map;
		t_image	img;
}				t_env;

void			remove_elem(t_key **keys, int keycode);
void			append_key(t_key **keys, t_key *new);
t_key			*create_key(int keycode);
int				search_key(t_key *keys, int keycode);
void			print_keys(t_key *keys);

void	plot_line(t_env *env, t_dot a, t_dot b);
void	draw_map(t_map *map, t_env *env);

int		parsing(t_map *map, const char *filename);

int			mouse_press(int button, int x, int y, void *param);
int			mouse_release(int button, int x, int y, void *param);
int 		mouse_move(int x, int y, void *param);
int			key_press(int keycode, void *params);
int			key_release(int keycode, void *params);

void		append_dot(t_dot **dots, t_dot *new);
t_dot		*create_dot(int x, int y, int z);
void		display_dots(t_dot *dots);

t_map_line	*create_map_line(int size, t_dot *dots);
void		append_map_line(t_map_line **map_lines, t_map_line *new);
void		print_map(t_map *map);
void		print_map_lines(t_map_line *map_line);
void		free_map(t_map_line **map_lines);

void	center_map(t_env *env, t_dot *center, t_dot *min, t_dot *max);

void	init_map(t_map *map, t_env *env);
void	update_map(t_map *map, t_env *env, int iso_proj);
void	map_cancel_iso(t_map *map);

#endif
