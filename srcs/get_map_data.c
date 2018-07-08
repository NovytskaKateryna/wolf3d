/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:17:55 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:30:30 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		side_of_wall(t_grid *map, int j, int side, int value)
{
	if (side == 1)
		map->side[j].north = value;
	else if (side == 2)
		map->side[j].south = value;
	else if (side == 3)
		map->side[j].east = value;
	if (side == 3)
		j++;
	return (j);
}

int		one_line_info(t_grid *map, char *line, int h, int j)
{
	int	w;
	int	i;
	int	side;

	w = 0;
	i = -1;
	side = 0;
	map->map[h] = (int*)malloc(sizeof(int) * map->width);
	while (line[++i])
	{
		if (line[i] >= '0' && line[i] <= '5')
		{
			if (side == 0)
			{
				map->side[j].west = line[i] - 48;
				map->map[h][w++] = line[i] - 48;
			}
			else
				j = side_of_wall(map, j, side, line[i] - 48);
			side++;
		}
		(side == 4) ? (side = 0) : 0;
	}
	return (j);
}

int		check_object(char *line, int i, int object)
{
	if ((line[i] == 'C' || line[i] == 'D') &&
		((line[i + 1] > '0' && line[i + 1] <= '5') ||
		((line[i - 1] > '0' && line[i - 1] <= '5'))) && object == 0)
		return (1);
	return (0);
}

int		obj_info(t_grid *map, char *line, int h, int obj)
{
	int i;
	int side;
	int w;
	int object;

	i = -1;
	side = 0;
	w = 0;
	object = 0;
	while (line[++i])
	{
		(line[i] >= '0' && line[i] <= '5') ? (side += 1) : 0;
		if (check_object(line, i, object))
		{
			map->obj[obj].x = w;
			map->obj[obj].y = h;
			map->obj[obj].type = line[i];
			map->obj[obj++].side = side + 1;
			object = 1;
		}
		(side == 4) ? (side = 0) : 0;
		(side == 4) ? (object = 0) : 0;
		(side == 0 && line[i] >= '0' && line[i] <= '5') ? (w += 1) : 0;
	}
	return (obj);
}

void	get_map_data(t_grid *map, int fd, char *file)
{
	char	*line;
	int		h;
	int		j;
	int		obj;

	line = NULL;
	h = 0;
	j = 0;
	obj = 0;
	map_validation(map, fd, line);
	map->map = (int**)malloc(sizeof(int*) * (map->height));
	map->obj = malloc(sizeof(t_obj) * (map->objects));
	map->side = malloc(sizeof(t_side) * (map->width * map->height));
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		j = one_line_info(map, line, h, j);
		obj = obj_info(map, line, h, obj);
		h++;
		free(line);
	}
	close(fd);
	check_floor_presence(map);
}
