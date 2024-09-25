/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endgame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:08:31 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/25 14:09:04 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_quit_game(t_game *game)
{
	if (game->map.line)
	{
		while (game->map.line != NULL)
		{
			free(game->map.line);
			game->map.line = get_next_line(game->fd_file);
		}
	}
	ft_free_textures(game);
	free_all(game);
	exit (0);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (game->texture[i])
	{
		if (game->texture[i]->img->mlx_img)
			mlx_destroy_image(game->mlx_ptr, game->texture[i]->img->mlx_img);
		free(game->texture[i]->img);
		free(game->texture[i]);
		i++;
	}
	free(game->texture);
}
