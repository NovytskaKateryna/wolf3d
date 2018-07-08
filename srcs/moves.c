/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:29:16 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:20:43 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	is_door_in_front(t_grid *map, double x, double y)
{
	int n;

	n = -1;
	while (++n < map->objects)
	{
		if (((map->obj[n].x == (int)(x) && map->obj[n].y == (int)(y + 1.0)) ||
			(map->obj[n].x == (int)(x + 1.0) && map->obj[n].y == (int)(y))) &&
			map->obj[n].type == 'D')
		{
			if ((map->obj[n].x < (map->width - 1) && map->obj[n].x > 0) &&
			(map->obj[n].y < (map->height - 1) && map->obj[n].y > 0))
				map->map[map->obj[n].y][map->obj[n].x] = 0;
		}
		else if (((map->obj[n].x == (int)(x) &&
			map->obj[n].y == (int)(y - 1.0)) ||
			(map->obj[n].x == (int)(x - 1.0) &&
			map->obj[n].y == (int)(y))) && map->obj[n].type == 'D')
		{
			if ((map->obj[n].x < (map->width - 1) && map->obj[n].x > 0) &&
			(map->obj[n].y < (map->height - 1) && map->obj[n].y > 0))
				map->map[map->obj[n].y][map->obj[n].x] = 0;
		}
	}
}

void	check_collision(t_render *r, t_grid *m)
{
	if (m->map[(int)(r->player_pos[Y] + 0.1)][(int)r->player_pos[X]] > 0 ||
		m->map[(int)(r->player_pos[Y] - 0.1)][(int)r->player_pos[X]] > 0)
	{
		r->player_pos[Y] -= r->direction[Y] * r->e.move_speed;
		r->player_pos[X] -= r->direction[X] * r->e.move_speed;
	}
	if (m->map[(int)r->player_pos[Y]][(int)(r->player_pos[X] + 0.1)] > 0 ||
		m->map[(int)r->player_pos[Y]][(int)(r->player_pos[X] - 0.1)] > 0)
	{
		r->player_pos[X] -= r->direction[X] * r->e.move_speed;
		r->player_pos[Y] -= r->direction[Y] * r->e.move_speed;
	}
}

void	view_rotation(t_render *r)
{
	r->e.rot_speed = 0.07;
	if (r->e.a)
	{
		r->e.sky_rot -= 10;
		r->e.view_angle -= r->e.rot_speed;
	}
	if (r->e.d)
	{
		r->e.sky_rot += 10;
		r->e.view_angle += r->e.rot_speed;
	}
}

void	move_back_forward(t_render *r, t_grid *map)
{
	if (r->e.w)
	{
		if (map->map[(int)r->player_pos[Y]][(int)(r->player_pos[X] +
			r->direction[X] * r->e.move_speed)] == 0)
			r->player_pos[X] += r->direction[X] * r->e.move_speed;
		if (map->map[(int)(r->player_pos[Y] + r->direction[Y] *
			r->e.move_speed)][(int)r->player_pos[X]] == 0)
			r->player_pos[Y] += r->direction[Y] * r->e.move_speed;
		check_collision(r, map);
		is_door_in_front(map, r->player_pos[X], r->player_pos[Y]);
	}
	if (r->e.s)
	{
		if (map->map[(int)r->player_pos[Y]][(int)(r->player_pos[X] -
			r->direction[X] * r->e.move_speed)] == 0)
			r->player_pos[X] -= r->direction[X] * r->e.move_speed;
		if (map->map[(int)(r->player_pos[Y] - r->direction[Y] *
			r->e.move_speed)][(int)r->player_pos[X]] == 0)
			r->player_pos[Y] -= r->direction[Y] * r->e.move_speed;
	}
}
