/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 14:23:28 by ccepre            #+#    #+#             */
/*   Updated: 2019/06/01 15:12:31 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static int	verif_elem(char *elem)
{
	int i;
	if (*elem == '+' || *elem == '-')
		elem++;
	while (*elem == '0')
		elem++;
	i = -1;
	while (elem[++i])
		if (elem[i] < 48 || elem[i] > 57)
			return (1);
	if (i > 5)
		return (1);
	return (0);
}

static int	line_manager(char *line, t_map *map, int y)
{
	char	**elems;
	int		x;
	t_dot	*dots;
	t_map_line	*map_line;

	if (!(elems = ft_strsplit(line, ' ')))
		return (-1);
	x = 0;
	while (elems[x])
		x++;
	if (!(dots = (t_dot*)malloc(sizeof(t_dot) * x)))
		return (-1);
	x = -1;
	while (elems[++x])
	{
		if (verif_elem(elems[x]))
		{
			free(dots);
			return (1);
		}
		dots[x].z = (double)ft_atoi(elems[x]);
		dots[x].x = (double)x;
		dots[x].y = (double)y;
	//	map->max.x = x > map->max.x || map->max.x == -1 ? x : map->max.x;
	//	map->min.x = x < map->min.x || map->min.x == -1 ? x : map->min.x;
	//	map->max.y = y > map->max.y || map->max.y == -1 ? y : map->max.y;
	//	map->min.y = y < map->min.y || map->min.y == -1 ? y : map->min.y;
	}
	if (!(map_line = create_map_line(x, dots)))
	{
		free(dots);
		return (-1);
	}
	append_map_line(&(map->map_lines), map_line);
	return (0);
}

int			parsing(t_map *map, const char *filename)
{
	int		fd;
	int		ret;
	int		y;
	char	*line;

//	map->max.x = -1;
//	map->max.y = -1;
//	map->min.x = -1;
//	map->min.y = -1;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	y = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		ret = line_manager(line, map, y);
		ft_strdel(&line);
		if (ret)
			return (ret);
		y++;
	}
	return (ret);
}
