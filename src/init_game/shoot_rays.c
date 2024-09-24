/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:03:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/18 13:36:41 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_ray_direction(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray->raydir_x = game->dirx + game->plane_x * camera_x;
	game->ray->raydir_y = game->diry + game->plane_y * camera_x;
	game->ray->map_x = (int)game->player.player_x;
	game->ray->map_y = (int)game->player.player_y;
	if (game->ray->raydir_x == 0)
		game->ray->deltadist_x = 1e30;
	else
		game->ray->deltadist_x = fabs(1 / game->ray->raydir_x);
	if (game->ray->raydir_y == 0)
		game->ray->deltadist_y = 1e30;
	else
		game->ray->deltadist_y = fabs(1 / game->ray->raydir_y);
}

void	calculate_lines(t_game *game)
{
	int	line_height;

	line_height = (int)(SCREEN_HEIGHT / game->ray->distance);
	game->ray->line_height = line_height;
	game->ray->h_pixel = -line_height / 2 + SCREEN_HEIGHT / 2;
	game->ray->l_pixel = line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->ray->h_pixel < 0)
		game->ray->h_pixel = 0;
	if (game->ray->l_pixel >= SCREEN_HEIGHT)
		game->ray->l_pixel = SCREEN_HEIGHT - 1;
}

void	dda(t_game *game)
{
	bool	wall_hit;

	wall_hit = false;
	while (wall_hit == false)
	{
		if (game->ray->raydist_x < game->ray->raydist_y)
		{
			game->ray->raydist_x += game->ray->deltadist_x;
			game->ray->map_x += game->ray->step_x;
			game->ray->side = false;
		}
		else
		{
			game->ray->raydist_y += game->ray->deltadist_y;
			game->ray->map_y += game->ray->step_y;
			game->ray->side = true;
		}
		if (game->map.map[game->ray->map_x][game->ray->map_y] == '1')
			wall_hit = true;
	}
	if (game->ray->side == false)
		game->ray->distance = (game->ray->raydist_x - game->ray->deltadist_x);
	else
		game->ray->distance = (game->ray->raydist_y - game->ray->deltadist_y);
}

void	calculate_ray_steps(t_game *game)
{
	if (game->ray->raydir_x < 0)
	{
		game->ray->step_x = -1;
		game->ray->raydist_x = (game->player.player_x - game->ray->map_x) \
		* game->ray->deltadist_x;
	}
	else
	{
		game->ray->step_x = 1;
		game->ray->raydist_x = (game->ray->map_x + 1.0 - game->player.player_x) \
		* game->ray->deltadist_x;
	}
	if (game->ray->raydir_y < 0)
	{
		game->ray->step_y = -1;
		game->ray->raydist_y = (game->player.player_y - game->ray->map_y) \
		* game->ray->deltadist_y;
	}
	else
	{
		game->ray->step_y = 1;
		game->ray->raydist_y = (game->ray->map_y + 1.0 - game->player.player_y) \
		* game->ray->deltadist_y;
	}
}

void	shoot_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x++ < SCREEN_WIDTH - 1)
	{
		calculate_ray_direction(game, x);
		calculate_ray_steps(game);
		dda(game);
		calculate_lines(game);
		draw_floor_ceiling(game, x, game->ray->h_pixel, game->ray->l_pixel);
		draw_wall(game, game->ray->h_pixel, game->ray->l_pixel, x);
	}
}
