/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:40:54 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:39:35 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		is_wall_object(t_render *r, t_grid *map, int x, int y)
{
	int n;

	n = -1;
	while (++n < map->objects)
	{
		if (map->obj[n].x == x && map->obj[n].y == y)
		{
			if (map->obj[n].type == 'C' && r->wall_side == map->obj[n].side)
				return (2);
			else if (map->obj[n].type == 'D' &&
				map->map[map->obj[n].y][map->obj[n].x] > 0)
			{
				if (r->e.scene_num == 1)
					return (3);
				return (5);
			}
		}
	}
	return (-1);
}

void	determine_wall_pos(t_render *r, int tex_num)
{
	if (r->side == 0)
		r->wall = r->player_pos[Y] + r->distance_to_wall * r->ray_direction[Y];
	else
		r->wall = r->player_pos[X] + r->distance_to_wall * r->ray_direction[X];
	r->wall -= (int)(r->wall);
	r->tex[X] = (int)(r->wall * r->wall_tex[tex_num].width);
}

void	draw_wall_object(t_render *r, unsigned int x, int num)
{
	union u_color	w_color;
	int				factor;
	int				y;
	int				y1;

	y = r->wall_start - 1;
	y1 = r->wall_end;
	r->tex[X] = (int)(r->wall * r->obj_tex[num].width);
	while (++y < y1)
	{
		factor = (2 * y) - HEIGHT + (r->line_height);
		r->tex[Y] = ((factor * r->obj_tex[num].height) /
			(r->line_height)) / 2;
		w_color.color_value = (r->obj_tex[num].image[r->tex[Y] *
			r->obj_tex[num].height + r->tex[X]]);
		if (r->wall_color == 1)
		{
			w_color.chanel[0] *= 0.55;
			w_color.chanel[1] *= 0.55;
			w_color.chanel[2] *= 0.55;
		}
		put_img_pixel(r, x, y + r->e.w_center, w_color.color_value);
	}
}

int		determine_wall_texture(t_render *r, t_grid *map, int x, int y)
{
	int num;

	if (r->side == 0 && r->ray_direction[X] > 0)
		num = map->side[y * map->width + x].east - 1;
	if (r->side == 0 && r->ray_direction[X] < 0)
		num = map->side[y * map->width + x].west - 1;
	if (r->side == 1 && r->ray_direction[Y] > 0)
		num = map->side[y * map->width + x].north - 1;
	if (r->side == 1 && r->ray_direction[Y] < 0)
		num = map->side[y * map->width + x].south - 1;
	return (num);
}

void	wall_texture(t_render *r, t_grid *map, unsigned int x)
{
	union u_color	w_color;
	int				tex_num;
	int				factor;
	int				y;

	tex_num = determine_wall_texture(r, map, r->block[X], r->block[Y]);
	determine_wall_pos(r, tex_num);
	y = r->wall_start;
	while (y < r->wall_end)
	{
		factor = (2 * y) - HEIGHT + r->line_height;
		r->tex[Y] = ((factor * r->wall_tex[tex_num].height) /
			r->line_height) / 2;
		w_color.color_value = (r->wall_tex[tex_num].image[r->tex[Y] *
			r->wall_tex[tex_num].height + r->tex[X]]);
		if (r->wall_color == 1)
		{
			w_color.chanel[0] *= 0.55;
			w_color.chanel[1] *= 0.55;
			w_color.chanel[2] *= 0.55;
		}
		put_img_pixel(r, x, y + r->e.w_center, w_color.color_value);
		y++;
	}
}
