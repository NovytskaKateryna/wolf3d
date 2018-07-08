/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 20:53:57 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:40:47 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_scene(t_render *r, t_grid *map, unsigned int x)
{
	int	num;

	num = 0;
	r->wall_start = (HEIGHT / 2 - r->line_height / 2);
	r->wall_end = HEIGHT / 2 + r->line_height / 2;
	r->wall_color = 0;
	if (r->side == 1)
		r->wall_color = 1;
	r->sky_start = -1;
	r->sky_end = r->wall_start + 1;
	r->floor_start = r->wall_end;
	r->floor_end = HEIGHT - 1;
	if (r->e.sky_tx != 1 && (r->sky_end + r->e.w_center) != 0)
		sky_texture(r, x);
	wall_texture(r, map, x);
	if (r->e.sky_tx == 1 && (r->sky_end + r->e.w_center) != 0)
		ceiling_texture(r, x);
	floor_texture(r, x);
	if ((num = is_wall_object(r, map, r->block[X], r->block[Y])) != -1)
		draw_wall_object(r, x, num);
}
