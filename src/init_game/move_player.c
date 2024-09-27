/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:14:31 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/27 00:56:01 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/cub3d.h"

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

void	login(t_game *game)
{
	if(game->login == false)
		game->login = true;
}

int	key_handler(int key, t_game *game)
{
	if (key == ESC)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		ft_quit_game(game);
	}
	if (game->map.show_minimap == false)
	{
		if (key == 'w')
			move_up(game);
		if (key == 's')
			move_down(game);
		if (key == 'a')
			move_left(game);
		if (key == 'd')
			move_right(game);
		if (key == LEFT)
			look_direction(game, true);
		if (key == RIGHT)
			look_direction(game, false);
		if (key == 'e')
			door_handler(game);
		if (key == ENTER)
			login(game);
	}
	if (key == 'm')
		game->map.show_minimap = true;
	return (0);
}
