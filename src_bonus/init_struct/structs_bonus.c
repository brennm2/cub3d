/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:27:02 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/30 15:30:40 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

t_game	*ft_init_structs(const char *file)
{
	t_game	*game;
	char	**map;

	game = (t_game *)ft_calloc(sizeof(t_game), 1);
	if (game == NULL)
		return (NULL);
	game->fd_file = open(file, O_RDONLY);
	ft_get_textures(game);
	ft_get_map(game);
	ft_check_player(game);
	ft_get_player_pos(game);
	map = ft_dup_map(game);
	ft_flood_fill(game, map, game->player.player_y, game->player.player_x);
	ft_free_map(map);
	game->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (game->ray == NULL)
		return (NULL);
	game->img = ft_calloc(sizeof(t_img), 1);
	if (game->img == NULL)
		return (NULL);
	init_window(game);
	create_all_textures(game);
	return (game);
}

void	ft_set_color(t_game *game, char **color_values, long *color)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(color_values[0]);
	g = ft_atoi(color_values[1]);
	b = ft_atoi(color_values[2]);
	if (r < 0 || g < 0 || b < 0)
	{
		free_double_pointer_array(color_values);
		printf("Negative values\n");
		ft_quit_game(game);
	}
	if (r > 255 || g > 255 || b > 255)
	{
		free_double_pointer_array(color_values);
		printf("Values too big, max is 255\n");
		ft_quit_game(game);
	}
	*color = (r << 16) | (g << 8) | b;
}

void	ft_parse_and_set_color(t_game *game,
			const char *path, long *color, const char *type)
{
	char	**color_split;

	if (ft_count_char(path, ',') != 2)
	{
		printf("Invalid %s colour!\n", type);
		ft_quit_game(game);
		exit(1);
	}
	color_split = ft_split(path, ',');
	if (color_split == NULL || ft_count_colours(color_split) != 3
		||!ft_color_check(color_split))
	{
		free_double_pointer_array(color_split);
		printf("Invalid %s colour!\n", type);
		ft_quit_game(game);
		exit(1);
	}
	ft_set_color(game, color_split, color);
	free_double_pointer_array(color_split);
}

void	check_string_content(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		printf("Empty file\n");
		return ;
	}
	if (has_only_spaces(str))
		printf("Only spaces\n");
	else if (has_only_tabs(str))
		printf("Only tabs\n");
	else if (has_only_spaces(str) && has_only_tabs(str))
		printf("Only spaces and tabs\n");
}

void	init_window(t_game *game)
{
	int	i;

	i = 0;
	game->mlx_ptr = mlx_init();
	game->win_ptr = NULL;
	game->texture = ft_calloc(sizeof(t_texture), 8);
	while (i < 8)
	{
		game->texture[i] = ft_calloc(1, sizeof(t_texture));
		game->texture[i]->h = 64;
		game->texture[i]->w = 64;
		game->texture[i]->img = ft_calloc(1, sizeof(t_img));
		i++;
	}
	game->mouse_x = ft_calloc(sizeof(int *), 1);
	game->mouse_y = ft_calloc(sizeof(int *), 1);
}
