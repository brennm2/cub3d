/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:14:31 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/11 12:48:34 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_move_x;
	double new_move_y;
	// int	map_pos_x;
	// int	map_pos_y;


	new_move_x = roundf(game->pos_x + move_x);
	new_move_y = roundf(game->pos_y + move_y);
	// map_pos_x = new_move_x / BLOCK_SIZE;
	// map_pos_y = new_move_y / BLOCK_SIZE;
	//printf("map after position: %c\n", game->map[map_pos_y][map_pos_x]);
	//printf("player position\nx:%d\ny:%d\nmap:%c\n",map_pos_x, map_pos_y, game->map[map_pos_y][map_pos_x]);
	if (game->map.map[(int)new_move_y][(int)new_move_x] != '1')
	{
		game->pos_x = new_move_x;
		game->pos_y = new_move_y;
	}
}
void	move_up(t_game *game)
{
	(void)game;
	// double	move_x;
	// double	move_y;

	//game->pos_x += 1;

	if(game->map.map[(int)(game->pos_x + game->dirx * PLAYER_SPEED)][(int)(game->pos_y)] == '0')
		game->pos_x += game->dirx * PLAYER_SPEED;
	if(game->map.map[(int)(game->pos_x)][(int)(game->pos_y + game->diry * PLAYER_SPEED)] == '0')
		game->pos_y += game->diry * PLAYER_SPEED;

	// move_x = cos(game->player->angle) * PLAYER_SPEED;
	//move_y = sin(game->player->angle) * PLAYER_SPEED;
	// move_x = game->pos_x + game->dirx * PLAYER_SPEED;
	// move_y = game->pos_y + game->diry * PLAYER_SPEED;
	// move_player(game, move_x, move_y);
}

void	move_down(t_game *game)
{
	// double	move_x;
	// double	move_y;

	if(game->map.map[(int)(game->pos_x - game->dirx * PLAYER_SPEED)][(int)(game->pos_y)] == '0')
		game->pos_x -= game->dirx * PLAYER_SPEED;
	if(game->map.map[(int)(game->pos_x)][(int)(game->pos_y - game->diry * PLAYER_SPEED)] == '0')
		game->pos_y -= game->diry * PLAYER_SPEED;

	// move_x = -cos(game->player->angle) * PLAYER_SPEED;
	// move_y = -sin(game->player->angle) * PLAYER_SPEED;
	// move_player(game, move_x, move_y);
}

void	move_right(t_game *game)
{
	double move_x;
    double move_y;

    move_x = game->diry * PLAYER_SPEED;
    move_y = -game->dirx * PLAYER_SPEED;

    if (game->map.map[(int)(game->pos_x + move_x)][(int)(game->pos_y)] == '0')
        game->pos_x += move_x;
    if (game->map.map[(int)(game->pos_x)][(int)(game->pos_y + move_y)] == '0')
        game->pos_y += move_y;
	// double move_x;
 	// double move_y ;

	// move_x = sin(game->diry) * PLAYER_SPEED; //cos(game->dirx) * PLAYER_SPEED;
	// move_y = -cos(game->dirx) * PLAYER_SPEED; //sin(game->diry) * PLAYER_SPEED;

	// if (game->map.map[(int)(game->pos_x - move_x)][(int)(game->pos_y)] == '0')
	// 	game->pos_x -= move_x;
	// if (game->map.map[(int)(game->pos_x)][(int)(game->pos_y + move_y)] == '0')
	// 	game->pos_y += move_y;

	// move_x = sin(game->player->angle) * PLAYER_SPEED;
	// move_y = -cos(game->player->angle) * PLAYER_SPEED;
	// move_player(game, move_x, move_y);
}

void	move_left(t_game *game)
{

	 double move_x;
    double move_y;

    move_x = -game->diry * PLAYER_SPEED;
    move_y = game->dirx * PLAYER_SPEED;

    if (game->map.map[(int)(game->pos_x + move_x)][(int)(game->pos_y)] == '0')
        game->pos_x += move_x;
    if (game->map.map[(int)(game->pos_x)][(int)(game->pos_y + move_y)] == '0')
        game->pos_y += move_y;
}

void	look_direction(t_game *game, bool is_left)
{
	double old_dir_x;
	double	old_plane_x;
	
	old_dir_x = game->dirx;
	old_plane_x = game->plane_x;
	if(!is_left)
	{
		game->dirx = game->dirx * cos(-PLAYER_SENS) - game->diry * sin(-PLAYER_SENS);
		game->diry = old_dir_x * sin(-PLAYER_SENS) + game->diry * cos(-PLAYER_SENS);
		game->plane_x = game->plane_x * cos(-PLAYER_SENS) - game->plane_y * sin(-PLAYER_SENS);
		game->plane_y = old_plane_x * sin(-PLAYER_SENS) + game->plane_y * cos(-PLAYER_SENS);
	}
	else
	{
		game->dirx = game->dirx * cos(PLAYER_SENS) - game->diry * sin(PLAYER_SENS);
		game->diry = old_dir_x * sin(PLAYER_SENS) + game->diry * cos(PLAYER_SENS);
		game->plane_x = game->plane_x * cos(PLAYER_SENS) - game->plane_y * sin(PLAYER_SENS);
		game->plane_y = old_plane_x * sin(PLAYER_SENS) + game->plane_y * cos(PLAYER_SENS);
	}
	
	//printf("angle: %f\n", game->player->angle);
	//printf("math: %f\n", 2 * M_PI);
}

int	key_handler(int key, t_game *game)
{
	(void)game;
	if (key == XK_Escape)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		ft_quit_game(game);
	}
	if (key == 'w')
		move_up(game); //printf("moveup\n");//test_move_up(game);
	if (key == 's')
		move_down(game); //printf("movedown\n");//test_move_down(game);
 	if (key == 'a')
		move_left(game); //printf("moveleft\n");//test_move_left(game);
	if (key == 'd')
		move_right(game); //printf("moveright\n");//test_move_right(game);
	if (key == XK_Left)
		look_direction(game, true); //printf("looked left\n");
	if (key == XK_Right)
		look_direction(game, false); //printf("looked right\n");c
	return (0);
}

int	ft_quit_game(t_game *game)
{
	//get_next_line(-1);
	free_all(game);
	exit (0);
}