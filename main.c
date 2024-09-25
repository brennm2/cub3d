/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/25 15:47:34 by bde-souz         ###   ########.fr       */
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

void	create_minimap_background(t_game *game)
{
	int	*x_p;
	int	*y_p;

	x_p = (int *)SCREEN_HEIGHT;
	y_p = (int *)SCREEN_WIDTH;
	if (game->img && game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	game->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
		"sprites/handmap.xm", x_p, y_p);
	if (!game->img->mlx_img)
	{
		printf("\nNo texture created (hand_map)\n\n");
		ft_quit_game(game);
	}
	game->img->addr = mlx_get_data_addr(game->img->mlx_img, &game->img->bpp, \
		&game->img->line_len, &game->img->endian);
	if (!game->img->addr)
	{
		printf("\nNo texture addr created(hand_map)\n\n");
		ft_quit_game(game);
	}
}

void	minimap(t_game *game, int *x_p, int *y_p)
{
	int y = 0;
	int x = 0;
	int step_y = (SCREEN_HEIGHT / 2) - ((game->map.height * 20)/ 2);
	int step_x = SCREEN_WIDTH / 2;
	int	player_step_x = (int)game->player.player_x * 20 + (SCREEN_HEIGHT / 2)- ((game->map.height * 20)/ 2);
	int	player_step_y = (int)game->player.player_y * 20 + (SCREEN_WIDTH / 2);
	
	
	create_minimap_background(game);
	// if (game->img && game->img->mlx_img)
	// 	mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	// game->img->mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, "sprites/handmap.xm", x_p, y_p);
	// game->img->addr = mlx_get_data_addr(game->img->mlx_img, &game->img->bpp, &game->img->line_len, &game->img->endian);
	// if (!game->img->mlx_img)
	// {
	// 	printf("minimap image dead\n");
	// 	ft_quit_game(game);
	// }
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

void	mouse_direction(t_game *game)
{
	int center_x = (SCREEN_WIDTH / 2);
	int	center_y = (SCREEN_HEIGHT / 2);
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dirx;
	old_plane_x = game->plane_x;
	(void)center_y;
	if (*game->mouse_x - center_x < -10)
	{
		game->dirx = game->dirx * cos(MOUSE_SENS) - game->diry * sin(MOUSE_SENS);
		game->diry = old_dir_x * sin(MOUSE_SENS) + game->diry * cos(MOUSE_SENS);
		game->plane_x = game->plane_x * cos(MOUSE_SENS) - game->plane_y * sin(MOUSE_SENS);
		game->plane_y = old_plane_x * sin(MOUSE_SENS) + game->plane_y * cos(MOUSE_SENS);
		
	}
	else if (*game->mouse_x - center_x > 10)
	{
		game->dirx = game->dirx * cos(-MOUSE_SENS) - game->diry * sin(-MOUSE_SENS);
		game->diry = old_dir_x * sin(-MOUSE_SENS) + game->diry * cos(-MOUSE_SENS);
		game->plane_x = game->plane_x * cos(-MOUSE_SENS) - game->plane_y * sin(-MOUSE_SENS);
		game->plane_y = old_plane_x * sin(-MOUSE_SENS) + game->plane_y * cos(-MOUSE_SENS);
	}
	if (*game->mouse_y - center_y < -10)
	{
		game->ray->mouse_height += MOUSE_PITCH;
		if (game->ray->mouse_height >= 300)
			game->ray->mouse_height = 300;
	}
	else if (*game->mouse_y - center_y > 10)
	{
		game->ray->mouse_height -= MOUSE_PITCH;
		if (game->ray->mouse_height <= -300)
			game->ray->mouse_height = -300;
	}
}

int	game_frame_loop(t_game *game)
{
	int x = SCREEN_WIDTH;
	int y = SCREEN_HEIGHT;

	if (game->img && game->img->mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	game->img->mlx_img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->mlx_img, &game->img->bpp, &game->img->line_len, &game->img->endian);
	shoot_rays(game);
	// Calcula FPS
	//show_fps_debug(game);
	//-------------
	if (game->map.show_minimap == true)
		minimap(game, &x, &y);
	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, game->mouse_x, game->mouse_y);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	mouse_direction(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->mlx_img, 0, 0);
	//mlx_destroy_image(game->mlx_ptr, game->img->mlx_img);
	return (0);
}

int	key_release(int key, t_game *game)
{
	(void)key;
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
