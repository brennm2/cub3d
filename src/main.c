/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/06 17:02:57 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/cub3d.h"

bool	syntax_error(char *map_name)
{
	(void)map_name;
	return (false);
}

void	init_window(t_game *game)
{
	game->mlx_ptr= mlx_init();
	game->win_ptr= NULL;
}


void	display_window(t_game *game)
{
	if(game->mlx_ptr == NULL)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr, 500, 500, "cub3d");
	if(game->win_ptr == NULL)
		return ;
}

void	open_window(t_game *game)
{
	display_window(game);
	if (!game->win_ptr)
		return ;
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_handler, game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
		&ft_quit_game, game);
	mlx_loop(game->mlx_ptr);
}

void	init_game(t_game *game)
{
	init_window(game);
}

static bool is_cub_file(char *argv)
{
	char *dot_position;

	dot_position = strrchr(argv, '.');
	if (dot_position)
		if (strcmp(dot_position, ".cub") == 0)
			if (dot_position > argv && *(dot_position - 1) != '/')
				return true;
	printf("Error: File not valid!\n");
	exit(1);
}

static void ft_check_args(int ac)
{
	if (ac != 2)
	{
		if (ac > 2)
			printf("Error: Too Many Arguments!\n");
		if (ac < 2)
			printf("Error: Not Enough Arguments!\n");
		exit(1);
	}
}

void file_exist(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		printf("Error: File does not exist!\n");
		exit(1);
	}
}

bool ft_check_empty_line(const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if(line[i] != ' ' && line[i] != '\n')
			return false;
		i++;
	}
	return true;
}

bool ft_check_empty_line_between(const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if(line[i] != '\n')
			return false;
		i++;
	}
	return true;
}

char	*remove_all_spaces(char *str)
{
	int i;
	int j;
	char *result;

	i = 0;
	j = 0;
	result = (char *) malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i] != ' ' && !ft_isalpha(str[i]))
		i++;
	while (ft_isalpha(str[i]))
		i++;
	while (str[i]) {
		if (str[i] != ' ')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	str = ft_strdup(result);
	free(result);
	return (str);
}

int ft_get_value(t_game *game, char *line)
{
	size_t len;

	len = ft_strlen(line);

	if(ft_strnstr(line, NORTH, len))
		game->map.NORTH_PATH = remove_all_spaces(line);
	else if(ft_strnstr(line, SOUTH, len))
		game->map.SOUTH_PATH = remove_all_spaces(line);
	else if(ft_strnstr(line, EAST, len))
		game->map.EAST_PATH = remove_all_spaces(line);
	else if(ft_strnstr(line, WEST, len))
		game->map.WEST_PATH = remove_all_spaces(line);
	else if(ft_strnstr(line, CEILING, len))
		game->map.CEILING_PATH = remove_all_spaces(line);
	else if(ft_strnstr(line, FLOOR, len))
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
	else if(ft_strnstr(line, SOUTH, len)&& game->map.SOUTH_PATH != NULL)
		return true;
	else if(ft_strnstr(line, EAST, len)&& game->map.EAST_PATH != NULL)
		return true;
	else if(ft_strnstr(line, WEST, len)&& game->map.WEST_PATH != NULL)
		return true;
	else if(ft_strnstr(line, CEILING, len)&& game->map.CEILING_PATH != NULL)
		return true;
	else if(ft_strnstr(line, FLOOR, len)&& game->map.FLOOR_PATH != NULL)
		return true;
	else
		return false;
}

void ft_get_textures(t_game *game)
{
	char *line;
	int flag;

	line = get_next_line(game->fd_file);
	while (line != NULL)
	{
		if (ft_check_empty_line(line))
		{
			free(line);
			line = get_next_line(game->fd_file);
			continue;
		}
		if (!ft_check_duplicates(game, line))
			flag = ft_get_value(game, line);
		else
			printf("Error: duplicate"); //TODO change to the function that prints and exits
		if(flag)
			break;
		free(line);
		line = get_next_line(game->fd_file);
	}
	game->map.first_line = ft_strdup(line);
	free(line);
}

char **copy_and_extend(char **original, int original_size) {
	// Allocate memory for the new array with one extra line
	char **new_array = malloc((original_size + 1) * sizeof(char *));
	if (!new_array) {
		return NULL;
	}
	// Copy the original array to the new array
	for (int i = 0; i < original_size; i++) {
		new_array[i] = ft_strdup(original[i]);
		if (!new_array[i])
		{
			// Free already allocated memory in case of failure
			for (int j = 0; j < i; j++)
				free(new_array[j]);
			free(new_array);
			return NULL;
		}
	}
	// Allocate memory for the new line and set it to NULL
	new_array[original_size] = NULL;
	// Free the original array
	for (int i = 0; i < original_size; i++) {
		free(original[i]);
	}
	free(original);
	return new_array;
}

void ft_get_map(t_game *game)
{
	int i;
	char *line;
	bool empty_line_found = false;

	i = 0;
	game->map.map = malloc(sizeof (char *));
	line = ft_strdup(game->map.first_line);
	free(game->map.first_line);
	while (line != NULL)
	{
		if (ft_check_empty_line_between(line))
			empty_line_found = true;
		else
		{
			if (empty_line_found)
			{
				printf("Error: Non-empty line found after an empty line!\n"); //TODO change to function to print an exits
				exit(1);
			}
			game->map.map[i] = ft_strdup(line);
			game->map.map = copy_and_extend(game->map.map, game->map.height + 1);
		}
		game->map.height++;
		i++;
		free(line);
		line = get_next_line(game->fd_file);
	}
}

static void ft_init_struct(t_game *game, char *file)
{
	free(game);
	game = malloc(sizeof(t_game));
	if (!game)
		exit(1);
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->fd_file = open(file, O_RDONLY);
	ft_get_textures(game);
	ft_get_map(game);
//	game->map.map = NULL;
	game->map.height = 0;
	game->map.length = 0;
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	ft_check_args(ac);
	is_cub_file(av[1]);
	file_exist(av[1]);
	ft_init_struct(game, av[1]);
//	ft_check_map(game, av);
//	init_game(game);
//	open_window(game);
//	free_map(game);
}
