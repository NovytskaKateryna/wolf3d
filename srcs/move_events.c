/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:09:49 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:27:42 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		hook_move(t_render *r)
{
	t_grid *map;

	if (r->e.play_mode)
		map = &r->map;
	else if (r->e.menu_play && !(r->e.menu_mode))
		map = &r->scene[r->e.scene_num];
	if (r->e.play_mode || !(r->e.menu_mode))
	{
		move_back_forward(r, map);
		view_rotation(r);
		redraw(r, map);
	}
	return (0);
}

void	player_move(t_render *r, t_grid *map)
{
	move_back_forward(r, map);
	view_rotation(r);
}
