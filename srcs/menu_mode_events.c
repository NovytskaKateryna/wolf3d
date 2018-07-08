/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_mode_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:08:48 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:26:46 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		menu_navigation(t_render *r, int keycode, int arrow)
{
	r->e.s1 = "textures/menu/scene1s.xpm";
	r->e.s2 = "textures/menu/scene2s.xpm";
	r->e.s3 = "textures/menu/scene3s.xpm";
	if (keycode == DOWN_ARROW)
		arrow++;
	else if (keycode == UP_ARROW)
		arrow--;
	(arrow > 3) ? (arrow = 1) : 0;
	(arrow <= 0) ? (arrow = 3) : 0;
	if (arrow == 1)
		r->e.s1 = "textures/menu/scene1b.xpm";
	if (arrow == 2)
		r->e.s2 = "textures/menu/scene2b.xpm";
	if (arrow == 3)
		r->e.s3 = "textures/menu/scene3b.xpm";
	return (arrow);
}

int		enter_scene(t_render *r, int arrow, int esc)
{
	(r->e.menu_mode) ? (esc -= 1) : 0;
	initial_parameters(r);
	r->e.sky_tx = arrow - 1;
	r->e.floor_tx = arrow - 1;
	r->e.scene_num = arrow - 1;
	if (arrow == 1)
		r->e.view_angle = 2.94;
	if (arrow == 2)
		r->e.view_angle = 7.76;
	if (arrow == 3)
	{
		r->e.view_angle = -1.88;
		r->player_pos[X] = 1.812;
		r->player_pos[Y] = 4.177;
	}
	rendering(&r->scene[r->e.scene_num], r);
	r->e.menu_mode = 0;
	r->e.menu_play = 1;
	return (esc);
}

void	menu_mode_events(int keycode, t_render *r)
{
	static int	arrow = 0;
	static int	esc = 0;

	if (keycode == ESC)
	{
		if (esc == 0 && r->e.menu_mode)
			program_exit(r);
		r->e.menu_mode = 1;
		r->e.menu_play = 0;
		esc++;
	}
	if (keycode == DOWN_ARROW || keycode == UP_ARROW)
		arrow = menu_navigation(r, keycode, arrow);
	if (keycode == ENTER && arrow >= 1 && arrow <= 3)
		esc = enter_scene(r, arrow, esc);
	if (r->e.menu_mode)
		make_menu(r);
}
