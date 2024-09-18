/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:50:11 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/14 14:40:22 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CUB3D_H
# define	CUB3D_H

# include "../libs/includes/libft.h"
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


//! Minilibx events
# ifdef __APPLE__
# include "../libs/minilibx-mac/mlx.h"
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
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
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
} t_map;

# define FOV 60
# define SCREEN_WIDTH 1500
# define SCREEN_HEIGHT 1000
# define BLOCK_SIZE 64
# define PLAYER_SPEED 0.2
# define PLAYER_SENS 0.045
# define TEXTURE_W 64
# define TEXTURE_H 64

typedef struct s_player
{
	double		player_x;
	double		player_y;
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
	int		l_pixel_ray;
	int		h_pixel_ray;
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
	//char		**map2;
	char		*map_name;
	int			map_w;
	int			map_h;
	int			h;
	int			fd_file;
	
	
	clock_t 		debug_time; //time of current frame
	clock_t 		debug_old_time ; //time of previous frame
	double		dirx;
	double		diry;
	double		plane_x;
	double		plane_y;
	int			player_in_map_x;
	int			player_in_map_y;

	void		*mlx_ptr;
	void		*win_ptr;


	t_ray		*ray;
	t_player	player;
	t_img		*img;
	t_texture	**texture;

	struct s_map	map;
}	t_game;

// ::::::::::::::::::::::::::::::: INIT_GAME :::::::::::::::::::::::::::::: //

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FILE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

/**
 * \brief Checks the number of command-line arguments.
 *
 * This function verifies that the number of command-line arguments is exactly 2.
 * If there are more than 2 arguments, it prints an error message indicating too many arguments.
 * If there are fewer than 2 arguments, it prints an error message indicating not enough arguments.
 * In both error cases, the function exits the program with a status of 1.
 *
 * \param ac The number of command-line arguments.
 */
void ft_check_args(int ac);

/**
 * \brief Checks if the given file has a .cub extension and is valid.
 *
 * This function verifies if the provided file name has a .cub extension.
 * It checks the position of the last dot in the file name and ensures that
 * the extension is .cub and that it is not preceded by a slash.
 * If the file is valid, the function returns true. Otherwise, it prints
 * an error message and exits the program with a status of 1.
 *
 * \param argv The file name to check.
 * \return true if the file has a .cub extension and is valid, false otherwise.
 */
bool is_cub_file(char *argv);


/**
 * \brief Checks if the given file exists.
 *
 * This function verifies if the provided file exists by attempting to open it.
 * If the file does not exist, it prints an error message and exits the program with a status of 1.
 *
 * \param file The file name to check.
 */
void file_exist(char *file);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STRUCTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

/**
 * \brief Initializes the game structure.
 *
 * This function initializes the game structure and allocates memory for it.
 * It also sets the file_descriptor to the given file name and initializes the
 * player structure.
 *
 * \param file The name of the file to load the map from.
 * \return A pointer to the newly created game structure.
 */
t_game *ft_init_structs(char *file);

/**
 * \brief Retrieves and sets texture paths from the configuration file.
 *
 * This function reads lines from the configuration file associated with the game
 * and sets the texture paths for the game map. It continues to read lines until
 * all textures are set or the end of the file is reached. If a duplicate texture
 * is found, it prints an error message and returns. After setting the textures,
 * it skips any empty lines.
 *
 * \param game	A pointer to the game structure containing the file descriptor
 *				and map information.
 */
void ft_get_textures(t_game *game);

bool	ft_all_textures_set(t_game const *game);
char	*remove_all_spaces(char *str);
int		ft_set_texture(t_game *game, char *line);
bool	ft_check_duplicates(t_game *game, char *line);
bool	ft_check_empty_line(const char *line, int option);
void	ft_get_map(t_game *game);
void	ft_get_player_pos(t_game *game);

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

void	ft_free_textures(t_game *game);

#endif