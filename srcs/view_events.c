/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:25:45 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:23:13 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	horizontal_rotation(t_render *r, int x)
{
	r->e.rot_speed = 0.08;
	if (x < r->e.mouse_x)
	{
		r->e.sky_rot -= 10;
		r->e.view_angle -= r->e.rot_speed;
		r->e.mouse_x = x;
		r->e.mouse_move = 1;
		r->e.rot_speed -= 0.001;
	}
	else if (x > r->e.mouse_x)
	{
		r->e.sky_rot += 10;
		r->e.view_angle += r->e.rot_speed;
		r->e.mouse_x = x;
		r->e.mouse_move = 1;
		r->e.rot_speed += 0.001;
	}
}

void	vertical_rotation(t_render *r, int y)
{
	if (y < r->e.y && r->e.w_center < 330)
	{
		r->e.w_center += r->e.vert_view;
		r->e.y = y;
		r->e.mouse_move = 1;
		r->e.vert_view -= 1;
	}
	else if (y > r->e.y && r->e.w_center > -330)
	{
		r->e.w_center -= r->e.vert_view;
		r->e.y = y;
		r->e.mouse_move = 1;
		r->e.vert_view += 1;
	}
}

int		mouse_move(int x, int y, t_render *r)
{
	r->e.mouse_move = 0;
	if ((x > 0 && x <= WIDTH) && (y > 0 && y < HEIGHT) &&
		r->e.mouse_x == 0 && r->e.mouse_y == 0)
	{
		r->e.mouse_x = x;
		r->e.mouse_y = y;
		r->e.x = x;
		r->e.y = y;
	}
	if ((x > 10 && x < WIDTH - 10) && (y > 10 && y < HEIGHT - 10))
	{
		horizontal_rotation(r, x);
		vertical_rotation(r, y);
	}
	if (r->e.play_mode)
	{
		player_move(r, &r->map);
		redraw(r, &r->map);
	}
	else if (!(r->e.play_mode) && !(r->e.menu_mode))
	{
		player_move(r, &r->scene[r->e.scene_num]);
		redraw(r, &r->scene[r->e.scene_num]);
	}
	return (0);
}
