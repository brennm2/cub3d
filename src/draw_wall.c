/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:15:21 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/15 18:43:35 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	better_mlx_pixel_put(t_img **img, int x, int y, int color)
{
	char	*dst;
	dst = (*img)->addr + (y * (*img)->line_len + x * ((*img)->bpp / 8));
	*(unsigned int*)dst = color;
}

static inline int	get_pixel_color(t_game *game, int higher_pixel, int lower_pixel, int t_index)
{
	int	color;
	
	color = *(unsigned int *)(game->texture[t_index]->img->addr + (higher_pixel *
		game->texture[t_index]->img->line_len + lower_pixel
			* (game->texture[t_index]->img->bpp / 8)));
	return (color);
}

int get_texture_color(t_game *game, int tex_y)
{
	double wall_x;

	if (game->ray->side == false)
		wall_x = game->player.player_y + game->ray->distance * game->ray->raydir_y;
	else
		wall_x = game->player.player_x + game->ray->distance * game->ray->raydir_x;
	wall_x -= floor(wall_x);
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

static inline int darken_rgb_color3 (int color, double factor, int i)
{
	int	r;
	int	g;
	int	b;
	int	j;
	
	j = 0;
	if (factor < 0 || factor > 1)
		return color;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	while (j++ < i)
	{
		r = (int)(r * factor);
		g = (int)(g * factor);
		b = (int)(b * factor);
	}
	return (r << 16) | (g << 8) | b;
}

static inline int	get_fog(t_game *game, int color)
{
	double	distance;
	int		times;

	if (game->ray->distance > 4.2)
		return (0);
	times = 0;
	distance = 1; //distancia do raio, isso implica na forca do fog
	while (distance < game->ray->distance)
	{
		distance += 0.15; //quantidade de step do fog
		times++; // vezes que ele rodou no while
	}
	color = darken_rgb_color3(color, 0.9, times);
	return (color);
}


void	draw_wall(t_game *game, int h_pixel, int l_pixel, int x)
{
	int		color;
	double	step = 1.0 * TEXTURE_H / game->ray->line_height;
	double	texpos = (h_pixel - SCREEN_HEIGHT / 2 + game->ray->line_height / 2) * step;
	int	tex_y;
	
	while(h_pixel++ < l_pixel)
	{
		tex_y= (int)texpos & (TEXTURE_H - 1);
		texpos += step;
		color = get_texture_color(game, tex_y);
		color = get_fog(game, color);
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
	}
}

unsigned long	convert_rgb(char *color)
{
	int		r;
	int		g;
	int		b;
	char	**temp_color;
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
			return (ft_printf("Error with convert_rgb!\n"));
		while(temp_color[i])
			free(temp_color[i++]);
		free(temp_color);
		return (r<<16) | (g<<8) | b;
	}
	return (0);
}

int get_fog_ceiling(int color, int i)
{
	int		times = 18;
	while (i < (SCREEN_HEIGHT / 2) - 110)
	{
		i += 10;
		times--;
	}
	color = darken_rgb_color3(color, 0.9, times);
	return (color);
}

int	get_fog_floor(int color, int i)
{
	int		times = 0;
	int stop = ((SCREEN_HEIGHT / 2) + ((SCREEN_HEIGHT / 2) / 2));
	while (i < stop + 50 && times <= 18)
	{
		i += 10; //quantidade de step do fog
		times++; // vezes que ele rodou no while
	}
	color = darken_rgb_color3(color, 0.9, times);
	return (color);
}
void	draw_ceiling(t_game *game, int x, int ray_count, int h_pixel)
{
	unsigned long	ceiling_rgb;
	unsigned long	ceiling_rgb_set;

	ceiling_rgb_set = convert_rgb(game->map.CEILING_PATH);
	
	int stop = (SCREEN_HEIGHT / 2) - ((SCREEN_HEIGHT / 2) / 2);
	while (x < SCREEN_HEIGHT / 2) //Ceiling
	{
		if (x == h_pixel)
			return ;
		ceiling_rgb = ceiling_rgb_set;
		if (x > ((SCREEN_HEIGHT / 2) + stop) / 2)
		 	better_mlx_pixel_put(&game->img, ray_count, x++, 0);
		else if (x >= ((SCREEN_HEIGHT / 2) / 2) - 100)
		{
			ceiling_rgb = get_fog_ceiling(ceiling_rgb, x);
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
	stop = (SCREEN_HEIGHT / 2) + ((SCREEN_HEIGHT / 2) / 2);
	while (x < SCREEN_HEIGHT)
	{
		while (x < l_pixel)
			x++ ;
		floor_rgb = floor_rgb_set;
		if (x < (((SCREEN_HEIGHT / 2) + stop) / 2))
		 	better_mlx_pixel_put(&game->img, ray_count, x++, 0);
		else if (x < stop + 50)
		{
			floor_rgb = get_fog_floor(floor_rgb, x);
			better_mlx_pixel_put(&game->img, ray_count, x++, floor_rgb);
		}
		else
		better_mlx_pixel_put(&game->img, ray_count, x++, floor_rgb_set); // ceiling
	}
}

void	draw_floor_ceiling(t_game *game, int ray_count, int h_pixel, int l_pixel)
{
	int		x;

	x = 0;
	draw_ceiling(game, x, ray_count, h_pixel);
	x = SCREEN_HEIGHT / 2;
	draw_floor(game, x, ray_count, l_pixel);
}
