/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:27:02 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/24 17:46:48 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_game *ft_init_structs(const char *file)
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
	ft_flood_fill(game, map, game->player.player_x, game->player.player_y);
	ft_free_map(map);
	game->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (game->ray == NULL)
		return (NULL);
	game->img = ft_calloc(sizeof(t_img), 1);
	if (game->img == NULL)
		return (NULL);
	init_window(game);
	create_all_textures(game);
	return game;
}

size_t ft_count_char(const char *str, const char find)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == find)
			count++;
		i++;
	}
	return count;
}

int ft_count_colours(char **colours)
{
	int i;

	i = 0;
	while(colours[i])
		i++;
	return i;
}

void ft_set_color(t_game *game, char **color_values, long *color)
{
	int r, g, b;

	r = ft_atoi(color_values[0]);
	g = ft_atoi(color_values[1]);
	b = ft_atoi(color_values[2]);

	if (r < 0 || g < 0 || b < 0)
	{
		free_double_pointer_array(color_values);
		printf("Negative values\n");
		ft_quit_game(game);
		exit(1); // TODO: Replace with function to print and free
	}
	if(r > 255 || g > 255 || b > 255)
	{
		free_double_pointer_array(color_values);
		printf("Values too big, max is 255\n");
		ft_quit_game(game);
		exit(1);
	}
	*color = (r << 16) | (g << 8) | b;
}


void	ft_parse_and_set_color(t_game *game, const char *path, long *color, const char *type)
{
	char **color_split;

	if (ft_count_char(path, ',') != 2)
	{
		printf("Invalid %s colour!\n", type);
		ft_quit_game(game);
		exit(1);
	}

	color_split = ft_split(path, ',');
	if (color_split == NULL || ft_count_colours(color_split) != 3)
	{
		free_double_pointer_array(color_split);
		printf("Invalid %s colour!\n", type);
		ft_quit_game(game);
		exit(1);
	}
	ft_set_color(game, color_split, color);
	free_double_pointer_array(color_split);
}

void	ft_check_color(t_game *game)
{
	ft_parse_and_set_color(game, game->map.ceiling_path, &game->map.ceiling_color, "CEILING");
	ft_parse_and_set_color(game, game->map.floor_path, &game->map.floor_color, "FLOOR");
}

void check_string_content(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		printf("Empty file\n");
		return;
	}

	bool only_spaces = false;
	bool only_tabs = false;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ') {
			only_spaces = true;
		}
		if (str[i] == '\t') {
			only_tabs = true;
		}
		if (str[i] != '\t' && str[i] != ' ') {
			return;
		}
	}
	if (only_spaces && only_tabs)
		printf("Only spaces and tabs\n");
	else if (only_spaces) {
		printf("Only spaces\n");
	} else if (only_tabs) {
		printf("Only tabs\n");
	}
}

void	init_window(t_game *game)
{
	game->mlx_ptr= mlx_init();
	game->win_ptr= NULL;
	game->texture = ft_calloc(sizeof(t_texture), 4);
	for (int i = 0; i < 4; i++)
	{
		game->texture[i] = ft_calloc(1, sizeof(t_texture));
		game->texture[i]->h = 64;
		game->texture[i]->w = 64;
		game->texture[i]->img = ft_calloc(1, sizeof(t_img));
	}
}
