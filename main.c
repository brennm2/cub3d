/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/18 18:57:36 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_window(t_game *game)
{
	game->mlx_ptr= mlx_init();
	game->win_ptr= NULL;
	game->texture = ft_calloc(sizeof(t_texture), 4);
	game->fps = ft_calloc(sizeof(t_fps), 1);
  	for (int i = 0; i < 6; i++)
	{
        game->texture[i] = ft_calloc(1, sizeof(t_texture));
        game->texture[i]->h = 64;
        game->texture[i]->w = 64;
        game->texture[i]->img = ft_calloc(1, sizeof(t_img));
    }
}

void	display_window(t_game *game)
{
	if(game->mlx_ptr == NULL)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if(game->win_ptr == NULL)
		return ;
}

void draw_box(t_game *game, int pos_y, int pos_x, long color)
{
    int x;
    int y = pos_y + 1;

    while (y < pos_y + 20)
    {
        x = pos_x + 1; // Iniciar x na posição correta
        while (x < pos_x + 20)
        {
            better_mlx_pixel_put(&game->img, x, y, color);
            x++;
        }
        y++;
    }
}

// void	minimap_background(t_game *game)
// {
// 	int	x = 0;
// 	int y = 0;
	
// }

void	minimap(t_game *game)
{
	int y = 0;
	int x = 0;
	int step_y = (SCREEN_HEIGHT / 2) - ((game->map.height * 20)/ 2);
	int step_x = SCREEN_WIDTH / 2;
	int	player_step_x = (int)game->player.player_x * 20 + (SCREEN_HEIGHT / 2)- ((game->map.height * 20)/ 2);
	int	player_step_y = (int)game->player.player_y * 20 + (SCREEN_WIDTH / 2);
	
	
	while(y < game->map.height)
	{
		while(game->map.map[y][x])
		{
			if (game->map.map[y][x] == '1')
				draw_box(game, step_y, step_x, 7995649);
			else if (game->map.map[y][x] == '0')
				draw_box(game, step_y, step_x, 5263440);
			else if (game->map.map[y][x] == 'D' || game->map.map[y][x] == 'i')
				draw_box(game, step_y, step_x, 15118117);
			else if (game->map.map[y][x] == 'd' || game->map.map[y][x] == 'i')
				draw_box(game, step_y, step_x, 5061133);
			draw_box(game, player_step_x, player_step_y, 90000);
			step_x += 20;
			if (game->map.map[y][x] == '\n')
			{
				step_x = SCREEN_WIDTH / 2;
				break;
			}
			x++;
		}
		step_y += 20;
		y++;
		x = 0;
	}
}

int	game_frame_loop(t_game *game)
{
	if (game->img && game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	game->img->mlx_img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->mlx_img, &game->img->bpp, &game->img->line_len, &game->img->endian);
	shoot_rays(game);
	// Calcula FPS
	show_fps_debug(game);
	//-------------
	if (game->map.show_minimap == true)
		minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0, 0);
	//mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	return (0);
}

int	key_release(int key, t_game *game)
{
	(void)key;
	if (key == 'm')
	{
		game->map.show_minimap = false;
	}
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
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
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

	ft_check_args(ac);
	is_cub_file(av[1]);
	file_exist(av[1]);
	game = ft_init_structs(av[1]);
	init_player(game, game->player);
	init_window(game);
	init_game_data(game);
	create_texture(game);
	open_window(game);
}
