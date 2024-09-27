/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:15:53 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/27 15:21:40 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_game(t_game *game)
{
	display_window(game);
	if (game->win_ptr == NULL)
		return ;
	mlx_loop_hook(game->mlx_ptr, &game_frame_loop, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_handler, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
		&ft_quit_game, game);
	//mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_loop(game->mlx_ptr);
}

void	display_window(t_game *game)
{
	if (game->mlx_ptr == NULL)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (game->win_ptr == NULL)
		return ;
}

int	game_frame_loop(t_game *game)
{
	if (game->login == true)
	{
		if (game->img && game->img->mlx_img)
			mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
		game->img->mlx_img = mlx_new_image(game->mlx_ptr,
				SCREEN_WIDTH, SCREEN_HEIGHT);
		game->img->addr = mlx_get_data_addr(game->img->mlx_img,
				&game->img->bpp, &game->img->line_len, &game->img->endian);
		shoot_rays(game);
		if (game->map.show_minimap == true)
			minimap(game);
		mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, game->mouse_x, \
			game->mouse_y);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, (SCREEN_WIDTH / 2), \
			(SCREEN_HEIGHT / 2));
		mouse_direction(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img->mlx_img, 0, 0);
	}
	else
		login_screen(game);
	return (0);
}
