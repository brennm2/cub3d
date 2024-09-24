/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:38:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/24 18:17:41 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static inline int	get_pixel_color(t_game *game, int higher_pixel,
	int lower_pixel, int t_index)
{
	int	color;

	color = *(unsigned int *)(game->texture[t_index]->img->addr \
	+ (higher_pixel * game->texture[t_index]->img->line_len + lower_pixel \
			* (game->texture[t_index]->img->bpp / 8)));
	return (color);
}


int	find_right_side(t_game *game, int tex_y, int tex_x)
{
	if (game->ray->is_door == true)
	{
		static int temp_fps = 0;
		if (game->ray->is_mid_door == true)
		{
			if (temp_fps < 100000000)
			{
				temp_fps += 1;
				return (get_pixel_color(game, tex_y, tex_x, game->tex_index));
			}
			else
			{
				temp_fps = 0;
				if (game->ray->is_in_y == false)
				{
					if (game->map.map[(int)game->player.player_x][(int)game->new_y] == 'i'
						&& game->ray->door_is_closing == false)
						game->map.map[(int)game->player.player_x][(int)game->new_y] = 'd';
					else if (game->map.map[(int)game->player.player_x][(int)game->new_y] == 'i'
						&& game->ray->door_is_closing == true)
					{
						game->ray->door_is_closing = false;
						game->ray->is_mid_door = false;
						game->map.map[(int)game->player.player_x][(int)game->new_y] = 'D';
					}
				}
				else
				{
					if (game->map.map[(int)game->new_x][(int)game->player.player_y] == 'i'
						&& game->ray->door_is_closing == false)
						game->map.map[(int)game->new_x][(int)game->player.player_y] = 'd';
					else if (game->map.map[(int)game->new_x][(int)game->player.player_y] == 'i'
						&& game->ray->door_is_closing == true)
					{
						game->ray->door_is_closing = false;
						game->ray->is_mid_door = false;
						game->map.map[(int)game->new_x][(int)game->player.player_y] = 'D';
					}
				}
			}
		}
		else
		{
			return (get_pixel_color(game, tex_y, tex_x, game->tex_index));
		}
	}
	else if (game->ray->side == true && game->ray->is_door == false)
	{
		if (game->ray->raydir_y > 0)
			return (get_pixel_color(game, tex_y, tex_x, west_t));
		else
			return (get_pixel_color(game, tex_y, tex_x, east_t));
	}
	else
	{
		if (game->ray->raydir_x > 0)
			return (get_pixel_color(game, tex_y, tex_x, north_t));
		else
			return (get_pixel_color(game, tex_y, tex_x, south_t));
	}
	return (0);
}

int	get_texture_color(t_game *game, int tex_y)
{
	double	wall_x;
	int		tex_x;

	if (game->ray->side == false)
		wall_x = game->player.player_y + game->ray->distance \
			* game->ray->raydir_y;
	else
		wall_x = game->player.player_x + game->ray->distance \
			* game->ray->raydir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * (double)TEXTURE_W;
	if (game->ray->side == false && game->ray->raydir_x > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if (game->ray->side == true && game->ray->raydir_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	return (find_right_side(game, tex_y, tex_x));
}

unsigned long	convert_rgb(char *color)
{
	int		r;
	int		g;
	int		b;
	int		i;
	char	**temp_color;

	i = 0;
	temp_color = ft_split(color, ',');
	if (temp_color)
	{
		if (temp_color[0] && temp_color[1] && temp_color[2])
		{
			r = ft_atoi(temp_color[0]);
			g = ft_atoi(temp_color[1]);
			b = ft_atoi(temp_color[2]);
		}
		else
			return (ft_printf("Error with convert_rgb!\n"));
		while (temp_color[i])
			free(temp_color[i++]);
		free(temp_color);
		return ((r << 16) | (g << 8) | b);
	}
	return (0);
}

void	better_mlx_pixel_put(t_img **img, int x, int y, int color)
{
	char	*dst;

	dst = (*img)->addr + (y * (*img)->line_len + x * ((*img)->bpp / 8));
	*(unsigned int *)dst = color;
}
