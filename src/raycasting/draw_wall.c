/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:15:21 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/11 18:55:57 by bde-souz         ###   ########.fr       */
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

// void	render_top_botton(t_game *game, int ray_count, int h_pixel, int l_pixel)
// {
// 	int		i;

// 	i = l_pixel;
// 	while (i < SCREEN_HEIGHT)
// 		better_mlx_pixel_put(&game->img, ray_count, i++, 0xB99470FF); // floor
// 	i = 0;
// 	while (i < h_pixel)
// 		better_mlx_pixel_put(&game->img, ray_count, i++, 0x89CFF3FF); // ceiling
// }

int	get_pixel_color(t_game *game, int higher_pixel, int lower_pixel, int t_index)
{
	int	color;
	
	color = *(unsigned int *)(game->texture[t_index]->img->addr + (higher_pixel *
		game->texture[t_index]->img->line_len + lower_pixel
			* (game->texture[t_index]->img->bpp / 8)));
	return (color);
}

// int	select_color(t_game *game, int tex_y, double tex_pos)
// {
// 	double	wallx;
// 	int		tex_x;
	
// 	//game->ray->ray_angle = normalize_angle(game->ray->ray_angle);


// 	//if (game->ray->ray_angle > 0 && game->ray->ray_angle < M_PI)
// 	if(game->ray->hit_wall == true)
// 		wallx = game->player->player_x + game->ray->distance + game->ray->hor_x; //rayDirY;
// 	else
// 		wallx = game->player->player_y + game->ray->distance + game->ray->ver_y; // rayDirX;
// 	wallx -=floor(wallx);
// 	tex_x = (int)(wallx * TEXTURE_W);
// 	if (game->ray->hit_wall == false && game->ray->ver_y > 0)
// 		tex_x = TEXTURE_W - tex_x - 1;
// 	if (game->ray->hit_wall == true && game->ray->hor_y < 0)
// 		tex_x = TEXTURE_W - tex_x - 1;
// 	tex_y = (int)tex_pos & (TEXTURE_H - 1);
// 	//printf("y: %d\n", tex_y);



// 	return (get_pixel_color(game, tex_y, tex_x));

// 	// if(game->ray->hit_wall == false) //if ray hit the wall
// 	// {
// 	// 	if (game->ray->ray_angle > M_PI / 2
// 	// 		&& game->ray->ray_angle < 3 * (M_PI / 2)) // Find the "midle" of the cube
// 	// 	{
// 	// 		// game->texture->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/w_wall.xpm", &game->texture->w, &game->texture->h);
// 	// 		// game->texture->img->addr = mlx_get_data_addr(game->texture->img->mlx_img, &game->texture->img->bpp, &game->texture->img->line_len, &game->texture->img->endian);
			
// 	// 		//return (0xB5B5B5FF); // west wall
// 	// 		return (get_pixel_color(game, tex_x, tex_y));
// 	// 	}
// 	// 	else
// 	// 		return (get_pixel_color(game, tex_x, tex_y)); // east wall
// 	// }
// 	// else
// 	// {
// 	// 	if (game->ray->ray_angle > 0 && game->ray->ray_angle < M_PI)
// 	// 		return (get_pixel_color(game, tex_x, tex_y)); // south wall
// 	// 	else
// 	// 		return (get_pixel_color(game, tex_x, tex_y)); // north wall
// 	// }
// }


// void	paint_wall(t_game *game, int ray_count, int higher_pixel, int lower_pixel)
// {
// 	int		color;
// 	double	step;
// 	int		tex_y;

// 	//uint32_t		*arr;
// 	double			x_o;
// 	double			tex_pos; // y_0;
// 	//uint32_t		*arr;
// 	//double			factor;

// 	//arr = game->texture->img->line_len;
// 	tex_y = 0;
	
// 	//color = *(unsigned int *)(game->img->addr + (higher_pixel *
// 	//	game->img->line_len + lower_pixel * (game->img->bpp / 8)));
	
	
// 	step = 1.0 * TEXTURE_H / game->ray->wall_height;

// 	tex_pos = (higher_pixel - (SCREEN_WIDTH / 2) + (game->ray->wall_height / 2)) * step;
// 	x_o = get_x_o(game);

// 	if (tex_pos < 0)
// 		tex_pos = 0;
	
// 	//double tex_pos = (higher_pixel - SCREEN_HEIGHT / 2 + game->ray->wall_height / 2)* step; // h?
// 	while(higher_pixel < lower_pixel)
// 	{
// 		color = select_color(game, tex_y, tex_pos);
// 		// better_mlx_pixel_put(&game->img, ray_count, higher_pixel, reverse_bytes \
// 		// (arr[(int)tex_pos * TEXTURE_W + (int)x_o]));
// 		better_mlx_pixel_put(&game->img, ray_count, higher_pixel, color);
// 		tex_pos += step;
// 		higher_pixel++;
// 	}
// }

int get_texture_color(t_game *game, int tex_y)
{
	//get wall_x
	double wall_x;
	if (game->ray->side == false)
		wall_x = game->pos_y + game->ray->distance * game->ray->raydir_y;
	else
		wall_x = game->pos_x + game->ray->distance * game->ray->raydir_x;
	wall_x -= floor(wall_x);

	//get texture coordinate
	int tex_x = wall_x * (double)TEXTURE_W;
	if (game->ray->side == false && game->ray->raydir_x > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if (game->ray->side == true && game->ray->raydir_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	
	if (game->ray->side == true)
	{
		if (game->ray->raydir_y > 0) //West (esquerda)
			return (get_pixel_color(game, tex_y, tex_x, 3));
		else //East (direita)
			return (get_pixel_color(game, tex_y, tex_x, 2));
	}
	else
	{
		if (game->ray->raydir_x > 0) //Norte
			return (get_pixel_color(game, tex_y, tex_x, 0));
		else //Sul
			return (get_pixel_color(game, tex_y, tex_x, 1));
	}
		return (0);
}

unsigned char	ft_min(unsigned char a, unsigned char b)
{
	if (a > b)
		return (b);
	return (a);
}

unsigned char	ft_max(unsigned char a, unsigned char b)
{
	if (a > b)
		return (a);
	return (b);
}

int	darken_color(int color, unsigned char amount)
{
	int	i;
	int	out;
	unsigned char	shade[4];

	i = -1;
	out = 0;
	while (++i < 4)
	{
		shade[i] = (color >> (i * 8)) & 0x0000FF;
		if (shade[i] / amount - 1 > 0)
			shade[i] -= shade[i] / amount - 1;
		else
			shade[i] -= ft_min(1, shade[i]);
	}
	out = shade[0] | shade[1] << 8 | shade[2] << 16 | shade[3] << 24;
	return (out);
}

int darken_rgb_color(int color, double factor)
{
    int r, g, b;

    if (factor < 0 || factor > 1)
        return color; // Factor should be between 0 and 1

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    r = (int)(r * factor);
    g = (int)(g * factor);
    b = (int)(b * factor);

    return (r << 16) | (g << 8) | b;
}

int darken_rgb_color2 (int color, double factor, int i)
{
	int r, g, b;

	if (factor < 0 || factor > 1)
		return color; // Factor should be between 0 and 1
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	for (int j = 0; j < i; j++)
	{
		r = (int)(r * factor);
		g = (int)(g * factor);
		b = (int)(b * factor);
	}
	return (r << 16) | (g << 8) | b;
}

int	get_fog(t_game *game, int color)
{
	double	distance = 3; //distancia do raio, isso implica na forca do fog
	int		times = 0;

	while (distance < game->ray->distance)
	{
		//color = darken_rgb_color(color, 0.9);
		distance += 0.1; //quantidade de step do fog
		times++; // vezes que ele rodou no while
	}
	
	color = darken_rgb_color2(color, 0.9, times);
	return (color);
}

void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x)
{
	int	color;
	double	step = 1.0 * TEXTURE_H / game->ray->line_height;
	double	texpos = (h_pixel - SCREEN_HEIGHT / 2 + game->ray->line_height / 2) * step;
	
	while(h_pixel < l_pixel)
	{
		int	tex_y = (int)texpos & (TEXTURE_H - 1);
		texpos += step;
		color = get_texture_color(game, tex_y);
		color = get_fog(game, color);
		// if(game->ray->side == 0)
		// 	color = (color >> 1) & 8355711;
		if (game->ray->side == true)
		{
			if (game->ray->raydir_y > 0) // Norte
				better_mlx_pixel_put(&game->img, x, h_pixel, color);
			else // Sul
				better_mlx_pixel_put(&game->img, x, h_pixel, color);
		}
		else
		{
			if (game->ray->raydir_x > 0)
				better_mlx_pixel_put(&game->img, x, h_pixel, color);
			else
				better_mlx_pixel_put(&game->img, x, h_pixel, color);
		}
 		h_pixel++;
	}
}

unsigned long	convert_rgb(char *color)
{
	int	r;
	int	g;
	int	b;
	char **temp_color;
	int i;

	i = 0;
	temp_color = ft_split(color, ',');
	if (temp_color)
	{
		if(temp_color[0] && temp_color[1] && temp_color[2])
		{
			r = ft_atoi(temp_color[0]);
			g = ft_atoi(temp_color[1]);
			b = ft_atoi(temp_color[2]);
		}
		else
			ft_printf("Error with convert_rgb!\n");
		while(temp_color[i])
			free(temp_color[i++]);
		free(temp_color);
		return (r<<16) | (g<<8) | b;
	}
	return (0);
}




int	get_fog_floor(t_game *game, int color)
{
	if (game->ray->distance > 3)
			color = (color >> 1) & 8355711;
	if (game->ray->distance > 3.2)
			color = (color >> 1) & 8355711;
	if (game->ray->distance > 3.4)
			color = (color >> 1) & 8355711;
	if (game->ray->distance > 3.6)
			color = (color >> 1) & 8355711;
	if (game->ray->distance > 3.8)
			color = (color >> 1) & 8355711;

	return (color);
}

void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, int l_pixel)
{
	int		i;
	unsigned long	floor_rgb_set;
	unsigned long	floor_rgb;
	unsigned long	ceiling_rgb;
	unsigned long	ceiling_rgb_set;

	//int times = 0;

	floor_rgb_set = convert_rgb(game->map.FLOOR_PATH);
	ceiling_rgb_set = convert_rgb(game->map.CEILING_PATH);
	i = l_pixel;
	while (i < SCREEN_HEIGHT)
	{
		floor_rgb = floor_rgb_set;
		if (i < game->ray->l_pixel_ray)
		{
			//floor_rgb = get_fog_floor(game, floor_rgb);
			floor_rgb = get_fog(game, floor_rgb);
			better_mlx_pixel_put(&game->img, ray_count, i++, floor_rgb); // floor
		}
		else
			better_mlx_pixel_put(&game->img, ray_count, i++, floor_rgb_set);
	}
	i = 0;
	while (i < h_pixel)
	{
		ceiling_rgb = ceiling_rgb_set;
		if (i > game->ray->h_pixel_ray)
		{
			//ceiling_rgb = get_fog_floor(game, ceiling_rgb);
			ceiling_rgb = get_fog(game, ceiling_rgb);
			better_mlx_pixel_put(&game->img, ray_count, i++, ceiling_rgb);
		}
		else
			better_mlx_pixel_put(&game->img, ray_count, i++, ceiling_rgb_set); // ceiling
	}
}
