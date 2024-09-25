/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:20:16 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/25 14:11:40 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_free_textures(t_game *game)
{
	ft_free_map(game->map.map);
	free(game->map.north_path);
	free(game->map.south_path);
	free(game->map.west_path);
	free(game->map.east_path);
	free(game->map.ceiling_path);
	free(game->map.floor_path);
}

void	free_mlx_resources(t_game *game)
{
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->img)
	{
		if (game->img->mlx_img)
			mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
		free(game->img);
	}
}

void	free_all(t_game *game)
{
	if (game == NULL)
		return ;
	free_mlx_resources(game);
	if (game->texture)
		free_textures(game);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (game->ray)
		free(game->ray);
	free(game);
}

void	free_double_pointer_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
