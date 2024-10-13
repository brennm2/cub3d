/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:15:21 by bde-souz          #+#    #+#             */
/*   Updated: 2024/10/13 18:25:41 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"




void	print_texture_pixel(t_game *game, int x, int h_pixel, int color, t_ray *ray)
{
	if (ray->side == true)
	{
		if (ray->raydir_y > 0)
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
		else
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
	}
	else
	{
		if (ray->raydir_x > 0)
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
		else
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
	}
}


void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x, t_ray *ray)
{
	double	tex_pos;
	double	step;
	int		color;
	int		tex_y;

	step = 1.0 * TEXTURE_H / ray->line_height;
	tex_pos = (h_pixel - ray->mouse_height - SCREEN_HEIGHT / 2 \
		+ ray->line_height / 2) * step;
	while (h_pixel++ < l_pixel)
	{
		tex_y = (int)tex_pos & (TEXTURE_H - 1);
		tex_pos += step;
		color = get_texture_color(game, tex_y, ray);
		color = get_fog(game, color, ray);
		print_texture_pixel(game, x, h_pixel, color, ray);
	}
}

void	draw_ceiling(t_game *game, int x, int ray_count, int h_pixel, t_ray *ray)
{
	unsigned long	ceiling_rgb;
	unsigned long	ceiling_rgb_set;
	int				stop;

	ceiling_rgb_set = game->map.ceiling_color;
	stop = (SCREEN_HEIGHT / 2) - ((SCREEN_HEIGHT / 2) / 2);
	while (x < (SCREEN_HEIGHT / 2) + ray->mouse_height)
	{
		if (x == h_pixel)
			return ;
		ceiling_rgb = ceiling_rgb_set;
		if (x > ((SCREEN_HEIGHT / 2) + stop) / 2 + ray->mouse_height)
			better_mlx_pixel_put(&game->img, ray_count, x++, 0);
		else if (x >= ((SCREEN_HEIGHT / 2) / 2) - 100 + ray->mouse_height)
		{
			ceiling_rgb = get_fog_ceiling(ceiling_rgb, x, \
				ray->mouse_height);
			better_mlx_pixel_put(&game->img, ray_count, x++, ceiling_rgb);
		}
		else
			better_mlx_pixel_put(&game->img, ray_count, x++, ceiling_rgb_set);
	}
}

void	draw_floor(t_game *game, int x, int ray_count, int l_pixel, t_ray *ray)
{
	unsigned long	floor_rgb_set;
	unsigned long	floor_rgb;
	int				stop;

	floor_rgb_set = game->map.floor_color;
	stop = ((SCREEN_HEIGHT / 2) + ((SCREEN_HEIGHT / 2) / 2) \
		+ ray->mouse_height);
	while (x < SCREEN_HEIGHT)
	{
		while (x < l_pixel)
			x++ ;
		floor_rgb = floor_rgb_set;
		if (x < (((SCREEN_HEIGHT / 2) + stop + ray->mouse_height) / 2))
			better_mlx_pixel_put(&game->img, ray_count, x++, 0);
		else if (x < stop + 50)
		{
			floor_rgb = get_fog_floor(floor_rgb, x, ray->mouse_height);
			better_mlx_pixel_put(&game->img, ray_count, x++, floor_rgb);
		}
		else
			better_mlx_pixel_put(&game->img, ray_count, x++, floor_rgb_set);
	}
}

void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, \
		int l_pixel, t_ray *ray)
{
	int		x;

	x = 0;
	draw_ceiling(game, x, ray_count, h_pixel, ray);
	x = SCREEN_HEIGHT / 2 + ray->mouse_height;
	draw_floor(game, x, ray_count, l_pixel, ray);
}
