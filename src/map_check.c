/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:33:30 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/03 17:14:52 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

bool ft_check_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return true;
		i++;
	}
	return false;
}

void ft_free_map(t_game *game)
{
	int i;

	i = 0;
	if (game->map.map == NULL)
		return;
	while (game->map.map[i] != NULL)
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
}

unsigned int ft_get_map_size(char **av)
{
	int i;
	int fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening fd\n");
		return 0;
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		i++;
	}
	close(fd);
	return i;
}

void read_textures(t_game *game, char **av)
{
	int fd;
	int lines;
	char *line;

	lines = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening fd\n");
		return;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_check_spaces(line))
		{
			game->map.map[lines] = ft_strdup(line);
			lines++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map.map[lines] = NULL;
	close(fd);
}

char *remove_all_spaces(const char *str) {
	int i = 0, j = 0;
	int len = ft_strlen(str);
	char *result = (char *)malloc(len + 1);
	if (!result) {
		return NULL;
	}

	while (str[i]) {
		if (str[i] != ' ') {
			result[j++] = str[i];
		}
		i++;
	}
	result[j] = '\0';
	return result;
}

void ft_get_textures(t_game *game)
{
	int i;

	i = 0;
	while(game->map.map[i])
	{
		if(ft_strnstr(game->map.map[i], NORTH, ft_strlen(game->map.map[i])) != NULL)
			game->map.NORTH_PATH = ft_strchr(remove_all_spaces(game->map.map[i]), 'N') + 2;
		if(ft_strnstr(game->map.map[i], SOUTH, ft_strlen(game->map.map[i])) != NULL)
			game->map.SOUTH_PATH = ft_strchr(remove_all_spaces(game->map.map[i]), 'S') + 2;
		if(ft_strnstr(game->map.map[i], EAST, ft_strlen(game->map.map[i])) != NULL)
			game->map.EAST_PATH = ft_strchr(remove_all_spaces(game->map.map[i]), 'E') + 2;
		if(ft_strnstr(game->map.map[i], WEST, ft_strlen(game->map.map[i])) != NULL)
			game->map.WEST_PATH = ft_strchr(remove_all_spaces(game->map.map[i]), 'W') + 2;
		if(ft_strnstr(game->map.map[i], CEILING, ft_strlen(game->map.map[i])) != NULL)
			game->map.CEILING_PATH = ft_strchr(remove_all_spaces(game->map.map[i]), 'C') + 1;
		if(ft_strnstr(game->map.map[i], FLOOR, ft_strlen(game->map.map[i])) != NULL)
			game->map.FLOOR_PATH = ft_strchr(remove_all_spaces(game->map.map[i]), 'F') + 1;
		i++;
	}
}

bool ft_check_map(t_game *game, char **av)
{
	unsigned int map_size;

	map_size = ft_get_map_size(av);
	if (map_size == 0)
		return false;
	game->map.map = malloc(sizeof(char *) * (map_size + 1));
	if (!game->map.map)
		return false;
	read_textures(game, av);
	ft_get_textures(game);
	printf("NORTH:%s", game->map.NORTH_PATH);
	printf("SOUTH:%s", game->map.SOUTH_PATH);
	printf("WEST:%s", game->map.WEST_PATH);
	printf("EAST:%s", game->map.EAST_PATH);
	printf("CEILING:%s", game->map.CEILING_PATH);
	printf("FLOOR:%s", game->map.FLOOR_PATH);
	ft_free_map(game);
	return true;
}
