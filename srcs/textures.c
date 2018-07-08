/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:13:18 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/09 17:13:19 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_textures(t_tex *tex, int num)
{
	int i;

	i = -1;
	while (++i < num)
		if (!(tex[i].tex_ptr))
			errors(TEXTURE_ERROR);
}

void	object_textures(t_render *r)
{
	r->obj_tex[0].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, PUSHKA,
		&r->obj_tex[0].width, &r->obj_tex[0].height);
	r->obj_tex[1].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, PUSHKA2,
		&r->obj_tex[1].width, &r->obj_tex[1].height);
	r->obj_tex[2].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, CARPET,
		&r->obj_tex[2].width, &r->obj_tex[2].height);
	r->obj_tex[3].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, DOOR,
		&r->obj_tex[3].width, &r->obj_tex[3].height);
	r->obj_tex[4].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, SHOOT,
		&r->obj_tex[4].width, &r->obj_tex[4].height);
	r->obj_tex[5].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, DOOR2,
		&r->obj_tex[5].width, &r->obj_tex[5].height);
	r->obj_tex[6].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, DOOM,
		&r->obj_tex[6].width, &r->obj_tex[6].height);
	check_textures(r->obj_tex, OBJ_TEX);
}

void	get_texture_image(t_render *r)
{
	r->wall_tex[0].image = (int*)mlx_get_data_addr(r->wall_tex[0].tex_ptr,
		&r->wall_tex[0].bpp, &r->wall_tex[0].size_line, &r->wall_tex[0].endian);
	r->wall_tex[1].image = (int*)mlx_get_data_addr(r->wall_tex[1].tex_ptr,
		&r->wall_tex[1].bpp, &r->wall_tex[1].size_line, &r->wall_tex[1].endian);
	r->wall_tex[2].image = (int*)mlx_get_data_addr(r->wall_tex[2].tex_ptr,
		&r->wall_tex[2].bpp, &r->wall_tex[2].size_line, &r->wall_tex[2].endian);
	r->wall_tex[3].image = (int*)mlx_get_data_addr(r->wall_tex[3].tex_ptr,
		&r->wall_tex[3].bpp, &r->wall_tex[3].size_line, &r->wall_tex[3].endian);
	r->wall_tex[4].image = (int*)mlx_get_data_addr(r->wall_tex[4].tex_ptr,
		&r->wall_tex[4].bpp, &r->wall_tex[4].size_line, &r->wall_tex[4].endian);
	r->obj_tex[0].image = (int*)mlx_get_data_addr(r->obj_tex[0].tex_ptr,
		&r->obj_tex[0].bpp, &r->obj_tex[0].size_line, &r->obj_tex[0].endian);
	r->obj_tex[1].image = (int*)mlx_get_data_addr(r->obj_tex[1].tex_ptr,
		&r->obj_tex[1].bpp, &r->obj_tex[1].size_line, &r->obj_tex[1].endian);
	r->obj_tex[2].image = (int*)mlx_get_data_addr(r->obj_tex[2].tex_ptr,
		&r->obj_tex[2].bpp, &r->obj_tex[2].size_line, &r->obj_tex[2].endian);
	r->obj_tex[3].image = (int*)mlx_get_data_addr(r->obj_tex[3].tex_ptr,
		&r->obj_tex[3].bpp, &r->obj_tex[3].size_line, &r->obj_tex[3].endian);
	r->obj_tex[4].image = (int*)mlx_get_data_addr(r->obj_tex[4].tex_ptr,
		&r->obj_tex[4].bpp, &r->obj_tex[4].size_line, &r->obj_tex[4].endian);
	r->obj_tex[5].image = (int*)mlx_get_data_addr(r->obj_tex[5].tex_ptr,
		&r->obj_tex[5].bpp, &r->obj_tex[5].size_line, &r->obj_tex[5].endian);
	r->obj_tex[6].image = (int*)mlx_get_data_addr(r->obj_tex[6].tex_ptr,
		&r->obj_tex[6].bpp, &r->obj_tex[6].size_line, &r->obj_tex[6].endian);
}

void	sky_floor_textures(t_render *r)
{
	r->sky_tex[0].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, COSMOS,
		&r->sky_tex[0].width, &r->sky_tex[0].height);
	r->sky_tex[1].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, PSYCHO,
		&r->sky_tex[1].width, &r->sky_tex[1].height);
	r->sky_tex[2].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, SKY,
		&r->sky_tex[2].width, &r->sky_tex[2].height);
	check_textures(r->sky_tex, SKY_FLOOR_TEX);
	r->flr_tex[0].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, GRASS,
		&r->flr_tex[0].width, &r->flr_tex[0].height);
	r->flr_tex[1].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, WOODEN,
		&r->flr_tex[1].width, &r->flr_tex[1].height);
	r->flr_tex[2].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, STONE,
		&r->flr_tex[2].width, &r->flr_tex[2].height);
	check_textures(r->flr_tex, SKY_FLOOR_TEX);
	r->sky_tex[0].image = (int*)mlx_get_data_addr(r->sky_tex[0].tex_ptr,
		&r->sky_tex[0].bpp, &r->sky_tex[0].size_line, &r->sky_tex[0].endian);
	r->sky_tex[1].image = (int*)mlx_get_data_addr(r->sky_tex[1].tex_ptr,
		&r->sky_tex[1].bpp, &r->sky_tex[1].size_line, &r->sky_tex[1].endian);
	r->sky_tex[2].image = (int*)mlx_get_data_addr(r->sky_tex[2].tex_ptr,
		&r->sky_tex[2].bpp, &r->sky_tex[2].size_line, &r->sky_tex[2].endian);
	r->flr_tex[0].image = (int*)mlx_get_data_addr(r->flr_tex[0].tex_ptr,
		&r->flr_tex[0].bpp, &r->flr_tex[0].size_line, &r->flr_tex[0].endian);
	r->flr_tex[1].image = (int*)mlx_get_data_addr(r->flr_tex[1].tex_ptr,
		&r->flr_tex[1].bpp, &r->flr_tex[1].size_line, &r->flr_tex[1].endian);
	r->flr_tex[2].image = (int*)mlx_get_data_addr(r->flr_tex[2].tex_ptr,
		&r->flr_tex[2].bpp, &r->flr_tex[2].size_line, &r->flr_tex[2].endian);
}

void	download_textures(t_render *r)
{
	r->wall_tex[0].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, ROUGH,
		&r->wall_tex[0].width, &r->wall_tex[0].height);
	r->wall_tex[1].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, PAPER,
		&r->wall_tex[1].width, &r->wall_tex[1].height);
	r->wall_tex[2].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, BRICKS,
		&r->wall_tex[2].width, &r->wall_tex[2].height);
	r->wall_tex[3].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, S_WALL1,
		&r->wall_tex[3].width, &r->wall_tex[3].height);
	r->wall_tex[4].tex_ptr = mlx_xpm_file_to_image(r->p.mlx_ptr, S_WALL2,
		&r->wall_tex[4].width, &r->wall_tex[4].height);
	check_textures(r->wall_tex, WALL_TEX);
	object_textures(r);
	sky_floor_textures(r);
	get_texture_image(r);
}
