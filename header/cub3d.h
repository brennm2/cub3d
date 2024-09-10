/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:50:11 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/10 15:38:52 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CUB3D_H
# define	CUB3D_H

# include "../libs/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define NORTH "NO"
# define SOUTH "SO"
# define WEST "WE"
# define EAST "EA"
# define CEILING "C"
# define FLOOR "F"

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
} t_map;
# include <math.h>
#include <stdint.h>

# define FOV 60
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 700
# define BLOCK_SIZE 64
# define PLAYER_SPEED 0.2
# define PLAYER_SENS 0.045
# define TEXTURE_W 64
# define TEXTURE_H 64

typedef struct s_player
{
	int		player_x;
	int		player_y;
	//double		fov_radian;
	//double	angle;
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int		line_height;
	bool	hit_wall;
	bool	side;

	double	raydir_x;
	double	raydir_y;
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
	//char		**map;
	char		*map_name;
	int			map_w;
	int			map_h;
	int			h;
	int			fd_file;

	double		pos_x;
	double		pos_y;
	double		dirx;
	double		diry;
	double		plane_x;
	double		plane_y;
	int			player_in_map_x;
	int			player_in_map_y;

	void		*mlx_ptr;
	void		*win_ptr;


	t_ray		*ray;
	t_player	*player;
	t_img		*img;
	t_texture	**texture;

	struct s_map	map;
}	t_game;



int		key_handler(int key, t_game *game);
void	free_all(t_game *game);
int		ft_quit_game(t_game *game);


// src/map_handler/fill_map.c
void	read_map(char *map_name, t_game *game);
void	fill_map(int fd, t_game *game);


// SRC/DEBUG/DEBUG_FUNCIONS.C
void	show_map(t_game *game);

// SRC/RAYCASTING/SHOOT_RAYS.C
void	shoot_rays(t_game *game);
float	normalize_angle(float angle);

// SRC/RAYCASTING/DRAW_WALL.C
void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x);
void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, int l_pixel);

// SRC/PLAYER/PLACE_PLAYER.C
void	place_player(t_game *game, double player_x, double player_y);


void	better_mlx_pixel_put(t_img **img, int x, int y, int color);


bool ft_check_map(t_game *game, char **av);

t_game *ft_init_struct(t_game *game, char *file);

#endif