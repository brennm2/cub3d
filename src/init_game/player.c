/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:12:00 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/23 15:12:35 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void ft_get_player_pos(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while(game->map.map[i][j])
		{
			if(game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' || game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				game->player.player_x = i + 0.5;
				game->player.player_y = j + 0.5;
				set_player_direction(game, game->map.map[i][j]);
				game->map.map[i][j] = '0';
				return;
			}
			j++;
		}
		i++;
	}
}

void	set_player_direction(t_game *game, const char c)
{
	if(c == 'N')
	{
		game->dirx = -1;
		game->plane_y = 0.66;
	}
	else if(c == 'S')
	{
		game->dirx = 1;
		game->plane_y = -0.66;
	}
	else if(c == 'E')
	{
		game->diry = 1;
		game->plane_x = 0.66;
	}
	else if(c == 'W')
	{
		game->diry = -1;
		game->plane_x = -0.66;
	}
}
