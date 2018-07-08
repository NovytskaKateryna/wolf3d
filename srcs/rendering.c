/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:19:28 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:22:36 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	find_the_wall(t_grid *b, t_render *r, unsigned int x)
{
	while (r->hit_wall == 0)
	{
		if (r->s_dist[X] < r->s_dist[Y])
		{
			r->s_dist[X] += r->d_dist[X];
			r->block[X] += r->step[X];
			r->side = 0;
		}
		else if (r->s_dist[Y] < r->s_dist[X])
		{
			r->s_dist[Y] += r->d_dist[Y];
			r->block[Y] += r->step[Y];
			r->side = 1;
		}
		(r->block[Y] >= b->height) ? (r->block[Y] = b->height - 1) : 0;
		(r->block[X] >= b->width) ? (r->block[X] = b->width - 1) : 0;
		(b->map[r->block[Y]][r->block[X]] > 0) ? (r->hit_wall = 1) : 0;
	}
	(r->side == 0) ? (r->distance_to_wall = ABS((r->block[X] -
		r->player_pos[X] + ((1 - r->step[X]) / 2)) / r->ray_direction[X])) :
			(r->distance_to_wall = ABS((r->block[Y] - r->player_pos[Y] +
			((1 - r->step[Y]) / 2)) / r->ray_direction[Y]));
	r->line_height = (int)(HEIGHT / r->distance_to_wall);
	draw_scene(r, b, x);
}

void	hit_the_wall(t_grid *b, t_render *r, unsigned int x)
{
	r->block[X] = (int)(r->player_pos[X]);
	r->block[Y] = (int)(r->player_pos[Y]);
	r->d_dist[X] = ABS(Y / r->ray_direction[X]);
	r->d_dist[Y] = ABS(Y / r->ray_direction[Y]);
	if (r->ray_direction[X] < 0)
	{
		r->step[X] = -1;
		r->s_dist[X] = (r->player_pos[X] - r->block[X]) * r->d_dist[X];
	}
	else if (r->ray_direction[X] > 0)
	{
		r->step[X] = 1;
		r->s_dist[X] = (r->block[X] + 1.0 - r->player_pos[X]) * r->d_dist[X];
	}
	if (r->ray_direction[Y] < 0)
	{
		r->step[Y] = -1;
		r->s_dist[Y] = (r->player_pos[Y] - r->block[Y]) * r->d_dist[Y];
	}
	else if (r->ray_direction[Y] > 0)
	{
		r->step[Y] = 1;
		r->s_dist[Y] = (r->block[Y] + 1.0 - r->player_pos[Y]) * r->d_dist[Y];
	}
	find_the_wall(b, r, x);
}

void	rotation(t_render *r)
{
	r->direction[X] = r->initial_direction[X] * cos(r->e.view_angle) +
						r->initial_direction[Y] * sin(r->e.view_angle);
	r->direction[Y] = r->initial_direction[X] * (-sin(r->e.view_angle)) +
						r->initial_direction[Y] * cos(r->e.view_angle);
	r->plane[X] = r->initial_plane[X] * cos(r->e.view_angle) +
						r->initial_plane[Y] * sin(r->e.view_angle);
	r->plane[Y] = r->initial_plane[X] * (-sin(r->e.view_angle)) +
						r->initial_plane[Y] * cos(r->e.view_angle);
}

void	put_objects(t_render *r)
{
	if (r->e.pushka == 1)
	{
		r->e.p_center[X] = 540;
		r->e.p_center[Y] = 650;
		mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr,
			r->obj_tex[0].tex_ptr, 540, 650 - r->obj_tex[6].height);
	}
	if (r->e.pushka == 2)
	{
		r->e.p_center[X] = 540;
		r->e.p_center[Y] = 708;
		mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr,
			r->obj_tex[1].tex_ptr, 540, 708 - r->obj_tex[6].height);
	}
	if (r->e.shooting == 1)
		mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr,
			r->obj_tex[4].tex_ptr, r->e.p_center[X],
			r->e.p_center[Y] - 55 - r->obj_tex[6].height);
	mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr,
		r->obj_tex[6].tex_ptr, 0, HEIGHT - r->obj_tex[6].height);
}

void	rendering(t_grid *b, t_render *r)
{
	unsigned int column;

	column = -1;
	rotation(r);
	while (++column < WIDTH)
	{
		r->camera_x = ((column * 2) / (double)WIDTH) - 1;
		r->ray_direction[X] = r->direction[X] + r->plane[X] * r->camera_x;
		r->ray_direction[Y] = r->direction[Y] + r->plane[Y] * r->camera_x;
		r->hit_wall = 0;
		hit_the_wall(b, r, column);
	}
	mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr, r->p.img_ptr, 0, 0);
	put_objects(r);
}
