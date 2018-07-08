/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:12:13 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:25:51 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	initial_parameters(t_render *r)
{
	r->initial_direction[X] = -1;
	r->initial_direction[Y] = 0;
	r->initial_plane[X] = 0;
	r->initial_plane[Y] = 0.66;
	r->player_pos[X] = 1.5;
	r->player_pos[Y] = 1.5;
	r->e.w_center = 0;
	r->e.view_angle = 3.5;
	r->e.move_speed = 0.25;
	r->e.rot_speed = 0.07;
	r->e.sky_rot = 0;
	r->e.mouse_x = 0;
	r->e.mouse_y = 0;
	r->e.shooting = 0;
	r->e.vert_view = 30;
	r->e.sky_tx = 2;
	r->e.floor_tx = 1;
	r->e.scene_num = -1;
	r->e.a = 0;
	r->e.w = 0;
	r->e.s = 0;
	r->e.d = 0;
}

void	initial_menu_parameters(t_render *r, int play_mode)
{
	if (!(play_mode))
		r->e.menu_mode = 1;
	r->e.menu_play = 0;
	r->e.pushka = 1;
	r->e.s1 = "textures/menu/scene1s.xpm";
	r->e.s2 = "textures/menu/scene2s.xpm";
	r->e.s3 = "textures/menu/scene3s.xpm";
}

void	make_menu(t_render *r)
{
	void	*name;
	int		width;
	int		height;
	int		x;

	if (!(name = mlx_xpm_file_to_image(r->p.mlx_ptr, MENU, &width, &height)))
		errors(TEXTURE_ERROR);
	x = WIDTH / 2 - width / 2;
	mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr, name, x, 0);
	if (!(name = mlx_xpm_file_to_image(r->p.mlx_ptr, LOGO, &width, &height)))
		errors(TEXTURE_ERROR);
	mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr, name, 200, 50);
	if (!(name = mlx_xpm_file_to_image(r->p.mlx_ptr, r->e.s1, &width, &height)))
		errors(TEXTURE_ERROR);
	x = WIDTH / 2 - width / 2;
	mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr, name, x, 350);
	if (!(name = mlx_xpm_file_to_image(r->p.mlx_ptr, r->e.s2, &width, &height)))
		errors(TEXTURE_ERROR);
	x = WIDTH / 2 - width / 2;
	mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr, name, x, 500);
	if (!(name = mlx_xpm_file_to_image(r->p.mlx_ptr, r->e.s3, &width, &height)))
		errors(TEXTURE_ERROR);
	x = WIDTH / 2 - width / 2;
	mlx_put_image_to_window(r->p.mlx_ptr, r->p.win_ptr, name, x, 650);
}

void	init_player(t_render *r, int play_mode)
{
	initial_parameters(r);
	initial_menu_parameters(r, play_mode);
	r->p.mlx_ptr = mlx_init();
	r->p.win_ptr = mlx_new_window(r->p.mlx_ptr, WIDTH, HEIGHT,
			"WOLF3D motherf*ker");
	r->p.img_ptr = mlx_new_image(r->p.mlx_ptr, WIDTH, HEIGHT);
	r->p.image = mlx_get_data_addr(r->p.img_ptr, &r->p.bpp,
			&r->p.size_line, &r->p.endian);
	r->p.bpp /= 8;
	r->e.play_mode = play_mode;
	download_textures(r);
	(r->e.play_mode) ? rendering(&r->map, r) : make_menu(r);
	mlx_loop_hook(r->p.mlx_ptr, hook_move, r);
	mlx_hook(r->p.win_ptr, 2, 0, key_hook, r);
	mlx_hook(r->p.win_ptr, 3, 0, key_release, r);
	mlx_hook(r->p.win_ptr, 4, 0, mouse_hook, r);
	mlx_hook(r->p.win_ptr, 5, 0, button_release, r);
	mlx_hook(r->p.win_ptr, 6, 0, mouse_move, r);
	mlx_hook(r->p.win_ptr, 17, 1L << 17, program_exit, r);
	mlx_loop(r->p.mlx_ptr);
}
