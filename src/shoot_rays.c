/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:03:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/13 12:34:46 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		double	deltadist_x;
		double	deltadist_y;

		if (game->ray->raydir_x == 0)
			deltadist_x = 1e30;
		else
			deltadist_x = fabs(1 / game->ray->raydir_x);
		if (game->ray->raydir_y == 0)
			deltadist_y = 1e30;
		else
			deltadist_y = fabs(1 / game->ray->raydir_y);

		
		int	step_x;
		int	step_y;

		bool	wall_hit = false;


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
				game->ray->side = false;
			}
			else
			{
				raydist_y += deltadist_y;
				map_y += step_y;
				game->ray->side = true;
			}
			if(game->map.map[map_x][map_y] == '1')
				wall_hit = true;
		}

		//fisheye effect
		if (game->ray->side == false)
			game->ray->distance = (raydist_x - deltadist_x);
		else
			game->ray->distance = (raydist_y - deltadist_y);
		
		//Calculate lineHeight
		int line_height = (int)(SCREEN_HEIGHT / game->ray->distance);
		game->ray->line_height = line_height;
		
		//calculate h_pixel and l_pixel
		int	h_pixel = -line_height / 2 + SCREEN_HEIGHT / 2;
		int l_pixel = line_height / 2 + SCREEN_HEIGHT / 2;
		if (h_pixel < 0)
			h_pixel = 0;
		if (l_pixel >= SCREEN_HEIGHT)
			l_pixel = SCREEN_HEIGHT - 1;
		static int flag = 0;
		if (game->ray->distance > 1.5 && flag == 0)
		{
			flag = 1;
			printf("%f\n",game->ray->distance);
			game->ray->l_pixel_ray = l_pixel;
			game->ray->h_pixel_ray = h_pixel;
		}

		draw_wall(game, h_pixel, l_pixel, x);
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
