/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:22:05 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/24 16:44:07 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_up(t_game *game)
{
	double new_x;
	double new_y;

	new_x = game->player.player_x + game->dirx * PLAYER_SPEED;
	new_y = game->player.player_y + game->diry * PLAYER_SPEED;
	if (game->map.map[(int)new_x][(int)game->player.player_y] == '0')
		game->player.player_x = new_x;
	if (game->map.map[(int)game->player.player_x][(int)new_y] == '0')
		game->player.player_y = new_y;
}

void	move_down(t_game *game)
{
	double new_x;
	double new_y;

	new_x = game->player.player_x - game->dirx * PLAYER_SPEED;
	new_y = game->player.player_y - game->diry * PLAYER_SPEED;
	if (game->map.map[(int)new_x][(int)game->player.player_y] == '0')
		game->player.player_x = new_x;
	if (game->map.map[(int)game->player.player_x][(int)new_y] == '0')
		game->player.player_y = new_y;
}

void	move_right(t_game *game)
{
	double new_x;
	double new_y;

	new_x = game->diry * PLAYER_SPEED;
	new_y = -game->dirx * PLAYER_SPEED;
	if (game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0')
		game->player.player_x += new_x;
	if (game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0')
		game->player.player_y += new_y;
}

void	move_left(t_game *game)
{

	double new_x;
	double new_y;

	new_x = -game->diry * PLAYER_SPEED;
	new_y = game->dirx * PLAYER_SPEED;

	if (game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0')
		game->player.player_x += new_x;
	if (game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0')
		game->player.player_y += new_y;
}

void	look_direction(t_game *game, const bool is_left)
{
	double	old_dir_x;
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
}

int	key_handler(const int key, t_game *game)
{
	(void)game;
	if (key == ESC)
	{
		// ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		ft_quit_game(game);
	}
	if (key == W)
		move_up(game);
	if (key == S)
		move_down(game);
 	if (key == A)
		move_left(game);
	if (key == D)
		move_right(game);
	if (key == LEFT)
		look_direction(game, true);
	if (key == RIGHT)
		look_direction(game, false);
	return (0);
}