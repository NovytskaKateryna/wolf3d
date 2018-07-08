/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:49:38 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:27:09 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_floor_presence(t_grid *map)
{
	int floor;
	int y;
	int x;

	floor = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y][x] == 0)
				floor++;
			if (map->map[0][x] == 0 || map->map[y][0] == 0 ||
				map->map[map->height - 1][x] == 0 ||
				map->map[y][map->width - 1] == 0)
				errors(INCORRECT_MAP);
		}
	}
	if (floor < 4)
		errors(INCORRECT_MAP);
	if (map->map[1][1] != 0)
		errors(INCORRECT_PLAYER_POSITION);
}

int		check_line(char *line, int i, int side, int obj)
{
	if (line[i] > '5' && line[i] <= '9')
		errors(INCORRECT_MAP);
	if ((line[i] > '0' && line[i] <= '5') &&
		!(line[i + 1] > '0' && line[i] <= '5') && side < 4)
	{
		if (line[i + 1] != 'D')
			errors(INCORRECT_MAP);
	}
	else if ((line[i] == 'C' || line[i] == 'D') &&
		((line[i + 1] > '0' && line[i + 1] <= '5') ||
		((line[i - 1] > '0' && line[i - 1] <= '5'))) && obj == 0)
		return (1);
	return (0);
}

int		count_line(t_grid *map, char *line, int i, int side)
{
	int		line_size;
	int		obj;

	obj = 0;
	line_size = 0;
	while (line[++i])
	{
		if (line[i] >= '0' && line[i] <= '5')
		{
			(side == 0) ? (line_size += 1) : 0;
			side++;
		}
		if (check_line(line, i, side, obj))
		{
			obj = 1;
			map->objects++;
		}
		if (side == 4)
		{
			side = 0;
			obj = 0;
		}
	}
	return (line_size);
}

void	map_validation(t_grid *map, int fd, char *line)
{
	int line_size;

	map->height = 0;
	map->width = 0;
	map->objects = 0;
	while (get_next_line(fd, &line))
	{
		line_size = count_line(map, line, -1, 0);
		if (map->width != 0 && line_size != map->width)
			errors(INCORRECT_MAP);
		map->width = line_size;
		map->height++;
		free(line);
	}
	close(fd);
	if (map->width < 4 && map->height < 4)
		errors(INCORRECT_MAP_SIZE);
}
