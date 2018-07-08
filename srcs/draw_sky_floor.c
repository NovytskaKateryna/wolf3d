/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:41:07 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:37:02 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	determine_floor_position(t_render *r)
{
	if (r->side == 0 && r->ray_direction[X] > 0)
	{
		r->floor[X] = r->block[X];
		r->floor[Y] = r->block[Y] + r->wall;
		r->wall_side = 1;
	}
	else if (r->side == 0 && r->ray_direction[X] < 0)
	{
		r->floor[X] = r->block[X] + 1.0;
		r->floor[Y] = r->block[Y] + r->wall;
		r->wall_side = 4;
	}
	else if (r->side == 1 && r->ray_direction[Y] > 0)
	{
		r->floor[X] = r->block[X] + r->wall;
		r->floor[Y] = r->block[Y];
		r->wall_side = 3;
	}
	else
	{
		r->floor[X] = r->block[X] + r->wall;
		r->floor[Y] = r->block[Y] + 1.0;
		r->wall_side = 2;
	}
}

void	floor_texture(t_render *r, unsigned int x)
{
	double	distance;
	double	factor;
	int		color;
	int		y;

	determine_floor_position(r);
	y = r->wall_end - 1;
	while ((y + r->e.w_center) < HEIGHT)
	{
		distance = HEIGHT / (2.0 * y - HEIGHT);
		factor = distance / r->distance_to_wall;
		r->floor_c[X] = factor * r->floor[X] +
			(1.0 - factor) * r->player_pos[X];
		r->floor_c[Y] = factor * r->floor[Y] +
			(1.0 - factor) * r->player_pos[Y];
		r->tex[X] = (int)(r->floor_c[X] * r->flr_tex[r->e.floor_tx].width) %
			r->flr_tex[r->e.floor_tx].width;
		r->tex[Y] = (int)(r->floor_c[Y] * r->flr_tex[r->e.floor_tx].height) %
			r->flr_tex[r->e.floor_tx].height;
		color = (r->flr_tex[r->e.floor_tx].image[r->tex[Y] *
			r->flr_tex[r->e.floor_tx].width + r->tex[X]]);
		put_img_pixel(r, x, y + r->e.w_center, color);
		y++;
	}
}

void	ceiling_texture(t_render *r, unsigned int x)
{
	double	distance;
	double	factor;
	int		color;
	int		y;

	determine_floor_position(r);
	y = r->wall_end + 1;
	while (y < HEIGHT + r->e.w_center)
	{
		distance = HEIGHT / (2.0 * y - HEIGHT);
		factor = distance / r->distance_to_wall;
		r->floor_c[X] = factor * r->floor[X] +
			(1.0 - factor) * r->player_pos[X];
		r->floor_c[Y] = factor * r->floor[Y] +
			(1.0 - factor) * r->player_pos[Y];
		r->tex[X] = (int)(r->floor_c[X] * r->sky_tex[r->e.sky_tx].width) %
			r->sky_tex[r->e.sky_tx].width;
		r->tex[Y] = (int)(r->floor_c[Y] * r->sky_tex[r->e.sky_tx].height) %
			r->sky_tex[r->e.sky_tx].height;
		color = (r->sky_tex[r->e.sky_tx].image[r->tex[Y] *
				r->sky_tex[r->e.sky_tx].width + r->tex[X]]);
		put_img_pixel(r, x, HEIGHT - y + r->e.w_center, color);
		y++;
	}
}

void	sky_texture(t_render *r, unsigned int x)
{
	int	color;
	int	y;

	y = 0;
	while (y < r->sky_end + r->e.w_center)
	{
		if (r->e.sky_rot > r->sky_tex[r->e.sky_tx].width ||
			r->e.sky_rot < -r->sky_tex[r->e.sky_tx].width)
			r->e.sky_rot = 0;
		r->tex[X] = x + r->e.sky_rot;
		if (r->tex[X] < 0)
			r->tex[X] += r->sky_tex[r->e.sky_tx].width;
		r->tex[Y] = y + 360 - r->e.w_center;
		color = (r->sky_tex[r->e.sky_tx].image[r->tex[Y] *
			r->sky_tex[r->e.sky_tx].width + r->tex[X]]);
		put_img_pixel(r, x, y, color);
		y++;
	}
}
