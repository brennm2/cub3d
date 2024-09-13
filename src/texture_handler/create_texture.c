/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:55:25 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/13 12:15:55 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../header/cub3d.h"

void	create_texture(t_game *game)
{
	//texture 0 = N
	game->texture[0]->img->mlx_img = mlx_xpm_file_to_image(
			game->mlx_ptr, "sprites/north_wall.xpm", &game->texture[0]->w,
				&game->texture[0]->h);
	if (!game->texture[0]->img->mlx_img)
	{
		printf("\nno texture created(NORTH)\n\n");
	}
	game->texture[0]->img->addr = mlx_get_data_addr(
			game->texture[0]->img->mlx_img, &game->texture[0]->img->bpp,
				&game->texture[0]->img->line_len,
					&game->texture[0]->img->endian);
	if (!game->texture[0]->img->addr)
	{
		printf("\nno texture addr created(NORTH)\n\n");
	}
	
	
	//texture 1 = S
	game->texture[1]->img->mlx_img = mlx_xpm_file_to_image(
			game->mlx_ptr, "sprites/south_wall.xpm", &game->texture[1]->w,
				&game->texture[1]->h);
	if (!game->texture[1]->img->mlx_img)
		printf("\nno texture created (south)\n\n");


	game->texture[1]->img->addr = mlx_get_data_addr(
			game->texture[1]->img->mlx_img, &game->texture[1]->img->bpp,
				&game->texture[1]->img->line_len,
					&game->texture[1]->img->endian);
	if (!game->texture[1]->img->addr)
		printf("\nno texture addr created(SOUTH)\n\n");

	//texture 2 = E
	game->texture[2]->img->mlx_img = mlx_xpm_file_to_image(
			game->mlx_ptr, "sprites/east_wall.xpm", &game->texture[2]->w,
				&game->texture[2]->h);
	if (!game->texture[2]->img->mlx_img)
		printf("\nno texture created (EAST)\n\n");
		
		
	game->texture[2]->img->addr = mlx_get_data_addr(
			game->texture[2]->img->mlx_img, &game->texture[2]->img->bpp,
				&game->texture[2]->img->line_len,
					&game->texture[2]->img->endian);
	if (!game->texture[2]->img->addr)
		printf("\nno texture addr created(EAST)\n\n");

	//texture 3 = W
	game->texture[3]->img->mlx_img = mlx_xpm_file_to_image(
			game->mlx_ptr, "sprites/west_wall.xpm", &game->texture[3]->w,
				&game->texture[3]->h);
	if (!game->texture[3]->img->mlx_img)
		printf("\nno texture created (WEST)\n\n");
		
		
	game->texture[3]->img->addr = mlx_get_data_addr(
			game->texture[3]->img->mlx_img, &game->texture[3]->img->bpp,
				&game->texture[3]->img->line_len,
					&game->texture[3]->img->endian);
	if (!game->texture[3]->img->addr)
		printf("\nno texture addr created(WEST)\n\n");


	

	
}