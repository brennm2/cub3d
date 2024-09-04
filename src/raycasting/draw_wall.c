/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:15:21 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/04 15:55:53 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../header/cub3d.h"

int	select_color(t_game *game, bool hit_wall)
{
	game->ray->ray_angle = normalize_angle(game->ray->ray_angle);
	if(hit_wall == false) //if ray hit the wall
	{
		if (game->ray->ray_angle > M_PI / 2
			&& game->ray->ray_angle < 3 * (M_PI / 2)) // Find the "midle" of the cube
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (game->ray->ray_angle > 0 && game->ray->ray_angle < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

// void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = game->img->addr + (y * game->img->line_len + x * (game->img->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

void	better_mlx_pixel_put(t_img **img, int x, int y, int color)	// put the pixel
{
	char	*dst;
	//int offset = (y * game->img->line_len + x * (game->img->bpp / 8));

	// if (x < 0) // check the x position
	// 	return ;
	// else if (x >= SCREEN_WIDTH)
	// 	return ;
	// if (y < 0) // check the y position
	// 	return ;
	// else if (y >= SCREEN_HEIGHT)
	// 	return ;
	//game->img->addr = mlx_get_data_addr(game->img, &game->img->bpp, &game->img->line_len, &game->img->endian);
	//game->img->addr = mlx_get_data_addr(game->img, &game->img->bpp, &game->img->line_len, &game->img->endian);
	dst = (*img)->addr + (y * (*img)->line_len + x * ((*img)->bpp / 8));
	*(unsigned int*)dst = color;
	//mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
}

void	paint_wall(t_game *game, int ray_count, int higher_pixel, int lower_pixel)
{
	int	color;

	color = select_color(game, game->ray->hit_wall);
	while(higher_pixel < lower_pixel)
	{
		better_mlx_pixel_put(&game->img, ray_count, higher_pixel, color);
		//mlx_pixel_put(game->mlx_ptr, game->win_ptr, ray_count, higher_pixel, color);
		higher_pixel++;
	}
}

void	render_top_botton(t_game *game, int ray_count, int h_pixel, int l_pixel)
{
	int		i;

	i = l_pixel;
	while (i < SCREEN_HEIGHT)
		better_mlx_pixel_put(&game->img, ray_count, i++, 0xB99470FF); // floor
	i = 0;
	while (i < h_pixel)
		better_mlx_pixel_put(&game->img, ray_count, i++, 0x89CFF3FF); // ceiling
}

void	draw_wall(t_game *game, int ray_count)
{
	double	wall_height;
	double	lower_pixel;
	double	higher_pixel;

	//wall_height = 0;
	//printf("entrou aqui\n");
	//game->ray->distance *= cos(normalize_angle(game->ray->ray_angle - game->player->angle)); // fix the fisheye

	//if (tan(game->player->fov_radian / 2) != 0)
	wall_height = (BLOCK_SIZE / game->ray->distance) * ((SCREEN_WIDTH / 2) / tan(game->player->fov_radian / 2)); // get the wall height from the ray casted by the player
	higher_pixel = (SCREEN_HEIGHT / 2) - (wall_height / 2); // get the top pixel of the wall
	lower_pixel = (SCREEN_HEIGHT / 2) + (wall_height / 2); // get the bottom pixel of the wall
	if (lower_pixel > SCREEN_HEIGHT) //Safe value
		lower_pixel = SCREEN_HEIGHT;
	if (higher_pixel < 0) // safe value
		higher_pixel = 0;
	paint_wall(game, ray_count, higher_pixel, lower_pixel);
	render_top_botton(game, ray_count, higher_pixel, lower_pixel);
}
