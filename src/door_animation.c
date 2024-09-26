/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:35:35 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/26 09:54:55 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	update_door_state(t_game *game, int x, int y)
{
	if (game->map.map[x][y] == 'D')
	{
		game->map.map[x][y] = 'i';
		game->ray->is_mid_door = true;
		game->ray->door_is_closing = false;
	}
	else if (game->map.map[x][y] == 'd')
	{
		game->map.map[x][y] = 'i';
		game->ray->is_mid_door = true;
		game->ray->door_is_closing = true;
	}
}

void	door_animation(t_game *game, int new_x, int new_y, bool in_y)
{
	game->new_x = new_x;
	game->new_y = new_y;
	game->ray->is_in_y = in_y;
	if (in_y == false)
		update_door_state(game, (int)game->player.player_x, (int)new_y);
	else
		update_door_state(game, (int)new_x, (int)game->player.player_y);
}

void	door_handler(t_game *game)
{
	double	new_x;
	double	new_y;

	if (game->map.map[(int)game->player.player_x] \
		[(int)game->player.player_y] == 'd')
		return ;
	new_x = game->player.player_x + game->dirx * (PLAYER_SPEED * 5);
	new_y = game->player.player_y + game->diry * (PLAYER_SPEED * 5);
	if (game->map.map[(int)new_x][(int)game->player.player_y] == 'D' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'd' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'i')
		door_animation(game, new_x, new_y, true);
	if (game->map.map[(int)game->player.player_x][(int)new_y] == 'D' \
		|| game->map.map[(int)game->player.player_x][(int)new_y] == 'd' \
		|| game->map.map[(int)game->player.player_x][(int)new_y] == 'i')
		door_animation(game, new_x, new_y, false);
}
