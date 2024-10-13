/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:21:22 by bde-souz          #+#    #+#             */
/*   Updated: 2024/10/13 17:13:37 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	create_text_to_window(t_game *game, int x_p, int y_p)
{
	if (game->img && game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	game->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
			"sprites/text.xpm", &x_p, &y_p);
	if (game->img->mlx_img == NULL)
	{
		printf("\nNo texture created (TEXT)\n\n");
		ft_quit_game(game);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
				game->img->mlx_img, (SCREEN_WIDTH / 2) - (x_p / 2), 550);
}

void	create_logo_to_window(t_game *game, int x_p, int y_p)
{
	if (game->img && game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	game->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
			"sprites/logo.xpm", &x_p, &y_p);
	if (game->img->mlx_img == NULL)
	{
		printf("\nNo texture created (LOGO)\n\n");
		ft_quit_game(game);
	}
}

void	login_screen(t_game *game)
{
	static double	moves = 500;
	static bool		logo;

	while (moves < 150)
	{
		create_logo_to_window(game, 514, 375);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
				game->img->mlx_img, (SCREEN_WIDTH / 2) - (514 / 2), moves);
		moves += 1.5;
	}
	if (logo == false)
	{
		create_text_to_window(game, 779, 200);
		logo = true;
	}
}
