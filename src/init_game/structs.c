/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:27:02 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/18 13:12:07 by bsousa-d         ###   ########.fr       */
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
	//duplica o mapa & flood fill
	// if (flood fill passar)
	// else (exit clean)
	game->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (game->ray == NULL)
		return (NULL);
	game->img = ft_calloc(sizeof(t_img), 1);
	if (game->img == NULL)
		return (NULL);
	return game;
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
}
