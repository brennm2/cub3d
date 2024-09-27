/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:55:25 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/27 12:27:06 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_texture(t_game *game, const int index, char *path,
		const char *error_msg)
{
	t_texture	*texture;

	texture = game->texture[index];
	texture->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr,
			path, &texture->w, &texture->h);
	if (texture->img->mlx_img == NULL)
	{
		printf("\nNo texture created (%s)\n\n", error_msg);
		return (1);
	}
	texture->img->addr = mlx_get_data_addr(texture->img->mlx_img,
			&texture->img->bpp, &texture->img->line_len, &texture->img->endian);
	if (texture->img->addr == NULL)
	{
		printf("\nNo texture addr created (%s)\n\n", error_msg);
		return (1);
	}
	return (0);
}

void	create_all_textures(t_game *game)
{
	if (create_texture(game, 0, game->map.north_path, "NORTH")
		|| create_texture(game, 1, game->map.south_path, "SOUTH")
		|| create_texture(game, 2, game->map.east_path, "EAST")
		|| create_texture(game, 3, game->map.west_path, "WEST")
		|| create_texture(game, door, "sprites/door.xpm", "DOOR")
		|| create_texture(game, door_mid, "sprites/door_mid.xpm", "DOOR_MID")
		|| create_texture(game, door_side, "sprites/door_side.xpm", \
			"DOOR_SIDE"))
	{
		ft_quit_game(game);
	}
}
