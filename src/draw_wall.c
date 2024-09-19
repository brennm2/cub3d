/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:15:21 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/19 16:29:35 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_texture_pixel(t_game *game, int x, int h_pixel, int color)
{
	if (game->ray->side == true)
	{
		if (game->ray->raydir_y > 0)
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
		else
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
	}
	else
	{
		if (game->ray->raydir_x > 0)
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
		else
			better_mlx_pixel_put(&game->img, x, h_pixel, color);
	}
}

void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x)
{
	double	tex_pos;
	double	step;
	int		color;
	int		tex_y;

	step = 1.0 * TEXTURE_H / game->ray->line_height;
	tex_pos = (h_pixel - game->ray->mouse_height - SCREEN_HEIGHT / 2 + game->ray->line_height / 2) * step;
	while (h_pixel++ < l_pixel)
	{
		tex_y = (int)tex_pos & (TEXTURE_H - 1);
		tex_pos += step;
		color = get_texture_color(game, tex_y);
		color = get_fog(game, color);
		print_texture_pixel(game, x, h_pixel, color);
	}
}

void	draw_ceiling(t_game *game, int x, int ray_count, int h_pixel)
{
	unsigned long	ceiling_rgb;
	unsigned long	ceiling_rgb_set;
	int				stop;

	ceiling_rgb_set = convert_rgb(game->map.CEILING_PATH);
	stop = (SCREEN_HEIGHT / 2) - ((SCREEN_HEIGHT / 2) / 2);
	while (x < (SCREEN_HEIGHT / 2) + game->ray->mouse_height)
	{
		if (x == h_pixel)
			return ;
		ceiling_rgb = ceiling_rgb_set;
		if (x > ((SCREEN_HEIGHT / 2) + stop) / 2 + game->ray->mouse_height)
			better_mlx_pixel_put(&game->img, ray_count, x++, 0);
		else if (x >= ((SCREEN_HEIGHT / 2) / 2) - 100 + game->ray->mouse_height)
		{
			ceiling_rgb = get_fog_ceiling(ceiling_rgb, x, game->ray->mouse_height);
			better_mlx_pixel_put(&game->img, ray_count, x++, ceiling_rgb);
		}
		else
			better_mlx_pixel_put(&game->img, ray_count, x++, ceiling_rgb_set);
	}
}

void	draw_floor(t_game *game, int x, int ray_count, int l_pixel)
{
	unsigned long	floor_rgb_set;
	unsigned long	floor_rgb;
	int				stop;

	floor_rgb_set = convert_rgb(game->map.FLOOR_PATH);
	stop = ((SCREEN_HEIGHT / 2) + ((SCREEN_HEIGHT / 2) / 2) + game->ray->mouse_height);
	while (x < SCREEN_HEIGHT)
	{
		while (x < l_pixel)
			x++ ;
		floor_rgb = floor_rgb_set;
		if (x < (((SCREEN_HEIGHT / 2) + stop + game->ray->mouse_height) / 2))
			better_mlx_pixel_put(&game->img, ray_count, x++, 0);
		else if (x < stop + 50)
		{
			floor_rgb = get_fog_floor(floor_rgb, x, game->ray->mouse_height);
			better_mlx_pixel_put(&game->img, ray_count, x++, floor_rgb);
		}
		else
			better_mlx_pixel_put(&game->img, ray_count, x++, floor_rgb_set);
	}
}

void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, \
		int l_pixel)
{
	int		x;

	x = 0;
	draw_ceiling(game, x, ray_count, h_pixel);
	x = SCREEN_HEIGHT / 2 + game->ray->mouse_height;
	draw_floor(game, x, ray_count, l_pixel);
}
