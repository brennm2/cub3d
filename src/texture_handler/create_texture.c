/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:55:25 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/18 13:40:44 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../../includes/cub3d.h"

int	create_north_texture(t_game *game)
{
	game->texture[0]->img->mlx_img = mlx_xpm_file_to_image(
		game->mlx_ptr, game->map.NORTH_PATH, &game->texture[0]->w,
			&game->texture[0]->h);
	if (!game->texture[0]->img->mlx_img)
	{
		printf("\nNo texture created(NORTH)\n\n");
		return (1);
	}
	game->texture[0]->img->addr = mlx_get_data_addr(
		game->texture[0]->img->mlx_img, &game->texture[0]->img->bpp,
			&game->texture[0]->img->line_len,
				&game->texture[0]->img->endian);
	if (!game->texture[0]->img->addr)
	{
		printf("\nNo texture addr created(NORTH)\n\n");
		return (1);
	}
	return (0);
}

int	create_south_texture(t_game *game)
{
	game->texture[1]->img->mlx_img = mlx_xpm_file_to_image(
		game->mlx_ptr, game->map.SOUTH_PATH, &game->texture[1]->w,
			&game->texture[1]->h);
	if (!game->texture[1]->img->mlx_img)
	{
		printf("\nNo texture created (south)\n\n");
		return (1);
	}
	game->texture[1]->img->addr = mlx_get_data_addr(
			game->texture[1]->img->mlx_img, &game->texture[1]->img->bpp,
				&game->texture[1]->img->line_len,
					&game->texture[1]->img->endian);
	if (!game->texture[1]->img->addr)
	{
		printf("\nNo texture addr created(SOUTH)\n\n");
		return (1);
	}
	return (0);
}

int	create_east_texture(t_game *game)
{
	game->texture[2]->img->mlx_img = mlx_xpm_file_to_image(
		game->mlx_ptr, game->map.EAST_PATH, &game->texture[2]->w,
			&game->texture[2]->h);
	if (!game->texture[2]->img->mlx_img)
	{
		printf("\nNo texture created (EAST)\n\n");
		return (1);
	}
	game->texture[2]->img->addr = mlx_get_data_addr(
			game->texture[2]->img->mlx_img, &game->texture[2]->img->bpp,
				&game->texture[2]->img->line_len,
					&game->texture[2]->img->endian);
	if (!game->texture[2]->img->addr)
	{
		printf("\nNo texture addr created(EAST)\n\n");
		return (1);
	}
	return (0);
}

int	create_west_texture(t_game *game)
{
	game->texture[3]->img->mlx_img = mlx_xpm_file_to_image(
		game->mlx_ptr, game->map.WEST_PATH, &game->texture[3]->w,
			&game->texture[3]->h);
	if (!game->texture[3]->img->mlx_img)
	{
		printf("\nNo texture created (WEST)\n\n");
		return (1);
	}
	game->texture[3]->img->addr = mlx_get_data_addr(
			game->texture[3]->img->mlx_img, &game->texture[3]->img->bpp,
				&game->texture[3]->img->line_len,
					&game->texture[3]->img->endian);
	if (!game->texture[3]->img->addr)
	{
		printf("\nNo texture addr created(WEST)\n\n");
		return (1);
	}
	return (0);
}
void	create_texture(t_game *game)
{
	if (create_north_texture(game) == 1)
		return ;
		//#TODO free_all func
	if (create_south_texture(game) == 1)
		return ;
		//#TODO free_all func
	if (create_east_texture(game) == 1)
		return ;
		//#TODO free_all func
	if (create_west_texture(game) == 1)
		return ;
		//#TODO free_all func
}
