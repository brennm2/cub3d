#ifndef		CUB3D_H
# define	CUB3D_H

# include "../libs/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <math.h>

# define FOV 60
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 700
# define BLOCK_SIZE 500
# define PLAYER_SPEED 50
# define PLAYER_SENS 0.045

typedef struct s_player
{
	int		player_x;
	int		player_y;
	double		fov_radian;
	double	angle;
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	bool	hit_wall;
}	t_ray;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;


typedef struct s_game
{
	char		**map;
	char		*map_name;
	int			map_w;
	int			map_h;

	int			player_in_map_x;
	int			player_in_map_y;

	void		*mlx_ptr;
	void		*win_ptr;

	t_ray		*ray;
	t_player	*player;
	t_img		*img;

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
void	draw_wall(t_game *game, int ray_count);

// SRC/PLAYER/PLACE_PLAYER.C
void	place_player(t_game *game, double player_x, double player_y);


#endif