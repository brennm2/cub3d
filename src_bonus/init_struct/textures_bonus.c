/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:47:45 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/30 15:49:22 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	ft_process_texture_line(t_game *game)
{
	char	*temp;

	if (ft_check_duplicates(game, game->map.line))
	{
		printf("Error: duplicate textures\n");
		ft_quit_game(game);
		return ;
	}
	temp = ft_strtrim(game->map.line, " ");
	free(game->map.line);
	game->map.line = temp;
	ft_set_texture(game, game->map.line);
}

void	ft_get_textures(t_game *game)
{
	game->map.line = get_next_line(game->fd_file);
	check_string_content(game->map.line);
	while (game->map.line != NULL && !ft_all_textures_set(game))
	{
		if (!ft_check_empty_line(game->map.line, 1))
			ft_process_texture_line(game);
		free(game->map.line);
		game->map.line = get_next_line(game->fd_file);
	}
	ft_skip_empty_lines(game);
	if (game->map.line == NULL)
	{
		printf("Not all textures\n");
		ft_quit_game(game);
	}
	ft_check_color(game);
}

int	ft_set_texture(t_game *game, const char *line)
{
	if (!ft_strncmp(line, NORTH, 3))
		game->map.north_path = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, (SOUTH), 3))
		game->map.south_path = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, EAST, 3))
		game->map.east_path = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, WEST, 3))
		game->map.west_path = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, CEILING, 2))
		game->map.ceiling_path = ft_strtrim(line + 1, " \n");
	else if (!ft_strncmp(line, FLOOR, 2))
		game->map.floor_path = ft_strtrim(line + 1, " \n");
	else
		return (1);
	return (0);
}
