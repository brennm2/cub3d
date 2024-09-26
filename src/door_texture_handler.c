/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:00:47 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/26 10:16:40 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_wall_hit(t_game *game)
{
	char	tile;

	tile = game->map.map[game->ray->map_x][game->ray->map_y];
	if (tile == '1')
	{
		game->ray->is_door = false;
		return (true);
	}
	if (tile == 'D')
		return (door_texture_handler(game, 0));
	if (tile == 'i')
		return (door_texture_handler(game, 1));
	if (tile == 'd')
	{
		game->ray->is_mid_door = false;
		game->ray->is_door = false;
		return (false);
	}
	return (false);
}

void	set_door_state(t_game *game, int option)
{
	if (option == 0)
	{
		game->ray->is_door = true;
		game->ray->is_mid_door = false;
	}
	else if (option == 1)
	{
		game->ray->is_mid_door = true;
		game->ray->is_door = true;
	}
	else if (option == 2)
	{
		game->ray->is_mid_door = false;
		game->ray->is_door = false;
	}
}

void	door_texture_final(t_game *game)
{
	if (game->map.map[game->ray->map_x][game->ray->map_y] == 'D')
		game->tex_index = door;
	else if (game->map.map[game->ray->map_x][game->ray->map_y] == 'i')
		game->tex_index = door_mid;
	else if (game->map.map[game->ray->map_x][game->ray->map_y] == 'd')
		game->tex_index = door_side;
}

bool	door_texture_handler(t_game *game, int option)
{
	door_texture_final(game);
	if (game->ray->side == false)
	{
		game->ray->raydist_x -= game->ray->deltadist_x / 2;
		if (game->ray->raydist_x > game->ray->raydist_y)
		{
			game->ray->raydist_y += game->ray->deltadist_y;
			game->ray->side = true;
			game->tex_index = door_side;
		}
		game->ray->raydist_x += game->ray->deltadist_x;
	}
	else
	{
		game->ray->raydist_y -= game->ray->deltadist_y / 2;
		if (game->ray->raydist_y > game->ray->raydist_x)
		{
			game->ray->raydist_x += game->ray->deltadist_x;
			game->ray->side = false;
			game->tex_index = door_side;
		}
		game->ray->raydist_y += game->ray->deltadist_y;
	}
	set_door_state(game, option);
	return (true);
}
