/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:20:16 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/10 15:17:38 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/cub3d.h"

// void	free_map(char **map, t_game *game)
// {
// 	int	i;

// 	i = -1;
// 	if (!map[0])
// 	{
// 		free (game->map.map);
// 		return ;
// 	}
// 	while (++i < game->map_h)
// 		free(game->map[i]);
// 	free(game->map);
// }

void	free_all(t_game *game)
{
	if (!game)
		return ;
	// if (game->map)
	// 	free_map(game->map, game);
	//if (game->map_copy)
	//	free_map_copy(game->map_copy, game);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->img)
	{
		if (game->img->mlx_img)
			mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
		//free(game->img->mlx_img);
		free(game->img);
	}
	//if (game->img.mlx_img)
	//	mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if(game->ray)
		free(game->ray);
	if(game->player)
		free(game->player);
	free (game);
}