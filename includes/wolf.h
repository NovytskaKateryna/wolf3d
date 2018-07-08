/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:44:02 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 16:05:11 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF_H
# define FT_WOLF_H

# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "mlx.h"
# include "keys.h"

# define ABS(Value) (((Value) < 0) ? -(Value) : (Value))

# define INCORRECT_MAP 11
# define INCORRECT_MAP_SIZE 2
# define INCORRECT_NUM_OF_ARGS 3
# define NON_VALID_FILE 4
# define FAIL_TO_READ 5
# define INCORRECT_PLAYER_POSITION 6
# define MLX_INIT_ERROR 7
# define MLX_WINDOW_ERROR 8
# define MLX_IMAGE_ERROR 9
# define TEXTURE_ERROR 13

# define WIDTH 1280
# define HEIGHT 1024
# define WALL_TEX 5
# define SKY_FLOOR_TEX 3
# define OBJ_TEX 7

# define X 0
# define Y 1

union				u_color
{
	unsigned int	color_value;
	unsigned char	chanel[3];
};

typedef struct		s_ptr
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*image;
	int				bpp;
	int				size_line;
	int				endian;
}					t_ptr;

typedef	struct		s_obj
{
	int				x;
	int				y;
	int				side;
	char			type;
}					t_obj;

typedef struct		s_side
{
	int				obj;
	int				east;
	int				west;
	int				north;
	int				south;
}					t_side;

typedef struct		s_grid
{
	t_obj			*obj;
	t_side			*side;
	int				**map;
	int				width;
	int				height;
	int				objects;
}					t_grid;

typedef	struct		s_tex
{
	void			*tex_ptr;
	int				width;
	int				height;
	int				*image;
	int				bpp;
	int				size_line;
	int				endian;
}					t_tex;

typedef struct		s_event
{
	double			sky_rot;
	double			view_angle;
	double			move_speed;
	double			rot_speed;
	int				vert_view;
	int				w_center;
	int				mouse_x;
	int				mouse_y;
	int				x;
	int				y;
	int				shooting;
	char			*s1;
	char			*s2;
	char			*s3;
	int				angle;
	int				sky_tx;
	int				floor_tx;
	int				scene_num;
	int				play_mode;
	int				menu_mode;
	int				menu_play;
	int				pushka;
	int				p_center[2];
	int				mouse_move;
	int				a;
	int				w;
	int				s;
	int				d;
}					t_event;

typedef struct		s_render
{
	t_ptr			p;
	t_event			e;
	t_grid			map;
	t_grid			scene[3];
	t_tex			wall_tex[10];
	t_tex			flr_tex[3];
	t_tex			sky_tex[3];
	t_tex			obj_tex[10];
	double			direction[2];
	double			player_pos[2];
	double			plane[2];
	double			ray_direction[2];
	double			s_dist[2];
	double			d_dist[2];
	double			initial_direction[2];
	double			initial_plane[2];
	double			camera_x;
	double			distance_to_wall;
	int				step[2];
	int				block[2];
	int				tex[2];
	int				hit_wall;
	int				side;
	int				line_height;
	int				wall_start;
	int				wall_end;
	int				wall_color;
	int				sky_start;
	int				sky_end;
	int				floor_start;
	int				floor_end;
	int				wall_side;
	double			wall;
	double			floor[2];
	double			floor_c[2];
}					t_render;

void				get_map_data(t_grid *map, int fd, char *file);
void				errors(int error_msg);
void				map_validation(t_grid *map, int fd, char *line);
void				check_floor_presence(t_grid *map);
void				initial_parameters(t_render *r);
void				init_player(t_render *r, int play_mode);
void				make_menu(t_render *r);
void				download_textures(t_render *r);
int					key_hook(int keycode, t_render *r);
int					mouse_move(int x, int y, t_render *r);
int					mouse_hook(int button, int x, int y, t_render *r);
int					program_exit(t_render *rc);
int					key_release(int keycode, t_render *r);
int					button_release(int button, int x, int y, t_render *r);
void				menu_mode_events(int keycode, t_render *r);
void				player_move(t_render *r, t_grid *map);
int					hook_move(t_render *r);
void				put_img_pixel(t_render *r, unsigned int x,
								unsigned int y, int color);
void				clear_image(t_render *r);
void				redraw(t_render *r, t_grid *map);
void				rendering(t_grid *b, t_render *r);
void				draw_scene(t_render *r, t_grid *map, unsigned int x);
void				sky_texture(t_render *r, unsigned int x);
void				ceiling_texture(t_render *r, unsigned int x);
void				floor_texture(t_render *r, unsigned int x);
void				wall_texture(t_render *r, t_grid *map, unsigned int x);
int					is_wall_object(t_render *r, t_grid *map, int x, int y);
void				draw_wall_object(t_render *r, unsigned int x, int num);
void				move_back_forward(t_render *r, t_grid *map);
void				view_rotation(t_render *r);
#endif
