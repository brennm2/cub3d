/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:50:11 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/05 14:29:18 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CUB3D_H
# define	CUB3D_H

# include "../libs/includes/libft.h"
# include "../libs/minilibx-mac/mlx.h"
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define NORTH "NO"
# define SOUTH "SO"
# define WEST "WE"
# define EAST "EA"
# define CEILING "C"
# define FLOOR "F"

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
# endif

typedef struct s_map
{
	char **map;
	int height;
	int length; //TODO DONT KNOW IF ITS NECESSARY, JUST LEAVE IT FOR NOW
	char *NORTH_PATH;
	char *SOUTH_PATH;
	char *WEST_PATH;
	char *CEILING_PATH;
	char *FLOOR_PATH;
	char *EAST_PATH;
} t_map;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			*map_name;
	struct s_map	map;
}	t_game;



int		key_handler(int key, t_game *game);
void	free_all(t_game *game);
int		ft_quit_game(t_game *game);

bool ft_check_map(t_game *game, char **av);

#endif