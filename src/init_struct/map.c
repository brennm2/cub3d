/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:05:32 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/27 12:23:22 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_get_map(t_game *game)
{
	game->map.map = malloc(sizeof (char *) * 2);
	if (game->map.map == NULL)
		return ;
	while (game->map.line != NULL)
	{
		if (!ft_check_empty_line(game->map.line, 2))
		{
			if (!has_valid_chars(game->map.line, " 10NSWE\n"))
			{
				game->map.map[game->map.height] = NULL;
				printf("Invalid char!\n");
				ft_quit_game(game);
			}
			game->map.map[game->map.height] = ft_strdup(game->map.line);
			game->map.height++;
			game->map.map[game->map.height] = NULL;
			ft_extend_map(game);
		}
		free(game->map.line);
		game->map.line = get_next_line(game->fd_file);
	}
	close(game->fd_file);
}

bool	has_valid_chars(const char *str,
			const char *valid_chars)
{
	int		i;
	int		j;
	bool	is_valid;

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
				break ;
			}
			j++;
		}
		if (!is_valid)
			return (false);
		i++;
	}
	return (true);
}

void	ft_extend_map(t_game *game)
{
	int		i;
	char	**new_map;

	new_map = malloc(sizeof(char *) * (game->map.height + 2));
	i = 0;
	if (new_map == NULL)
		return ;
	while (game->map.map[i] != NULL)
	{
		new_map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	new_map[i] = NULL;
	i = 0;
	while (game->map.map[i])
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
	game->map.map = new_map;
}

char	**ft_dup_map(const t_game *game)
{
	char	**map_test;
	int		i;

	i = -1;
	map_test = ft_calloc(game->map.height + 1, sizeof (char *));
	if (map_test == NULL)
		return (NULL);
	while (++i < game->map.height)
		map_test[i] = ft_strdup(game->map.map[i]);
	map_test[i] = NULL;
	return (map_test);
}

int	ft_flood_fill(t_game *game, char **map, const int x, const int y)
{
	if (x < 0 || y < 0 || y >= game->map.height
		|| x >= (int)ft_strlen(map[y]) || map[y][x] == 32)
	{
		printf("Invalid Map(Not Wall Closed)\n");
		free_double_pointer_array(map);
		ft_quit_game(game);
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
