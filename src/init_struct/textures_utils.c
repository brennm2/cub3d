/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:39:43 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/25 13:41:19 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_check_duplicates(const t_game *game, const char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strnstr(line, NORTH, len) && game->map.north_path != NULL)
		return (true);
	if (ft_strnstr(line, SOUTH, len) && game->map.south_path != NULL)
		return (true);
	if (ft_strnstr(line, EAST, len) && game->map.east_path != NULL)
		return (true);
	if (ft_strnstr(line, WEST, len) && game->map.west_path != NULL)
		return (true);
	if (ft_strnstr(line, CEILING, len) && game->map.ceiling_path != NULL)
		return (true);
	if (ft_strnstr(line, FLOOR, len) && game->map.floor_path != NULL)
		return (true);
	return (false);
}

bool	ft_check_empty_line(const char *line, const int option)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (option == 1)
		{
			if (line[i] != ' ' && line[i] != '\n')
				return (false);
		}
		else
		{
			if (line[i] != '\n')
				return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_all_textures_set(t_game const *game)
{
	if (game->map.north_path != NULL && game->map.south_path != NULL
		&& game->map.west_path != NULL && game->map.east_path != NULL
		&& game->map.ceiling_path != NULL && game->map.floor_path != NULL)
	{
		return (true);
	}
	return (false);
}

void	ft_skip_empty_lines(t_game *game)
{
	while (game->map.line != NULL && ft_check_empty_line(game->map.line, 1))
	{
		free(game->map.line);
		game->map.line = get_next_line(game->fd_file);
	}
}
