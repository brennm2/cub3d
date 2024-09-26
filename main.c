/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/26 12:02:50 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_window(t_game *game)
{
	game->mlx_ptr= mlx_init();
	game->win_ptr= NULL;
	game->texture = ft_calloc(sizeof(t_texture), 4);
	game->fps = ft_calloc(sizeof(t_fps), 1);
  	for (int i = 0; i < 8; i++)
	{
        game->texture[i] = ft_calloc(1, sizeof(t_texture));
        game->texture[i]->h = 64;
        game->texture[i]->w = 64;
        game->texture[i]->img = ft_calloc(1, sizeof(t_img));
    }
	game->mouse_x = ft_calloc(sizeof(int *), 1);
	game->mouse_y = ft_calloc(sizeof(int *), 1);
}

void	display_window(t_game *game)
{
	if(game->mlx_ptr == NULL)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if(game->win_ptr == NULL)
		return ;
}

int	game_frame_loop(t_game *game)
{
	if (game->img && game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	game->img->mlx_img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->mlx_img, &game->img->bpp, &game->img->line_len, &game->img->endian);
	shoot_rays(game);
	if (game->map.show_minimap == true)
		minimap(game);
	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, game->mouse_x, game->mouse_y);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	mouse_direction(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0, 0);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 'm')
		game->map.show_minimap = false;
	return (0);
}

void	open_window(t_game *game)
{
	display_window(game);
	if (!game->win_ptr)
		return ;
	mlx_loop_hook(game->mlx_ptr, &game_frame_loop, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_handler, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
		&ft_quit_game, game);
	//mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_loop(game->mlx_ptr);
}

void	init_game_data(t_game *game)
{
	(void)game;
	// game->dirx = 0;
	// game->diry = 1;
	// game->plane_x = 0.66;
	// game->plane_y = 0;
}

void	init_player(t_game *game, t_player player)
{
	game->player_in_map_x = 14; //DEBUG
	game->player_in_map_y = 3; //DEBUG
	(void)player;
	// player->player_x = game->player_in_map_x * BLOCK_SIZE + BLOCK_SIZE/2;
	// player->player_y = game->player_in_map_y * BLOCK_SIZE + BLOCK_SIZE/2;
	//player->fov_radian = (FOV * M_PI) / 180;
	//player->angle = M_PI;
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

// t_game	*init_game(void)
// {
// 	t_game	*game;
//
//
// 	init_player(game, game->player);
// 	init_window(game);
// 	init_game_data(game);
// 	return (game);
// }

int	main(int ac, char **av)
{
	t_game	*game;

static void	ft_check_file(const int ac, char **av)
{
	ft_check_args(ac);
	is_cub_file(av[1]);
	file_exist(av[1]);
}

//TODO map too long its not working
//TODO remove make norm from makefile

int	main(const int ac, char **av)
{
	t_game	*game;

	ft_check_file(ac, av);
	game = ft_init_structs(av[1]);
	init_game(game);
}
