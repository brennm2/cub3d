/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/02 18:07:34 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/cub3d.h"

void	init_window(t_game *game)
{
	game->mlx_ptr= mlx_init();
	game->win_ptr= NULL;
	//game->img = malloc(sizeof(t_img));
	//if (!game->img)
	//	return ;
	game->img = malloc(sizeof(t_img));
	game->img->mlx_img = NULL;
	game->img->addr = NULL;
	game->img->bpp = 0;
	game->img->line_len = 0;
	game->img->endian = 0;
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
	//t_game	*game;

	//game = temp_game;
	if (game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img);
	game->img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	//playermove
	//castrays
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
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
	//game->map_name = NULL;
	// game->map_h = 0;
	// game->map_w = 0;
	// game->player_map_x = 0;
	// game->player_map_y = 0;

}

void	init_player(t_game *game, t_player *player)
{
	player->player_x = game->player_in_map_x * BLOCK_SIZE + BLOCK_SIZE/2;
	player->player_y = game->player_in_map_y * BLOCK_SIZE + BLOCK_SIZE/2;
	player->fov_radian = (FOV * M_PI) / 180;
	player->angle = M_PI;
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
	//game->img = malloc(sizeof(t_img));
	//if (!game->img)
	//	return (NULL);


	//init_game_data(game);
	init_player(game, game->player);
	init_window(game);
	return (game);
}



int	main(int ac, char **av)
{
	t_game	*game;
	int	fd;
	
	(void)fd;
	(void)ac;
	(void)av;
	game = NULL;
	//if(ac == 2 && syntax_error(av[1]))
	//{
	game = init_game();
	if (!game)
		return (0);
	game->map_name = av[1];
	//read_map(av[1], game); //Read and fill the game->map
	//DEBUG --------------
	show_map(game);
	//DEBUG ------------
	//}
	// --read_map func--
	
	open_window(game);
}
