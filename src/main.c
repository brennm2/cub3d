/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/10 14:47:07 by bsousa-d         ###   ########.fr       */
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

	dot_position = ft_strrchr(argv, '.');
	if (dot_position)
		if (ft_strcmp(dot_position, ".cub") == 0)
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

static void file_exist(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		printf("Error: File does not exist!\n");
		exit(1);
	}
}


int	main(int ac, char **av)
{
	t_game	*game;

	ft_check_args(ac);
	is_cub_file(av[1]);
	file_exist(av[1]);
	game = malloc(sizeof (t_game));
	if(game == NULL)
		return 1;
	ft_init_struct(game, av[1]);
//	ft_check_map(game, av);
//	init_game(game);
//	open_window(game);
	free_map(game);
	free(game->map.SOUTH_PATH);
	free(game->map.WEST_PATH);
	free(game->map.EAST_PATH);
	free(game->map.CEILING_PATH);
	free(game->map.FLOOR_PATH);
	free(game);

}
