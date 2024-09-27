/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_sup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:47:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/27 14:16:07 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	change_door_in_y(t_game *game)
{
	if (game->map.map[(int)game->player.player_x][(int)game->new_y] == 'i'
		&& game->ray->door_is_closing == false)
		game->map.map[(int)game->player.player_x][(int)game->new_y] = 'd';
	else if (game->map.map[(int)game->player.player_x][(int)game->new_y] == 'i'
		&& game->ray->door_is_closing == true)
	{
		game->ray->door_is_closing = false;
		game->ray->is_mid_door = false;
		game->map.map[(int)game->player.player_x][(int)game->new_y] = 'D';
	}
}

void	change_door_in_map(t_game *game)
{
	if (game->ray->is_in_y == false)
		change_door_in_y(game);
	else
	{
		if (game->map.map[(int)game->new_x][(int)game->player.player_y] == 'i'
			&& game->ray->door_is_closing == false)
			game->map.map[(int)game->new_x][(int)game->player.player_y] = 'd';
		else if (game->map.map[(int)game->new_x] \
			[(int)game->player.player_y] == 'i'
			&& game->ray->door_is_closing == true)
		{
			game->ray->door_is_closing = false;
			game->ray->is_mid_door = false;
			game->map.map[(int)game->new_x][(int)game->player.player_y] = 'D';
		}
	}
}

int	select_wall_texture(t_game *game, int tex_x, int tex_y)
{
	if (game->ray->side == true && game->ray->is_door == false)
	{
		if (game->ray->raydir_y > 0)
			return (get_pixel_color(game, tex_y, tex_x, west_t));
		else
			return (get_pixel_color(game, tex_y, tex_x, east_t));
	}
	else
	{
		if (game->ray->raydir_x > 0)
			return (get_pixel_color(game, tex_y, tex_x, north_t));
		else
			return (get_pixel_color(game, tex_y, tex_x, south_t));
	}
}
