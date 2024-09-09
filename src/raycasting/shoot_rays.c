/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:03:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/09 19:01:42 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../header/cub3d.h"

// int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
// {
// 	if (is_horizon)
// 	{
// 		if (angle > 0 && angle < M_PI)
// 		{
// 			*inter += BLOCK_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	else
// 	{
// 		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
// 		{
// 			*inter += BLOCK_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	return (1);
// }

// int	unit_circle(float angle, char c)	// check the unit circle
// {
// 	if (c == 'x')
// 	{
// 		if (angle > 0 && angle < M_PI)
// 			return (1);
// 	}
// 	else if (c == 'y')
// 	{
// 		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
// 			return (1);
// 	}
// 	return (0);
// }

// int	wall_hit(float x, float y, t_game *game)	// check the wall hit
// {
// 	int		x_m;
// 	int		y_m;

// 	if (x < 0 || y < 0)
// 		return (0);
// 	x_m = floor (x / BLOCK_SIZE); // get the x position in the map
// 	y_m = floor (y / BLOCK_SIZE); // get the y position in the map
// 	if ((y_m >= game->map_h || x_m >= game->map_w))
// 		return (0);
// 	if (game->map[y_m] && x_m <= (int)ft_strlen(game->map[y_m]))
// 		if (game->map[y_m][x_m] == '1')
// 			return (0);
// 	return (1);
// }

// float	normalize_angle(float angle)
// {
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	if (angle > (2 * M_PI))
// 		angle -= (2 * M_PI);
// 	return (angle);
// }

// float	cal_h_inter(t_game *game, float angle)
// {
// 	float	h_x;
// 	float	h_y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;

// 	y_step = BLOCK_SIZE;
// 	x_step = BLOCK_SIZE / tan(angle);
// 	h_y = floor(game->player->player_y / BLOCK_SIZE) * BLOCK_SIZE;
// 	pixel = inter_check(angle, &h_y, &y_step, 1);
// 	h_x = game->player->player_x + (h_y - game->player->player_y) / tan(angle);
// 	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0)) // check x_step value
// 		x_step *= -1;
// 	while (wall_hit(h_x, h_y - pixel, game)) // check the wall hit whit the pixel value
// 	{
// 		h_x += x_step;
// 		h_y += y_step;
// 	}
// 	game->ray->hor_x = h_x;
// 	game->ray->hor_y = h_y;
// 	return (sqrt(pow(h_x - game->player->player_x, 2) + pow(h_y - game->player->player_y, 2))); // get the distance
// }

// float	cal_v_inter(t_game *game, float angle)	// get the vertical intersection
// {
// 	float	v_x;
// 	float	v_y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;

// 	x_step = BLOCK_SIZE;
// 	y_step = BLOCK_SIZE * tan(angle);
// 	v_x = floor(game->player->player_x / BLOCK_SIZE) * BLOCK_SIZE;
// 	pixel = inter_check(angle, &v_x, &x_step, 0); // check the intersection and get the pixel value
// 	v_y = game->player->player_y + (v_x - game->player->player_x) * tan(angle);
// 	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0)) // check y_step value
// 		y_step *= -1;
// 	while (wall_hit(v_x - pixel, v_y, game)) // check the wall hit whit the pixel value
// 	{
// 		v_x += x_step;
// 		v_y += y_step;
// 	}
// 	game->ray->ver_x = v_x;
// 	game->ray->ver_y = v_y;
// 	return (sqrt(pow(v_x - game->player->player_x, 2) + pow(v_y - game->player->player_y, 2))); // get the distance
// }

void	shoot_rays(t_game *game)
{
	int x = 0;
	
	while (x < SCREEN_WIDTH)
	{
		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		game->ray->raydir_x = game->dirx + game->plane_x * camera_x;
		game->ray->raydir_y = game->diry + game->plane_y * camera_x;
	
		int map_x = (int)game->pos_x;
		int	map_y = (int)game->pos_y;


		double	raydist_x;
		double	raydist_y;
		double	deltadist_x = sqrt(1 + (game->ray->raydir_y * game->ray->raydir_y) /
		(game->ray->raydir_x * game->ray->raydir_x));
		double	deltadist_y = sqrt(1 + (game->ray->raydir_x * game->ray->raydir_x) /
			(game->ray->raydir_y * game->ray->raydir_y));
		
		int	step_x;
		int	step_y;

		bool	wall_hit = false;
		bool	side = false;
		

		//calculate step and initial sideDist
		if(game->ray->raydir_x < 0)
		{
			step_x = -1;
			raydist_x = (game->pos_x - map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			raydist_x = (map_x + 1.0 - game->pos_x) * deltadist_x;
		}
		if (game->ray->raydir_y < 0)
		{
			step_y = -1;
			raydist_y = (game->pos_y - map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			raydist_y = (map_y + 1.0 - game->pos_y) * deltadist_y;
		}

		//DDA
		while(wall_hit == false)
		{
			if(raydist_x < raydist_y)
			{
				raydist_x += deltadist_x;
				map_x += step_x;
				side = false;
			}
			else
			{
				raydist_y += deltadist_y;
				map_y += step_y;
				side = true;
			}
			if(game->map[map_x][map_y] == '1')
				wall_hit = true;
		}

		//fisheye effect
		if (side == false)
			game->ray->distance = (raydist_x - deltadist_x);
		else
			game->ray->distance = (raydist_y - deltadist_y);
		
		//Calculate lineHeight
		int line_height = (int)(SCREEN_HEIGHT / game->ray->distance);
		
		//calculate h_pixel and l_pixel
		int	h_pixel = -line_height / 2 + SCREEN_HEIGHT / 2;
		int l_pixel = line_height / 2 + SCREEN_HEIGHT / 2;
		if (h_pixel < 0)
			h_pixel = 0;
		if (l_pixel >= SCREEN_HEIGHT)
			l_pixel = SCREEN_HEIGHT - 1;
		


		//tentativa de por algo na tela
		draw_wall(game, h_pixel, l_pixel);
		draw_floor_ceiling(game, x, h_pixel, l_pixel);
		x++;
	}










	
	// int		ray_count;
	// double	h_inter;
	// double	v_inter;


	// ray_count = 0;
	// game->ray->ray_angle = game->player->angle - (game->player->fov_radian / 2); //Calcula o angulo inicial
	// while(ray_count < SCREEN_WIDTH) // enquanto a quantidade de rays for menor que o tamanho da tela
	// {
	// 	game->ray->hit_wall = false; //reseta a flag de ter acertado a parede na horizontal
	// 	h_inter = cal_h_inter(game, normalize_angle(game->ray->ray_angle));
	// 	v_inter = cal_v_inter(game, normalize_angle(game->ray->ray_angle));
		
	// 	game->raydir_y = v_inter;
	// 	game->raydir_x = h_inter;
		
	// 	if (v_inter <= h_inter)
	// 		game->ray->distance = v_inter;
	// 	else
	// 	{
	// 		game->ray->distance = h_inter;
	// 		game->ray->hit_wall = true;
	// 	}
	// 	draw_wall(game, ray_count);
	// 	ray_count++; //aumenta 1 na quantidade de rays
	// 	game->ray->ray_angle += (game->player->fov_radian / SCREEN_WIDTH); // pega o proximo angulo
	// }
}
