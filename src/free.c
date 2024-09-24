/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:20:16 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/24 16:38:26 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/cub3d.h"

void ft_free_map(char **map)
{
	int i = 0;
	if (map == NULL)
		return;
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
	free(game->map.north_path); //TODO THESE FREE NEEDS TO BE ADDED LATER WHEN THE PROGRAM FINISH
	free(game->map.south_path);
	free(game->map.west_path);
	free(game->map.east_path);
	free(game->map.ceiling_path);
	free(game->map.floor_path);
}

void	free_all(t_game *game)
{
	if (game == NULL)
		return ;

	// Destroy the window if it exists
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);

	// Free the main image if it exists
	if (game->img)
	{
		if (game->img->mlx_img)
			mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
		free(game->img);  // Free the image structure itself
	}

	// Free all textures if they exist
	if (game->texture)
	{
		int i = 0;
		while (game->texture[i])
		{
			if (game->texture[i]->img->mlx_img)  // Check before destroying
				mlx_destroy_image(game->mlx_ptr, game->texture[i]->img->mlx_img);
			free(game->texture[i]->img);  // Free image structure
			free(game->texture[i]);  // Free texture structure
			i++;
		}
		free(game->texture);  // Free texture array
	}

	// Destroy the display if the mlx_ptr exists
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}

	// Free rays if allocated
	if (game->ray)
		free(game->ray);

	// Free the main game structure
	free(game);
}

void free_double_pointer_array(char **array)
{
	if (array == NULL) {
		return;
	}

	int i = 0;
	// Free each individual element in the array
	while (array[i] != NULL) {
		free(array[i]);
		i++;
	}

	// Free the array itself
	free(array);
}


int	ft_quit_game(t_game *game)
{
	//get_next_line(-1);
	if(game->map.line)
	{
		while(game->map.line != NULL)
		{
			free(game->map.line);
			game->map.line = get_next_line(game->fd_file);
		}
	}
	ft_free_textures(game);
	free_all(game);
	exit (0);
}

