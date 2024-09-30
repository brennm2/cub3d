/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:17:40 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/30 15:29:58 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dirx;
	old_plane_x = game->plane_x;
	game->dirx = game->dirx * cos(angle) - game->diry * sin(angle);
	game->diry = old_dir_x * sin(angle) + game->diry * cos(angle);
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

static void	adjust_mouse_height(t_game *game, int delta_y)
{
	game->ray->mouse_height += delta_y;
	if (game->ray->mouse_height > 300)
		game->ray->mouse_height = 300;
	else if (game->ray->mouse_height < -300)
		game->ray->mouse_height = -300;
}

void	mouse_direction(t_game *game)
{
	int	center_x;
	int	center_y ;

	center_x = SCREEN_WIDTH / 2;
	center_y = SCREEN_HEIGHT / 2;
	if (*game->mouse_x - center_x < -10)
		rotate_player(game, MOUSE_SENS);
	else if (*game->mouse_x - center_x > 10)
		rotate_player(game, -MOUSE_SENS);
	if (*game->mouse_y - center_y < -10)
		adjust_mouse_height(game, MOUSE_PITCH);
	else if (*game->mouse_y - center_y > 10)
		adjust_mouse_height(game, -MOUSE_PITCH);
}

// void	mouse_direction(t_game *game)
// {
// 	int center_x = (SCREEN_WIDTH / 2);
// 	int	center_y = (SCREEN_HEIGHT / 2);
// 	double	old_dir_x;
// 	double	old_plane_x;

// 	old_dir_x = game->dirx;
// 	old_plane_x = game->plane_x;
// 	(void)center_y;
// 	if (*game->mouse_x - center_x < -10)
// 	{
// 		game->dirx = game->dirx * cos(MOUSE_SENS) - game->diry *
// sin(MOUSE_SENS);
// 		game->diry = old_dir_x * sin(MOUSE_SENS) + game->diry * 
//cos(MOUSE_SENS);
// 		game->plane_x = game->plane_x * cos(MOUSE_SENS) - game->plane_y * 
//sin(MOUSE_SENS);
// 		game->plane_y = old_plane_x * sin(MOUSE_SENS) + game->plane_y * 
//cos(MOUSE_SENS);
// 	}
// 	else if (*game->mouse_x - center_x > 10)
// 	{
// 		game->dirx = game->dirx * cos(-MOUSE_SENS) - game->diry * 
//sin(-MOUSE_SENS);
// 		game->diry = old_dir_x * sin(-MOUSE_SENS) + game->diry * 
//cos(-MOUSE_SENS);
// 		game->plane_x = game->plane_x * cos(-MOUSE_SENS) - 
//game->plane_y * sin(-MOUSE_SENS);
// 		game->plane_y = old_plane_x * sin(-MOUSE_SENS) + 
//game->plane_y * cos(-MOUSE_SENS);
// 	}
// 	if (*game->mouse_y - center_y < -10)
// 	{
// 		game->ray->mouse_height += MOUSE_PITCH;
// 		if (game->ray->mouse_height >= 300)
// 			game->ray->mouse_height = 300;
// 	}
// 	else if (*game->mouse_y - center_y > 10)
// 	{
// 		game->ray->mouse_height -= MOUSE_PITCH;
// 		if (game->ray->mouse_height <= -300)
// 			game->ray->mouse_height = -300;
// 	}
// }
