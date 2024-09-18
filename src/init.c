/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:42:38 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/18 16:50:14 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <assert.h>

bool has_valid_chars(const char *str, const char *valid_chars) //TODO ADD TO LIBFT
{
	int i, j;
	bool is_valid;

	i = 0;
	while (str[i])
	{
		is_valid = false;
		j = 0;
		while (valid_chars[j])
		{
			if (str[i] == valid_chars[j])
			{
				is_valid = true;
				break;
			}
			j++;
		}
		if (!is_valid)
			return false;
		i++;
	}
	return true;
}

static void ft_extend_map(t_game *game)
{
	int i = 0;
	char **new_map = malloc(sizeof(char *) * (game->map.height + 2));
	if (new_map == NULL)
		return ; //TODO change this function to deal with leaks and print error
	while (game->map.map[i] != NULL)
	{
		new_map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	new_map[i] = NULL;
	i = 0;
	while(game->map.map[i])
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
	game->map.map = new_map;
}

bool ft_check_empty_line(const char *line, int option)
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

void ft_get_map(t_game *game)
{
	game->map.map = malloc(sizeof (char *) * 2);
	if (game->map.map == NULL)
		return ; // TODO CHANGE TO FUNCTION TO PRINT AND EXIT
	while(game->map.line != NULL)
	{
		if(!ft_check_empty_line(game->map.line, 2))
		{
			if (!has_valid_chars(game->map.line, "10NSWE\n"))
			{
				printf("Invalid char!\n");
				exit(1); //TODO change to funtion to print, free and exit
			}
			game->map.map[game->map.height] = ft_strdup(game->map.line);
			game->map.height++;
			game->map.map[game->map.height] =  NULL;
			ft_extend_map(game);
		}
		free(game->map.line);
		game->map.line = get_next_line(game->fd_file);
	}
	close(game->fd_file);
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

char	*remove_all_spaces(char *str)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	result = (char *) malloc(ft_strlen(str) + 1);
	if (result == NULL)
		return (NULL);
	while (str[i] != ' ' && !ft_isalpha(str[i]))
		i++;
	while (ft_isalpha(str[i]))
		i++;
	while (str[i]) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	str = ft_strdup(result);
	free(result);
	return (str);
}

int ft_set_texture(t_game *game, char *line)
{
	size_t len;

	len = ft_strlen(line);

	if(!ft_strncmp(line, NORTH, 3))
		game->map.NORTH_PATH = remove_all_spaces(line);
	else if(!ft_strncmp(line, (SOUTH), 3))
		game->map.SOUTH_PATH = remove_all_spaces(line);
	else if(!ft_strncmp(line, EAST, 3))
		game->map.EAST_PATH = remove_all_spaces(line);
	else if(!ft_strncmp(line, WEST, 3))
		game->map.WEST_PATH = remove_all_spaces(line);
	else if(!ft_strncmp(line, CEILING,	 2))
		game->map.CEILING_PATH = remove_all_spaces(line);
	else if(!ft_strncmp(line, FLOOR, 2))
		game->map.FLOOR_PATH = remove_all_spaces(line);
	else
		return 1;
	return 0;
}

bool ft_check_duplicates(t_game *game, char *line)
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

void	set_player_direction(t_game *game, char c)
{
	if(c == 'N')
	{
		game->dirx = -1;
		game->plane_y = 0.66;
	}
	else if(c == 'S')
	{
		game->dirx = 1;
		game->plane_y = -0.66;
	}
	else if(c == 'E')
	{
		game->diry = 1;
		game->plane_x = 0.66;
	}
	else if(c == 'W')
	{
		game->diry = -1;
		game->plane_x = -0.66;
	}
}

void ft_get_player_pos(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while(game->map.map[i][j])
		{
			if(game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' || game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				game->player.player_x = i + 0.5;
				game->player.player_y = j + 0.5;
				set_player_direction(game, game->map.map[i][j]);
				game->map.map[i][j] = '0';
				return;
			}
			j++;
		}
		i++;
	}
}
