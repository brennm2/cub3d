/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:50:11 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/30 13:56:59 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/includes/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <math.h>
# include <stdint.h>

//Debug
# include <time.h>

# define NORTH "NO "
# define SOUTH "SO "
# define WEST "WE "
# define EAST "EA "
# define CEILING "C "
# define FLOOR "F "

# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define C 99
# define V 118
# define RIGHT 65363
# define LEFT 65361

typedef struct s_map
{
	char	**map;
	char	*line;
	int		height;
	int		length; //TODO DONT KNOW IF ITS NECESSARY, JUST LEAVE IT FOR NOW
	long	ceiling_color;
	long	floor_color;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*ceiling_path;
	char	*floor_path;
	char	*east_path;
}	t_map;

# define FOV 60
# define SCREEN_WIDTH 1500
# define SCREEN_HEIGHT 1000
# define BLOCK_SIZE 64
# define PLAYER_SPEED 0.2
# define PLAYER_SENS 0.045
# define TEXTURE_W 64
# define TEXTURE_H 64

typedef enum s_tdir
{
	north_t,
	south_t,
	west_t,
	east_t,
}		t_tdir;

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
	char			*map_name;
	int				map_w;
	int				map_h;
	int				h;
	int				fd_file;
	double			dirx;
	double			diry;
	double			plane_x;
	double			plane_y;
	void			*mlx_ptr;
	void			*win_ptr;
	t_ray			*ray;
	t_player		player;
	t_img			*img;
	t_texture		**texture;
	struct s_map	map;
}	t_game;

// ::::::::::::::::::::::::::::::: INIT_GAME :::::::::::::::::::::::::::::: //

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FILE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

/**
 * \brief Checks the number of command-line arguments.
 *
 * This function verifies that the number of arguments is exactly 2.
 * If there are more than 2 arguments, it prints an error message indicating
 * too many arguments.
 * If there are fewer than 2 arguments, it prints an error message indicating
 * not enough arguments.
 * In both error cases, the function exits the program with a status of 1.
 *
 * \param ac The number of command-line arguments.
 */
void			ft_check_args(const int ac);

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
bool			is_cub_file(const char *argv);

/**
 * \brief Checks if the given file exists.
 *
 * This function verifies if the provided file exists by attempting to open it.
 * If the file does not exist, it prints an error message and exits the program
 * with a status of 1.
 *
 * \param file The file name to check.
 */
void			file_exist(const char *file);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STRUCTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

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
t_game			*ft_init_structs(const char *file);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEXTURES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

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
void			ft_get_textures(t_game *game);

/**
 * @brief Checks if all texture paths are set in the game map.
 *
 * This function verifies if all the texture paths:
 * (NORTH, SOUTH, WEST, EAST, CEILING, and FLOOR) are set.
 *
 * @param game	A constant pointer to the game structure containing the map with
 *				texture paths.
 * @return		true if all texture paths are set, false otherwise.
 */
bool			ft_all_textures_set(t_game const *game);

/**
 * @brief Checks if a line is empty based on the given option.
 *
 * This function iterates through each character of the provided line and checks
 * if it is empty.
 * If the option is 1, it considers a line empty if it contains
 * only spaces and newline characters.
 * If the option is not 1, it considers a line empty if it contains
 * only newline characters.
 *
 * @param line The line to be checked.
 * @param option The option to determine the criteria for an empty line.
 * @return true if the line is empty based on the given option, false otherwise.
 */
bool			ft_check_empty_line(const char *line, int option);

/**
 * @brief Checks for duplicate texture paths in the game map.
 *
 * This function checks if the given line contains any of the texture
 * identifiers (NORTH, SOUTH, EAST, WEST, CEILING, FLOOR) and if the texture
 * path is a duplicate, it returns true.
 *
 * @param game A constant pointer to the game structure containing the map with
 *				texture paths.
 * @param line The line to be checked for duplicate texture paths.
 * @return true if a duplicate texture path is found, false otherwise.
 */
bool			ft_check_duplicates(const t_game *game, const char *line);

/**
 * @brief Sets the texture path in the game map based on the given line.
 *
 * This function checks the provided line for texture identifiers
 * (NORTH, SOUTH, EAST, WEST, CEILING, FLOOR)
 * and sets the corresponding texture path in the game map.
 *
 * @param game A pointer to the game structure with the map with texture paths.
 * @param line The line to be checked for texture identifiers and paths.
 * @return 0 if a texture path is successfully set, 1 otherwise.
 */
int				ft_set_texture(t_game *game, const char *line);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

/**
 * \brief Reads and processes the game map from a file.
 *
 * This function allocates memory for the game map and reads each line from
 * the file. It checks for empty lines and valid characters, and extends the
 * map as needed. If an invalid character is found, it prints an error message
 * and exits the program.
 *
 * \param game A pointer to the game structure containing the map and file
 * descriptor.
 */
void			ft_get_map(t_game *game);

/**
 * \brief Checks if a string contains only valid characters.
 *
 * This function iterates through each character of the provided string and
 * checks if it is present in the set of valid characters. If all characters
 * in the string are valid, it returns true; otherwise, it returns false.
 *
 * \param str The string to be checked.
 * \param valid_chars A string containing the set of valid characters.
 * \return true if all characters in the string are valid, false otherwise.
 */
bool			has_valid_chars(const char *str, const char *valid_chars);

/**
 * \brief Extends the game map by allocating more memory.
 *
 * This function allocates additional memory for the game map to accommodate
 * more lines. It copies the existing map lines to the new memory location,
 * frees the old map memory, and updates the map pointer to the new memory.
 *
 * \param game A pointer to the game structure containing the map.
 */
void			ft_extend_map(t_game *game);

/**
 * \brief Duplicates the game map.
 *
 * This function allocates memory for a new map and copies the contents of the
 * existing game map into it. If memory allocation fails, it returns NULL.
 *
 * \param game A pointer to the game structure containing the map.
 * \return A pointer to the duplicated map, or NULL if memory allocation fails.
 */
char			**ft_dup_map(const t_game *game);

/**
 * \brief Performs a flood fill algorithm to validate the game map.
 *
 * This function recursively checks the game map to ensure it is properly
 * enclosed by walls. If an invalid map configuration is detected, it prints
 * an error message and exits the program.
 *
 * \param game A pointer to the game structure containing the map.
 * \param map A 2D array representing the game map.
 * \param x The x-coordinate to start the flood fill.
 * \param y The y-coordinate to start the flood fill.
 * \return 1 if the current position is a wall, otherwise 0.
 */
int				ft_flood_fill(t_game *game, char **map, int x, int y);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PLAYER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

/**
 * \brief Finds and sets the player's initial position on the game map.
 *
 * This function iterates through the game map to find the player's starting
 * position, which is indicated by the characters 'N', 'S', 'E', or 'W'. Once
 * found, it sets the player's coordinates and direction, and replaces the
 * map character with '0'.
 *
 * \param game A pointer to the game structure containing the map and player
 * information.
 */
void			ft_get_player_pos(t_game *game);

/**
 * \brief Sets the player's direction based on the given character.
 *
 * This function sets the player's direction and plane values based on the
 * provided character, which indicates the initial direction the player is
 * facing ('N', 'S', 'E', or 'W').
 *
 * \param game A pointer to the game structure containing player information.
 * \param c The character indicating the player's initial direction.
 */
void			set_player_direction(t_game *game, char c);
char			*remove_all_spaces(char *str);
int				ft_set_texture(t_game *game, const char *line);
bool			ft_check_empty_line(const char *line, int option);
void			ft_get_map(t_game *game);
void			ft_get_player_pos(t_game *game);
int				key_handler(int key, t_game *game);
void			free_all(t_game *game);
int				ft_quit_game(t_game *game);
// src/map_handler/fill_map.c
void			read_map(char *map_name, t_game *game);
void			fill_map(int fd, t_game *game);
// SRC/TEXTURE_HANDLER/CREATE_TEXTURE
void			create_all_textures(t_game *game);
int				create_texture(t_game *game, const int index, char *path,
					const char *error_msg);
// SRC/DEBUG/DEBUG_FUNCIONS.C
void			show_map(const t_game *game);
void			show_fps_debug(void);
// SRC/RAYCASTING/SHOOT_RAYS.C
void			shoot_rays(t_game *game);
float			normalize_angle(float angle);
// SRC/RAYCASTING/DRAW_WALL.C
void			draw_wall(t_game *game, int h_pixel, int l_pixel, int x);
void			draw_floor_ceiling(t_game *game, int ray_count, int h_pixel,
					int l_pixel);
// SRC/PLAYER/PLACE_PLAYER.C
void			place_player(t_game *game, double player_x, double player_y);
// SRC/FOG_CREATOR.C
int				darken_rgb_color3(int color, double factor, int i);
int				get_fog(t_game *game, int color);
int				get_fog_ceiling(int color, int i);
int				get_fog_floor(int color, int i);
// SRC/TEXTURE_HANDLER/GET_TEXTURE_COLOR.C
int				get_texture_color(t_game *game, int tex_y);
unsigned long	convert_rgb(char *color);
void			better_mlx_pixel_put(t_img **img, int x, int y, int color);
void			better_mlx_pixel_put(t_img **img, int x, int y, int color);
bool			ft_check_map(t_game *game, char **av);
void			ft_free_textures(t_game *game);
void			free_map(t_game *game);
void			ft_free_map(char **map);
void			init_window(t_game *game);
void			display_window(t_game *game);
void			init_game(t_game *game);
int				game_frame_loop(t_game *game);
void			check_string_content(const char *str);
void			ft_check_color(t_game *game);
void			free_double_pointer_array(char **array);
void			look_direction(t_game *game, bool is_left);
void			ft_skip_empty_lines(t_game *game);
int				ft_count_colours(char **colours);
size_t			ft_count_char(const char *str, char find);
bool			has_only_tabs(const char *str);
bool			has_only_spaces(const char *str);
void			ft_parse_and_set_color(t_game *game,
					const char *path, long *color, const char *type);
void			free_textures(t_game *game);
bool			ft_color_check(char **str);
void			ft_check_player(t_game *game);
void			validate_map_line(t_game *game);
bool			has_trailing_text_after_empty_line(const char *line,
					bool found_empty);
#endif