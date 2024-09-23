/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:55:25 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/23 15:35:34 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int create_texture(const t_game *game, const int index, char *path, const char *error_msg)
{
	t_texture *texture = game->texture[index];

	texture->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->w, &texture->h);
	if (texture->img->mlx_img == NULL)
	{
		printf("\nNo texture created (%s)\n\n", error_msg);
		return (1);
	}

	texture->img->addr = mlx_get_data_addr(texture->img->mlx_img, &texture->img->bpp,
										   &texture->img->line_len, &texture->img->endian);
	if (texture->img->addr == NULL)
	{
		printf("\nNo texture addr created (%s)\n\n", error_msg);
		return (1);
	}
	return (0);
}

void create_all_textures(const t_game *game)
{
	if (create_texture(game, 0, game->map.NORTH_PATH, "NORTH") ||
		create_texture(game, 1, game->map.SOUTH_PATH, "SOUTH") ||
		create_texture(game, 2, game->map.EAST_PATH, "EAST") ||
		create_texture(game, 3, game->map.WEST_PATH, "WEST"))
	{
		// TODO free and exit
		exit(1);
		return;
	}
}
