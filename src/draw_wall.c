/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:15:21 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/13 16:50:40 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//cub3d.h"

void	better_mlx_pixel_put(t_img **img, int x, int y, int color)	// put the pixel
{
	char	*dst;
	dst = (*img)->addr + (y * (*img)->line_len + x * ((*img)->bpp / 8));
	*(unsigned int*)dst = color;
	//mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
}

int	get_pixel_color(t_game *game, int higher_pixel, int lower_pixel, int t_index)
{
	int	color;
	
	color = *(unsigned int *)(game->texture[t_index]->img->addr + (higher_pixel *
		game->texture[t_index]->img->line_len + lower_pixel
			* (game->texture[t_index]->img->bpp / 8)));
	return (color);
}

int get_texture_color(t_game *game, int tex_y)
{
	//get wall_x
	double wall_x;
	if (game->ray->side == false)
		wall_x = game->player.player_y + game->ray->distance * game->ray->raydir_y;
	else
		wall_x = game->player.player_x + game->ray->distance * game->ray->raydir_x;
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
	double	distance = 1.5; //distancia do raio, isso implica na forca do fog
	int times = 0;
	//printf("distance: %f\n", game->ray->distance);
	if (game->ray->distance > 4.3)
		return (0);
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


int darken_rgb_color3 (int color, double factor, int i)
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



int get_fog_ceiling(t_game *game, int color, int i, int h_pixel)
{
	//double		distance = (SCREEN_HEIGHT / 2) / 2;
	int		times = 20;
	(void)i;
	(void)h_pixel;
	(void)game;
	while (i < SCREEN_HEIGHT / 2)
	{
		i += 10;
		times--;
	}
	//times = times - distance;
	//times = ft_min(1, times);
	color = darken_rgb_color3(color, 0.9, times);
	return (color);
}

int	get_fog_floor(t_game *game, int color, int i, int l_pixel)
{
	//double		distance = SCREEN_HEIGHT / 2; //distancia do raio, isso implica na forca do fog
	int		times = 0;

	(void)game;
	(void)i;
	(void)l_pixel;
	int stop = ((SCREEN_HEIGHT / 2) + ((SCREEN_HEIGHT / 2) / 2));
	while (i < stop)
	{
		i += 10; //quantidade de step do fog
		times++; // vezes que ele rodou no while
	}
	color = darken_rgb_color3(color, 0.9, times * 1);
	return (color);
}

void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, int l_pixel)
{
	int		i;
	unsigned long	floor_rgb_set;
	unsigned long	floor_rgb;
	unsigned long	ceiling_rgb;
	unsigned long	ceiling_rgb_set;

	(void)l_pixel;
	(void)h_pixel;

	//(void)times;
	floor_rgb_set = convert_rgb(game->map.FLOOR_PATH);
	ceiling_rgb_set = convert_rgb(game->map.CEILING_PATH);
	i = 0;
	while (i < SCREEN_HEIGHT / 2) //Ceiling
	{
		ceiling_rgb = ceiling_rgb_set;
		if (i >= (SCREEN_HEIGHT / 2) / 2)
		{
			ceiling_rgb = get_fog_ceiling(game, ceiling_rgb, i, h_pixel);
			better_mlx_pixel_put(&game->img, ray_count, i++, ceiling_rgb);
		}
		else
			better_mlx_pixel_put(&game->img, ray_count, i++, ceiling_rgb_set);
	}
	i = SCREEN_HEIGHT / 2;
	int stop = (SCREEN_HEIGHT / 2) + ((SCREEN_HEIGHT / 2) / 2);
	while (i < SCREEN_HEIGHT) // floor
	{
		floor_rgb = floor_rgb_set;
		if (i < ((SCREEN_HEIGHT / 2) + stop) / 2)
			better_mlx_pixel_put(&game->img, ray_count, i++, 0);
		if (i < stop)
		{
			floor_rgb = get_fog_floor(game, floor_rgb, i, h_pixel);
			better_mlx_pixel_put(&game->img, ray_count, i++, floor_rgb);
		}
		else
		better_mlx_pixel_put(&game->img, ray_count, i++, floor_rgb_set); // ceiling
	}
}
