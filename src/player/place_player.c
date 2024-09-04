/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:37:20 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/04 12:45:10 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../header/cub3d.h"

void	place_player(t_game *game, double player_x, double player_y) //#TODO REMAKE THIS
{
	if (game->player->angle == 1) //move right
	{
		player_x = -sin(game->player->angle) * PLAYER_SPEED;
		player_y = cos(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->angle == -1) //move left
	{
		player_x = sin(game->player->angle) * PLAYER_SPEED;
		player_y = -cos(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->angle == 1) //move up
	{
		player_x = cos(game->player->angle) * PLAYER_SPEED;
		player_y = sin(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->angle == -1) //move down
	{
		player_x = -cos(game->player->angle) * PLAYER_SPEED;
		player_y = -sin(game->player->angle) * PLAYER_SPEED;
	}
}