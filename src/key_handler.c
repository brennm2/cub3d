/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:14:31 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/05 12:14:14 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)
{
	int	new_move_x;
	int new_move_y;
	int	map_pos_x;
	int	map_pos_y;


	new_move_x = roundf(game->player->player_x + move_x);
	new_move_y = roundf(game->player->player_y + move_y);
	map_pos_x = new_move_x / BLOCK_SIZE;
	map_pos_y = new_move_y / BLOCK_SIZE;
	//printf("map after position: %c\n", game->map[map_pos_y][map_pos_x]);
	//printf("player position\nx:%d\ny:%d\nmap:%c\n",map_pos_x, map_pos_y, game->map[map_pos_y][map_pos_x]);
	if (game->map[map_pos_y][map_pos_x] != '1')
	{
		game->player->player_x = new_move_x;
		game->player->player_y = new_move_y;
	}
}
void	move_up(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = cos(game->player->angle) * PLAYER_SPEED;
	move_y = sin(game->player->angle) * PLAYER_SPEED;
	move_player(game, move_x, move_y);
}

void	move_down(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = -cos(game->player->angle) * PLAYER_SPEED;
	move_y = -sin(game->player->angle) * PLAYER_SPEED;
	move_player(game, move_x, move_y);
}

void	move_left(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = sin(game->player->angle) * PLAYER_SPEED;
	move_y = -cos(game->player->angle) * PLAYER_SPEED;
	move_player(game, move_x, move_y);
}

void	move_right(t_game *game)
{
	double	move_x;
	double	move_y;

	move_y = cos(game->player->angle) * PLAYER_SPEED;
	move_x = -sin(game->player->angle) * PLAYER_SPEED;
	move_player(game, move_x, move_y);
}

void	look_direction(t_game *game, bool is_left)
{
	if(!is_left)
	{
		game->player->angle += PLAYER_SENS;
		// if (game->player->angle > 2 * M_PI)
		// {
		// 	printf("entrou\n\n");
		// 	game->player->angle -= 2 * M_PI;
		// }
	}
	else
	{
		game->player->angle -= PLAYER_SENS;
		// if (game->player->angle < 0)
		// 	game->player->angle += 2 * M_PI;
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