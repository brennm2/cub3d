/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:27:02 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/18 16:39:03 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void ft_print_map(char **map)
{
	int i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int ft_flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.height || x >= (int)ft_strlen(map[y]) || map[y][x] == 32)
	{
		printf("Invalid Map(Not Wall Closed)\n");
		exit(1);
	}
	if (map[y][x] == '1')
		return (1);
	map[y][x] = '1';
	ft_flood_fill(game, map, x + 1, y);
	ft_flood_fill(game, map, x - 1, y);
	ft_flood_fill(game, map, x, y + 1);
	ft_flood_fill(game, map, x, y - 1);
	return (0);
}

char	**ft_dup_map(t_game *game)
{
	char	**map_test;
	int		i;

	i = -1;
	map_test = ft_calloc(game->map.height + 1, sizeof (char *));
	if (map_test == NULL)
		free(map_test);
	else
		while (++i < game->map.height)
			map_test[i] = ft_strdup(game->map.map[i]);
	map_test[i] = NULL;
	return (map_test);
}

t_game *ft_init_structs(char *file)
{
	t_game *game;
	char **map;

	game = (t_game *)ft_calloc(sizeof(t_game), 1);
	if (game == NULL)
		return (NULL); // TODO put function to print and free memory
	game->fd_file = open(file, O_RDONLY);
	ft_get_textures(game);
	ft_get_map(game);
	ft_get_player_pos(game);
	map = ft_dup_map(game);
	ft_flood_fill(game, map, 1, 1);
	ft_free_map(map);
	game->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (game->ray == NULL)
		return (NULL);
	game->img = ft_calloc(sizeof(t_img), 1);
	if (game->img == NULL)
		return (NULL);
	return game;
}

int ft_count_colours(char **colours)
{
	int i;

	i = 0;
	while(colours[i])
		i++;
	return i;
}

void ft_set_color(char **color_values, long *color)
{
	int r, g, b;

	r = ft_atoi(color_values[0]);
	g = ft_atoi(color_values[1]);
	b = ft_atoi(color_values[2]);

	if (r < 0 || g < 0 || b < 0)
	{
		printf("Negative values\n");
		exit(1); // TODO: Replace with function to print and free
	}
	if(r > 255 || g > 255 || b > 255)
	{
		printf("Values too big, max is 255\n");
		exit(1);
	}
	*color = (r << 16) | (g << 8) | b;
}

void ft_check_color(t_game *game)
{
	char **color_ceiling;
	char **color_floor;

	color_ceiling = ft_split(game->map.CEILING_PATH, ',');
	color_floor = ft_split(game->map.FLOOR_PATH, ',');

	if (color_ceiling && ft_count_colours(color_ceiling) == 3 &&
		color_floor && ft_count_colours(color_floor) == 3)
	{
		ft_set_color(color_ceiling, &game->map.CEILING_COLOR);
		ft_set_color(color_floor, &game->map.FLOOR_COLOR);
	}
	else
	{
		printf("Invalid color format\n");
		exit(1); // TODO: Replace with function to print and free
	}
}


void ft_get_textures(t_game *game)
{
	game->map.line = get_next_line(game->fd_file);
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
	ft_check_color(game);
}
