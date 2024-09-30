/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:22:05 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/30 11:07:01 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_up(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.player_x + game->dirx * PLAYER_SPEED;
	new_y = game->player.player_y + game->diry * PLAYER_SPEED;
	if (game->map.map[(int)new_x][(int)game->player.player_y] == '0' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'd')
		game->player.player_x = new_x;
	if (game->map.map[(int)game->player.player_x][(int)new_y] == '0' \
		|| game->map.map[(int)game->player.player_x][(int)new_y] == 'd')
		game->player.player_y = new_y;
}

void	move_down(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.player_x - game->dirx * PLAYER_SPEED;
	new_y = game->player.player_y - game->diry * PLAYER_SPEED;
	if (game->map.map[(int)new_x][(int)game->player.player_y] == '0' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'd')
		game->player.player_x = new_x;
	if (game->map.map[(int)game->player.player_x][(int)new_y] == '0' \
		|| game->map.map[(int)game->player.player_x][(int)new_y] == 'd')
		game->player.player_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->diry * PLAYER_SPEED;
	new_y = -game->dirx * PLAYER_SPEED;
	if (game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == 'd')
		game->player.player_x += new_x;
	if (game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == 'd')
		game->player.player_y += new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = -game->diry * PLAYER_SPEED;
	new_y = game->dirx * PLAYER_SPEED;
	if (game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == 'd')
		game->player.player_x += new_x;
	if (game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == 'd')
		game->player.player_y += new_y;
}

int	key_handler(int key, t_game *game)
{
	if (key == ESC)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		ft_quit_game(game);
	}
	if (game->map.show_minimap == false)
		key_press(game, key);
	if (key == 'm')
		game->map.show_minimap = true;
	return (0);
}
