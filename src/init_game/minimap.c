/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:57:13 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/27 15:07:18 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	create_minimap_background(t_game *game)
{
	int	x_p;
	int	y_p;

	x_p = SCREEN_HEIGHT;
	y_p = SCREEN_WIDTH;
	if (game->img && game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	game->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
		"sprites/handmap.xpm", &x_p, &y_p);
	if (!game->img->mlx_img)
	{
		printf("\nNo texture created (hand_map)\n\n");
		ft_quit_game(game);
	}
	game->img->addr = mlx_get_data_addr(game->img->mlx_img, &game->img->bpp, \
		&game->img->line_len, &game->img->endian);
	if (!game->img->addr)
	{
		printf("\nNo texture addr created(hand_map)\n\n");
		ft_quit_game(game);
	}
}

void	draw_box(t_game *game, int pos_y, int pos_x, long color)
{
	int	x;
	int	y;
	int	scale;

	scale = (SCREEN_HEIGHT / game->map.height) * 0.3;
	y = pos_y + 1;
	while (y < pos_y + scale)
	{
		x = pos_x + 1;
		while (x < pos_x + scale && x < SCREEN_WIDTH - 150)
		{
			better_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	select_box(t_game *game, int x, int y)
{
	int	player_step_x;
	int	player_step_y;
	int	scale;

	scale = (SCREEN_HEIGHT / game->map.height) * 0.3;
	player_step_x = (int)game->player.player_x * scale
		+ (SCREEN_HEIGHT / 2) - ((game->map.height * scale) / 2);
	player_step_y = (int)game->player.player_y * scale + (SCREEN_WIDTH / 2)
		- ((10 * scale) / 2);
	if (game->map.map[y][x] == '1')
		draw_box(game, game->mm_step_y, game->mm_step_x, 7995649);
	else if (game->map.map[y][x] == '0')
		draw_box(game, game->mm_step_y, game->mm_step_x, 5263440);
	else if (game->map.map[y][x] == 'D' || game->map.map[y][x] == 'i')
		draw_box(game, game->mm_step_y, game->mm_step_x, 15118117);
	else if (game->map.map[y][x] == 'd' || game->map.map[y][x] == 'i')
		draw_box(game, game->mm_step_y, game->mm_step_x, 5061133);
	draw_box(game, player_step_x, player_step_y, 90000);
}

void	draw_minimap_row(t_game *game, int y)
{
	int	x;
	int	scale;

	scale = (SCREEN_HEIGHT / game->map.height) * 0.3;
	x = 0;
	while (game->map.map[y][x])
	{
		select_box(game, x, y);
		game->mm_step_x += scale;
		if (game->map.map[y][x] == '\n')
		{
			game->mm_step_x = SCREEN_WIDTH / 2 - ((10 * scale) / 2);
			break ;
		}
		x++;
	}
}

void	minimap(t_game *game)
{
	int	y;
	int	scale;

	scale = (SCREEN_HEIGHT / game->map.height) * 0.3;
	y = 0;
	game->mm_step_x = SCREEN_WIDTH / 2 - ((10 * scale) / 2);
	game->mm_step_y = (SCREEN_HEIGHT / 2) - ((game->map.height * scale) / 2);
	create_minimap_background(game);
	while (y < game->map.height)
	{
		draw_minimap_row(game, y);
		game->mm_step_y += scale;
		y++;
	}
}
