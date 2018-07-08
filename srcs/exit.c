/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 13:59:13 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:40:18 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		program_exit(t_render *r)
{
	int n;
	int	i;

	n = -1;
	if (r->map.map != NULL)
	{
		while (++n < r->map.height)
			free(r->map.map[n]);
		free(r->map.obj);
		free(r->map.side);
	}
	if (!(r->e.play_mode))
	{
		i = -1;
		while (++i < 3)
		{
			while (++n < r->scene[i].height)
				free(r->scene[i].map[n]);
			free(r->scene[i].obj);
			free(r->scene[i].side);
		}
	}
	mlx_destroy_window(r->p.mlx_ptr, r->p.win_ptr);
	mlx_destroy_image(r->p.mlx_ptr, r->p.img_ptr);
	exit(0);
}
