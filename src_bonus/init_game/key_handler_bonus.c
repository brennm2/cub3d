/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:52:50 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/30 15:29:54 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	login(t_game *game)
{
	if (game->login == false)
		game->login = true;
}

int	key_release(int key, t_game *game)
{
	if (key == 'm')
		game->map.show_minimap = false;
	return (0);
}

void	key_press(t_game *game, int key)
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
