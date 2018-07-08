/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:24:02 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:32:02 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		key_release(int keycode, t_render *r)
{
	if (keycode == UP_ARROW || keycode == W)
		r->e.w = 0;
	if (keycode == DOWN_ARROW || keycode == S)
		r->e.s = 0;
	if (keycode == LEFT_ARROW || keycode == A)
		r->e.a = 0;
	if (keycode == RIGHT_ARROW || keycode == D)
		r->e.d = 0;
	return (0);
}

void	key_press(int keycode, t_render *r)
{
	if (keycode == UP_ARROW || keycode == W)
		r->e.w = 1;
	if (keycode == DOWN_ARROW || keycode == S)
		r->e.s = 1;
	if (keycode == LEFT_ARROW || keycode == A)
		r->e.a = 1;
	if (keycode == RIGHT_ARROW || keycode == D)
		r->e.d = 1;
}

int		button_release(int button, int x, int y, t_render *r)
{
	if (button == LEFT_MOUSE &&
		(x > 0 && x < WIDTH && y > 0 && y < HEIGHT))
		r->e.shooting = 0;
	if (r->e.play_mode)
		redraw(r, &r->map);
	if (!(r->e.play_mode) && !(r->e.menu_mode))
		redraw(r, &r->scene[r->e.scene_num]);
	return (0);
}

int		key_hook(int keycode, t_render *r)
{
	key_press(keycode, r);
	if (!(r->e.play_mode))
		menu_mode_events(keycode, r);
	if (keycode == ESC && r->e.play_mode)
		program_exit(r);
	if (keycode == SPACE)
	{
		r->e.pushka++;
		(r->e.pushka > 2) ? (r->e.pushka = 1) : 0;
	}
	if (r->e.play_mode && !(r->e.mouse_move))
	{
		player_move(r, &r->map);
		redraw(r, &r->map);
	}
	if (!(r->e.play_mode) && !(r->e.menu_mode) && !(r->e.mouse_move))
	{
		player_move(r, &r->scene[r->e.scene_num]);
		redraw(r, &r->scene[r->e.scene_num]);
	}
	return (0);
}

int		mouse_hook(int button, int x, int y, t_render *r)
{
	int i;
	int j;

	i = x;
	j = y;
	if (button == LEFT_MOUSE && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		r->e.shooting = 1;
	if (r->e.play_mode)
		redraw(r, &r->map);
	if (!(r->e.play_mode) && !(r->e.menu_mode))
		redraw(r, &r->scene[r->e.scene_num]);
	return (0);
}
