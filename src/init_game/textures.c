/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:47:45 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/23 14:57:00 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void ft_get_textures(t_game *game)
{
	game->map.line = get_next_line(game->fd_file);
	// check_string_content(game->map.line);
	while (game->map.line != NULL && !ft_all_textures_set(game))
	{
		if (!ft_check_empty_line(game->map.line, 1))
		{
			if(ft_check_duplicates(game, game->map.line))
			{
				printf("Error: duplicate textures");
				return ;
			}
			game->map.line = ft_strtrim(game->map.line, " ");
			ft_set_texture(game, game->map.line);
		}
		free(game->map.line);
		game->map.line = get_next_line(game->fd_file);
	}
	while(game->map.line != NULL && ft_check_empty_line(game->map.line, 1))
	{
		free(game->map.line);
		game->map.line = get_next_line(game->fd_file);
	}
	if(game->map.line == NULL)
	{
		printf("Not all testures\n");
		exit(1);
	}
	// ft_check_color(game);
}

bool ft_all_textures_set(t_game const *game)
{
	if (game->map.NORTH_PATH != NULL && game->map.SOUTH_PATH != NULL
		&& game->map.WEST_PATH != NULL && game->map.EAST_PATH != NULL
		&& game->map.CEILING_PATH != NULL && game->map.FLOOR_PATH != NULL)
	{
		return true;
	}
	return false;
}

bool ft_check_empty_line(const char *line, const int option)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (option == 1)
		{
			if (line[i] != ' ' && line[i] != '\n')
				return false;
		}
		else
		{
			if (line[i] != '\n')
				return false;
		}
		i++;
	}
	return true;
}

bool ft_check_duplicates(const t_game *game,const char *line)
{
	size_t len;

	len = ft_strlen(line);

	if(ft_strnstr(line, NORTH, len) && game->map.NORTH_PATH != NULL)
		return true;
	if(ft_strnstr(line, SOUTH, len)&& game->map.SOUTH_PATH != NULL)
		return true;
	if(ft_strnstr(line, EAST, len)&& game->map.EAST_PATH != NULL)
		return true;
	if(ft_strnstr(line, WEST, len)&& game->map.WEST_PATH != NULL)
		return true;
	if(ft_strnstr(line, CEILING, len)&& game->map.CEILING_PATH != NULL)
		return true;
	if(ft_strnstr(line, FLOOR, len)&& game->map.FLOOR_PATH != NULL)
		return true;
	return false;
}

int ft_set_texture(t_game *game, const char *line)
{
	if(!ft_strncmp(line, NORTH, 3))
		game->map.NORTH_PATH = ft_strtrim(line + 2, " \n");
	else if(!ft_strncmp(line, (SOUTH), 3))
		game->map.SOUTH_PATH = ft_strtrim(line + 2, " \n");
	else if(!ft_strncmp(line, EAST, 3))
		game->map.EAST_PATH = ft_strtrim(line + 2, " \n");
	else if(!ft_strncmp(line, WEST, 3))
		game->map.WEST_PATH = ft_strtrim(line + 2, " \n");
	else if(!ft_strncmp(line, CEILING,	 2))
		game->map.CEILING_PATH = ft_strtrim(line + 1, " \n");
	else if(!ft_strncmp(line, FLOOR, 2))
		game->map.FLOOR_PATH = ft_strtrim(line + 1, " \n");
	else
		return 1;
	return 0;
}