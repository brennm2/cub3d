/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/10 15:55:54 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"header/cub3d.h"

void	init_window(t_game *game)
{
	game->mlx_ptr= mlx_init();
	game->win_ptr= NULL;
	game->texture = ft_calloc(sizeof(t_texture), 2);
  	for (int i = 0; i < 2; i++) {
        game->texture[i] = ft_calloc(1, sizeof(t_texture));
        game->texture[i]->h = 64;
        game->texture[i]->w = 64;
        game->texture[i]->img = ft_calloc(1, sizeof(t_img));
    }
	//game->img = malloc(sizeof(t_img));
	//if (!game->img)
	//	return ;
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
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0, 0);
	//mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	return (0);
}

void	open_window(t_game *game)
{
	display_window(game);
	if (!game->win_ptr)
		return ;
	mlx_loop_hook(game->mlx_ptr, &game_frame_loop, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_handler, game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
		&ft_quit_game, game);
	mlx_loop(game->mlx_ptr);
}

void	init_game_data(t_game *game)
{
	(void)game;
	game->dirx = -1;
	game->diry = 0;
	game->plane_x = 0;
	game->plane_y = 0.66;
	game->pos_x = 7;
	game->pos_y = 2;
}

void	init_player(t_game *game, t_player *player)
{
	game->player_in_map_x = 14; //DEBUG
	game->player_in_map_y = 3; //DEBUG
	player->player_x = game->player_in_map_x * BLOCK_SIZE + BLOCK_SIZE/2;
	player->player_y = game->player_in_map_y * BLOCK_SIZE + BLOCK_SIZE/2;
	//player->fov_radian = (FOV * M_PI) / 180;
	//player->angle = M_PI;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(sizeof(t_game), 1);
	//game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (!game->ray)
		return (NULL);
	game->player = (t_player *)ft_calloc(sizeof(t_player), 1);
	if (!game->player)
		return (NULL);
	game->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (!game->img)
		return (NULL);

	init_player(game, game->player);
	init_window(game);
	init_game_data(game);
	return (game);
}

void	debug_create_texture(t_game *game)
{
	//texture 0 = N
	game->texture[0]->img->mlx_img = mlx_xpm_file_to_image(
			game->mlx_ptr, game->map.NORTH_PATH, &game->texture[0]->w,
				&game->texture[0]->h);
	game->texture[0]->img->addr = mlx_get_data_addr(
			game->texture[0]->img->mlx_img, &game->texture[0]->img->bpp,
				&game->texture[0]->img->line_len,
					&game->texture[0]->img->endian);
	
	//texture 1 = S
	game->texture[1]->img->mlx_img = mlx_xpm_file_to_image(
			game->mlx_ptr, game->map.SOUTH_PATH, &game->texture[1]->w,
				&game->texture[1]->h);
	game->texture[1]->img->addr = mlx_get_data_addr(
			game->texture[1]->img->mlx_img, &game->texture[1]->img->bpp,
				&game->texture[1]->img->line_len,
					&game->texture[1]->img->endian);

	
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
	game = init_game();
	ft_init_struct(game, av[1]);
	if (!game)
		return (0);
	//if(ac == 2 && syntax_error(av[1]))
	//{
	// ft_check_map(game, av);
	//printf("Hello\n");
	//init_game(game);
	game->map_name = av[1];
	//read_map(av[1], game); //Read and fill the game->map
	//DEBUG --------------
	//show_map(game);
	//DEBUG ------------
	//}
	// --read_map func--
	debug_create_texture(game);
	open_window(game);
}
