/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_fuctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:46:29 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/18 12:04:34 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//cub3d.h"

void	show_map(t_game *game)
{
	int	i;

	i = 0;
	printf("map name: %s\n", game->map_name);
	while(i < game->map.height)
	{
		ft_printf("%s", game->map.map[i]);
		i++;
	}
}

void show_fps_debug(t_game *game)
{
	game->fps->time = clock();
	game->fps->frametime = game->fps->time - game->fps->old_time;
	game->fps->old_time = game->fps->time; // Atualizar old_time após calcular frametime

	if (game->fps->frametime > 0)
		game->fps->fps = CLOCKS_PER_SEC / (double)game->fps->frametime;
	else
		game->fps->fps = 0.0; // Evitar divisão por zero
	game->fps->temp_fps += game->fps->fps;

	if (game->fps->temp_fps > 60)
		game->fps->temp_fps = 0;
	//printf("temp: %f\n", game->fps->temp_fps);
	// if (game->fps->fps >= 36)
	// 	printf("\033[0;32mFPS: %.2f\033[0;37m\n", game->fps->fps);
	// else if (game->fps->fps <= 34)
	// 	printf("\033[0;31mFPS: %.2f\033[0;37m\n", game->fps->fps);
	// else
	// 	printf("FPS: %.2f\n", game->fps->fps);
}