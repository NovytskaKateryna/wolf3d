/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:32:54 by knovytsk          #+#    #+#             */
/*   Updated: 2018/02/26 17:32:55 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	redraw(t_render *r, t_grid *map)
{
	clear_image(r);
	rendering(map, r);
}

void	clear_image(t_render *r)
{
	ft_bzero(r->p.image, WIDTH * HEIGHT * r->p.bpp);
}

void	put_img_pixel(t_render *r, unsigned int x, unsigned int y, int color)
{
	if (x < WIDTH && y < HEIGHT)
		*(int*)(r->p.image + (x + y * WIDTH) * r->p.bpp) = color;
}
