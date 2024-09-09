/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:15:21 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/09 16:55:14 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../header/cub3d.h"

void	better_mlx_pixel_put(t_img **img, int x, int y, int color)	// put the pixel
{
	char	*dst;
	dst = (*img)->addr + (y * (*img)->line_len + x * ((*img)->bpp / 8));
	*(unsigned int*)dst = color;
	//mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
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

int	get_pixel_color(t_game *game, int higher_pixel, int lower_pixel)
{
	int	color;
	
	color = *(unsigned int *)(game->texture->img->addr + (higher_pixel *
		game->texture->img->line_len + lower_pixel * (game->texture->img->bpp / 8)));
	return (color);
}

int	select_color(t_game *game, int tex_y, double tex_pos)
{
	double	wallx;
	int		tex_x;
	
	//game->ray->ray_angle = normalize_angle(game->ray->ray_angle);


	//if (game->ray->ray_angle > 0 && game->ray->ray_angle < M_PI)
	if(game->ray->hit_wall == true)
		wallx = game->player->player_x + game->ray->distance + game->ray->hor_x; //rayDirY;
	else
		wallx = game->player->player_y + game->ray->distance + game->ray->ver_y; // rayDirX;
	wallx -=floor(wallx);
	tex_x = (int)(wallx * TEXTURE_W);
	if (game->ray->hit_wall == false && game->ray->ver_y > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if (game->ray->hit_wall == true && game->ray->hor_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	tex_y = (int)tex_pos & (TEXTURE_H - 1);
	//printf("y: %d\n", tex_y);



	return (get_pixel_color(game, tex_y, tex_x));

	// if(game->ray->hit_wall == false) //if ray hit the wall
	// {
	// 	if (game->ray->ray_angle > M_PI / 2
	// 		&& game->ray->ray_angle < 3 * (M_PI / 2)) // Find the "midle" of the cube
	// 	{
	// 		// game->texture->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/w_wall.xpm", &game->texture->w, &game->texture->h);
	// 		// game->texture->img->addr = mlx_get_data_addr(game->texture->img->mlx_img, &game->texture->img->bpp, &game->texture->img->line_len, &game->texture->img->endian);
			
	// 		//return (0xB5B5B5FF); // west wall
	// 		return (get_pixel_color(game, tex_x, tex_y));
	// 	}
	// 	else
	// 		return (get_pixel_color(game, tex_x, tex_y)); // east wall
	// }
	// else
	// {
	// 	if (game->ray->ray_angle > 0 && game->ray->ray_angle < M_PI)
	// 		return (get_pixel_color(game, tex_x, tex_y)); // south wall
	// 	else
	// 		return (get_pixel_color(game, tex_x, tex_y)); // north wall
	// }
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

double	get_x_o(t_game *game)
{
	double	x_o;

	if (game->ray->hit_wall == 1)
		x_o = (int)fmodf((game->ray->hor_x * (TEXTURE_W / BLOCK_SIZE)), TEXTURE_W);
	else
		x_o = (int)fmodf((game->ray->ver_y * (TEXTURE_W / BLOCK_SIZE)), TEXTURE_W);
	return (x_o);
}

void	paint_wall(t_game *game, int ray_count, int higher_pixel, int lower_pixel)
{
	int		color;
	double	step;
	int		tex_y;

	//uint32_t		*arr;
	double			x_o;
	double			tex_pos; // y_0;
	//uint32_t		*arr;
	//double			factor;

	//arr = game->texture->img->line_len;
	tex_y = 0;
	
	//color = *(unsigned int *)(game->img->addr + (higher_pixel *
	//	game->img->line_len + lower_pixel * (game->img->bpp / 8)));
	
	
	step = 1.0 * TEXTURE_H / game->ray->wall_height;

	tex_pos = (higher_pixel - (SCREEN_WIDTH / 2) + (game->ray->wall_height / 2)) * step;
	x_o = get_x_o(game);

	if (tex_pos < 0)
		tex_pos = 0;
	
	//double tex_pos = (higher_pixel - SCREEN_HEIGHT / 2 + game->ray->wall_height / 2)* step; // h?
	while(higher_pixel < lower_pixel)
	{
		color = select_color(game, tex_y, tex_pos);
		// better_mlx_pixel_put(&game->img, ray_count, higher_pixel, reverse_bytes \
		// (arr[(int)tex_pos * TEXTURE_W + (int)x_o]));
		better_mlx_pixel_put(&game->img, ray_count, higher_pixel, color);
		tex_pos += step;
		higher_pixel++;
	}
}


void	draw_wall(t_game *game, int ray_count)
{
	double	wall_height;
	double	lower_pixel;
	double	higher_pixel;

	game->ray->distance *= cos(normalize_angle(game->ray->ray_angle - game->player->angle)); // fix the fisheye #TODO maybe
	wall_height = (BLOCK_SIZE / game->ray->distance) * ((SCREEN_WIDTH / 2) / tan(game->player->fov_radian / 2)); // get the wall height from the ray casted by the player
	game->ray->wall_height = wall_height;
	lower_pixel = (SCREEN_HEIGHT / 2) + (wall_height / 2); // get the bottom pixel of the wall
	higher_pixel = (SCREEN_HEIGHT / 2) - (wall_height / 2); // get the top pixel of the wall
	if (higher_pixel < 0) // safe value
		higher_pixel = 0;
	if (lower_pixel > SCREEN_HEIGHT) //safe value
		lower_pixel = SCREEN_HEIGHT;
	paint_wall(game, ray_count, higher_pixel, lower_pixel);
	render_top_botton(game, ray_count, higher_pixel, lower_pixel);
}
