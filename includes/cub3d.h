/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:50:11 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/19 18:13:40 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CUB3D_H
# define	CUB3D_H

# include "../libs/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"
// # include "../minilibx-mac/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <math.h>
# include <stdint.h>

//Debug
#include <time.h>

# define NORTH "NO"
# define SOUTH "SO"
# define WEST "WE"
# define EAST "EA"
# define CEILING "C"
# define FLOOR "F"


//

//! Minilibx events
# ifdef __APPLE__
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define C 8
#  define V 9
#  define RIGHT 124
#  define LEFT 123
#  define KeyPress 2
#  define KeyPressMask (1L<<0)
#  define DestroyNotify 17
#  define StructureNotifyMask (1L<<17)
# else
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define C 99
#  define V 118
#  define RIGHT 65363
#  define LEFT 65361
# endif

typedef struct s_map
{
	char **map;
	char *line;
	int height;
	int length; //TODO DONT KNOW IF ITS NECESSARY, JUST LEAVE IT FOR NOW
	char *NORTH_PATH;
	char *SOUTH_PATH;
	char *WEST_PATH;
	char *CEILING_PATH;
	char *FLOOR_PATH;
	char *EAST_PATH;

	bool	show_minimap;
} t_map;

# define FOV 60
# define SCREEN_WIDTH 1500
# define SCREEN_HEIGHT 1000
# define BLOCK_SIZE 64
# define PLAYER_SPEED 0.2
# define PLAYER_SENS 0.045
# define MOUSE_SENS 0.040
# define MOUSE_PITCH 25
# define TEXTURE_W 64
# define TEXTURE_H 64

typedef enum s_tdir
{
	north_t,
	south_t,
	west_t,
	east_t,
	door,
	door_mid,
}		t_tdir;

typedef struct s_fps
{
	clock_t	old_time;
	clock_t	time;
	clock_t	frametime;
	double	fps;
	double	temp_fps;
}	t_fps;


typedef struct s_player
{
	double		player_x;
	double		player_y;
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int		line_height;
	bool	wall_hit;
	bool	side;
	bool	is_door;
	bool	is_mid_door;
	bool	door_is_closing;
	bool	is_in_y;
	
	int		mouse_height;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	raydir_x;
	double	raydir_y;
	double	raydist_x;
	double	raydist_y;
	double	deltadist_x;
	double	deltadist_y;

	
	int		l_pixel;
	int		h_pixel;
}	t_ray;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;


typedef struct s_texture
{
	t_img	*img;
	int		h;
	int		w;
}	t_texture;



typedef struct s_game
{
	char		*map_name;
	int			map_w;
	int			map_h;
	int			h;
	int			fd_file;
	
	int			*mouse_x;
	int			*mouse_y;
	int			new_x;
	int			new_y;
	double		dirx;
	double		diry;
	double		plane_x;
	double		plane_y;
	int			player_in_map_x;
	int			player_in_map_y;

	void		*mlx_ptr;
	void		*win_ptr;


	t_img		*handmap;
	t_ray		*ray;
	t_player	player;
	t_img		*img;
	t_texture	**texture;
	t_fps		*fps;

	struct s_map	map;
}	t_game;



int		key_handler(int key, t_game *game);
void	free_all(t_game *game);
int		ft_quit_game(t_game *game);


// src/map_handler/fill_map.c
void	read_map(char *map_name, t_game *game);
void	fill_map(int fd, t_game *game);


// SRC/TEXTURE_HANDLER/CREATE_TEXTURE
void	create_texture(t_game *game);

// SRC/DEBUG/DEBUG_FUNCIONS.C
void	show_map(t_game *game);
void	show_fps_debug(t_game *game);

// SRC/RAYCASTING/SHOOT_RAYS.C
void	shoot_rays(t_game *game);
float	normalize_angle(float angle);

// SRC/RAYCASTING/DRAW_WALL.C
void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x);
void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, int l_pixel);

// SRC/PLAYER/PLACE_PLAYER.C
void	place_player(t_game *game, double player_x, double player_y);


// SRC/FOG_CREATOR.C
int	darken_rgb_color3 (int color, double factor, int i);
int	get_fog(t_game *game, int color);
int			get_fog_ceiling(int color, int i, int mouse);
int			get_fog_floor(int color, int i, int mouse);

// SRC/TEXTURE_HANDLER/GET_TEXTURE_COLOR.C
int				get_texture_color(t_game *game, int tex_y);
unsigned long	convert_rgb(char *color);
void			better_mlx_pixel_put(t_img **img, int x, int y, int color);

void	better_mlx_pixel_put(t_img **img, int x, int y, int color);


bool ft_check_map(t_game *game, char **av);


void	minimap(t_game *game, int *x_p, int *y_p);
t_game *ft_init_structs(char *file);

#endif