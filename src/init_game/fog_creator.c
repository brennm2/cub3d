/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:24:45 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/16 18:32:51 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_fog_floor(int color, int i)
{
	int	times;
	int	stop;

	stop = ((SCREEN_HEIGHT / 2) + ((SCREEN_HEIGHT / 2) / 2));
	times = 0;
	while (i < stop + 50 && times <= 18)
	{
		i += 10;
		times++;
	}
	color = darken_rgb_color3(color, 0.9, times);
	return (color);
}

int	get_fog_ceiling(int color, int i)
{
	int	times;

	times = 18;
	while (i < (SCREEN_HEIGHT / 2) - 110)
	{
		i += 10;
		times--;
	}
	color = darken_rgb_color3(color, 0.9, times);
	return (color);
}

int	get_fog(t_game *game, int color)
{
	double	distance;
	int		times;

	if (game->ray->distance > 4.2)
		return (0);
	times = 0;
	distance = 1;
	while (distance < game->ray->distance)
	{
		distance += 0.101;
		times++;
	}
	color = darken_rgb_color3(color, 0.9, times);
	return (color);
}

int	darken_rgb_color3(int color, double factor, int i)
{
	int	r;
	int	g;
	int	b;
	int	j;

	j = 0;
	if (factor < 0 || factor > 1)
		return (color);
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	while (j++ < i)
	{
		r = (int)(r * factor);
		g = (int)(g * factor);
		b = (int)(b * factor);
	}
	return ((r << 16) | (g << 8) | b);
}
