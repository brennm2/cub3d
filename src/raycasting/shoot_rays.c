/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:03:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/05 13:25:37 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../header/cub3d.h"

int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += BLOCK_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += BLOCK_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	unit_circle(float angle, char c)	// check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	wall_hit(float x, float y, t_game *game)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / BLOCK_SIZE); // get the x position in the map
	y_m = floor (y / BLOCK_SIZE); // get the y position in the map
	if ((y_m >= game->map_h || x_m >= game->map_w))
		return (0);
	if (game->map[y_m] && x_m <= (int)ft_strlen(game->map[y_m]))
		if (game->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

float	cal_h_inter(t_game *game, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = BLOCK_SIZE;
	x_step = BLOCK_SIZE / tan(angle);
	h_y = floor(game->player->player_y / BLOCK_SIZE) * BLOCK_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = game->player->player_x + (h_y - game->player->player_y) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, game)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - game->player->player_x, 2) + pow(h_y - game->player->player_y, 2))); // get the distance
}

float	cal_y_inter(t_game *game, float angle)	// get the vertical intersection
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = BLOCK_SIZE;
	y_step = BLOCK_SIZE * tan(angle);
	v_x = floor(game->player->player_x / BLOCK_SIZE) * BLOCK_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = game->player->player_y + (v_x - game->player->player_x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, game)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - game->player->player_x, 2) + pow(v_y - game->player->player_y, 2))); // get the distance
}

void	shoot_rays(t_game *game)
{
	int		ray_count;
	double	h_inter;
	double	y_inter;

	ray_count = 0;
	game->ray->ray_angle = game->player->angle - (game->player->fov_radian / 2); //Calcula o angulo inicial
	while(ray_count < SCREEN_WIDTH) // enquanto a quantidade de rays for menor que o tamanho da tela
	{
		game->ray->hit_wall = false; //reseta a flag de ter acertado a parede
		h_inter = cal_h_inter(game, normalize_angle(game->ray->ray_angle));
		y_inter = cal_y_inter(game, normalize_angle(game->ray->ray_angle));
		if (y_inter <= h_inter)
			game->ray->distance = y_inter;
		else
		{
			game->ray->distance = h_inter;
			game->ray->hit_wall = true;
		}
		draw_wall(game, ray_count);
		ray_count++; //aumenta 1 na quantidade de rays
		game->ray->ray_angle += (game->player->fov_radian / SCREEN_WIDTH); // pega o proximo angulo
	}
}
