/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:33:30 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/10 17:38:39 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

bool	ft_check_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (true);
		i++;
	}
	return (false);
}

void	ft_free_textures(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map == NULL)
		return ;
	while (game->map.map[i] != NULL)
	{
		free(game->map.map[i]);
		i++;
	}
	printf("NORTH %s", game->map.NORTH_PATH);
	printf("SOUTH %s", game->map.SOUTH_PATH);
	printf("WEST %s", game->map.WEST_PATH);
	printf("EAST %s", game->map.EAST_PATH);
	printf("CEILING %s", game->map.CEILING_PATH);
	printf("FLOOR %s", game->map.FLOOR_PATH);
	free(game->map.NORTH_PATH); //TODO THESE FREE NEEDS TO BE ADDED LATER WHEN THE PROGRAM FINISH
	free(game->map.SOUTH_PATH);
	free(game->map.WEST_PATH);
	free(game->map.EAST_PATH);
	free(game->map.CEILING_PATH);
	free(game->map.FLOOR_PATH);
	free(game->map.map);
}

unsigned int	ft_get_map_size(char **av)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening fd\n");
		return (0);
	}
	i = 0;
	line = get_next_line(fd);
	while ((line) != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

void	read_textures(t_game *game, char **av)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening fd\n");
		return ;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_check_spaces(line) && lines <= 6)
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

char	*remove_all_spaces(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i] != ' ' && !ft_isalpha(str[i]))
		i++;
	while (ft_isalpha(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] != ' ')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	str = ft_strdup(result);
	free(result);
	return (str);
}

void	ft_get_textures(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	while (game->map.map[i])
	{
		len = ft_strlen(game->map.map[i]);
		if (ft_strnstr(game->map.map[i], NORTH, len) != NULL)
			game->map.NORTH_PATH = remove_all_spaces(game->map.map[i]);
		if (ft_strnstr(game->map.map[i], SOUTH, len) != NULL)
			game->map.SOUTH_PATH = remove_all_spaces(game->map.map[i]);
		if (ft_strnstr(game->map.map[i], EAST, len) != NULL)
			game->map.EAST_PATH = remove_all_spaces(game->map.map[i]);
		if (ft_strnstr(game->map.map[i], WEST, len) != NULL)
			game->map.WEST_PATH = remove_all_spaces(game->map.map[i]);
		if (ft_strnstr(game->map.map[i], CEILING, len) != NULL)
			game->map.CEILING_PATH = remove_all_spaces(game->map.map[i]);
		if (ft_strnstr(game->map.map[i], FLOOR, len) != NULL)
			game->map.FLOOR_PATH = remove_all_spaces(game->map.map[i]);
		i++;
	}
}

void	ft_read_map(t_game *game, char **av)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening fd\n");
		return ;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if(ft_check_spaces(line))
		{
			if(lines > 6)
				game->map.map[lines - 7] = ft_strdup(line);
			lines++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map.map[lines - 7] = NULL;
	close(fd);
}

void print_map(t_game *game) {
	int i = 0;
	while (game->map.map[i] != NULL)
	{
		printf("%s", game->map.map[i]);
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
}

bool ft_map_valid_chars(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while(game->map.map[i][j])
		{
			if(game->map.map[i][j] != '1' && game->map.map[i][j] != '0' && game->map.map[i][j] != 'N' && game->map.map[i][j] != 'E' && game->map.map[i][j] != 'W' && game->map.map[i][j] != 'S' && game->map.map[i][j] != '\n')
			{
				printf("CHAR: %s %i %i\n", game->map.map[i], i, j);
				return false;
			}
			j++;
		}
		i++;
	}
	return true;
}

void free_map(t_game *game)
{
	int i = 0;
	if (game->map.map == NULL)
		return;
	while (game->map.map[i] != NULL)
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
	game->map.map = NULL;
}

bool	ft_check_map(t_game *game, char **av)
{
	unsigned int	map_size;

	map_size = ft_get_map_size(av);
	if (map_size < 6)
		return (false);
	game->map.map = malloc(sizeof(char *) * (map_size + 1));
	if (!game->map.map)
		return (false);
	read_textures(game, av);
	ft_get_textures(game);
	ft_free_textures(game);
	ft_read_map(game, av);
	print_map(game);
	if (!ft_map_valid_chars(game))
		return printf("Invalid chars\n"), free_map(game), false;
	free_map(game);
	return (true);
}
