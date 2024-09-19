/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:14:31 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/19 11:15:16 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/cub3d.h"

void	move_up(t_game *game)
{
	double new_x;
	double new_y;

	new_x = game->player.player_x + game->dirx * PLAYER_SPEED;
	new_y = game->player.player_y + game->diry * PLAYER_SPEED;
	if (game->map.map[(int)new_x][(int)game->player.player_y] == '0' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'd')
		game->player.player_x = new_x;
	if (game->map.map[(int)game->player.player_x][(int)new_y] == '0' \
		|| game->map.map[(int)game->player.player_x][(int)new_y] == 'd')
		game->player.player_y = new_y;
}

void	move_down(t_game *game)
{
	double new_x;
	double new_y;

	new_x = game->player.player_x - game->dirx * PLAYER_SPEED;
	new_y = game->player.player_y - game->diry * PLAYER_SPEED;
	if (game->map.map[(int)new_x][(int)game->player.player_y] == '0' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'd')
		game->player.player_x = new_x;
	if (game->map.map[(int)game->player.player_x][(int)new_y] == '0' \
		|| game->map.map[(int)game->player.player_x][(int)new_y] == 'd')
		game->player.player_y = new_y;
}

void	move_right(t_game *game)
{
	double new_x;
	double new_y;

	new_x = game->diry * PLAYER_SPEED;
	new_y = -game->dirx * PLAYER_SPEED;
	if (game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == 'd')
		game->player.player_x += new_x;
	if (game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == 'd')
		game->player.player_y += new_y;
}

void	move_left(t_game *game)
{

	double new_x;
	double new_y;

	new_x = -game->diry * PLAYER_SPEED;
	new_y = game->dirx * PLAYER_SPEED;

	if (game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == 'd')
		game->player.player_x += new_x;
	if (game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0' \
		|| game->map.map[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == 'd')
		game->player.player_y += new_y;
}

void	look_direction(t_game *game, bool is_left)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dirx;
	old_plane_x = game->plane_x;
	if(!is_left)
	{
		game->dirx = game->dirx * cos(-PLAYER_SENS) - game->diry * sin(-PLAYER_SENS);
		game->diry = old_dir_x * sin(-PLAYER_SENS) + game->diry * cos(-PLAYER_SENS);
		game->plane_x = game->plane_x * cos(-PLAYER_SENS) - game->plane_y * sin(-PLAYER_SENS);
		game->plane_y = old_plane_x * sin(-PLAYER_SENS) + game->plane_y * cos(-PLAYER_SENS);
	}
	else
	{
		game->dirx = game->dirx * cos(PLAYER_SENS) - game->diry * sin(PLAYER_SENS);
		game->diry = old_dir_x * sin(PLAYER_SENS) + game->diry * cos(PLAYER_SENS);
		game->plane_x = game->plane_x * cos(PLAYER_SENS) - game->plane_y * sin(PLAYER_SENS);
		game->plane_y = old_plane_x * sin(PLAYER_SENS) + game->plane_y * cos(PLAYER_SENS);
	}
}

void	door_animation(t_game *game, int new_x, int new_y, bool in_y)
{
	game->new_x = new_x;
	game->new_y = new_y;
	game->ray->is_in_y = in_y ;

	if (in_y == false)
	{
		if (game->map.map[(int)game->player.player_x][(int)new_y] == 'D')
		{
			game->map.map[(int)game->player.player_x][(int)new_y] = 'i';
			game->ray->is_mid_door = true;
			game->ray->door_is_closing = false;
			
		}
		else if (game->map.map[(int)game->player.player_x][(int)new_y] == 'd')
		{
			game->ray->is_mid_door = true;
			game->ray->door_is_closing = true;
			game->map.map[(int)game->player.player_x][(int)new_y] = 'i';
		}
		ft_printf("open door X\n");
	}
	else
	{
		if (game->map.map[(int)new_x][(int)game->player.player_y] == 'D')
		{
			game->map.map[(int)new_x][(int)game->player.player_y] = 'i';
			game->ray->is_mid_door = true;
			game->ray->door_is_closing = false;
		}
		else if(game->map.map[(int)new_x][(int)game->player.player_y] == 'd')
		{
			game->ray->is_mid_door = true;
			game->ray->door_is_closing = true;
			game->map.map[(int)new_x][(int)game->player.player_y] = 'i';
		}
		ft_printf("open door Y\n");
		
	}
}

void	door_handler(t_game *game)
{
	double new_x;
	double new_y;

	new_x = game->player.player_x + game->dirx * (PLAYER_SPEED * 5);
	new_y = game->player.player_y + game->diry * (PLAYER_SPEED * 5);
	if (game->map.map[(int)new_x][(int)game->player.player_y] == 'D' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'd' \
		|| game->map.map[(int)new_x][(int)game->player.player_y] == 'i')
	{
		door_animation(game, new_x, new_y, true);
	}
	if (game->map.map[(int)game->player.player_x][(int)new_y] == 'D' \
		|| game->map.map[(int)game->player.player_x][(int)new_y] == 'd' ||
		game->map.map[(int)game->player.player_x][(int)new_y] == 'i')
	{
		door_animation(game, new_x, new_y, false);
	}
	show_map(game);
}

int	key_handler(int key, t_game *game)
{
	(void)game;
	if (key == ESC)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		ft_quit_game(game);
	}
	if (game->map.show_minimap == false)
	{
		if (key == 'w')
			move_up(game);
		if (key == 's')
			move_down(game);
		if (key == 'a')
			move_left(game);
		if (key == 'd')
			move_right(game);
		if (key == LEFT)
			look_direction(game, true);
		if (key == RIGHT)
			look_direction(game, false);
		if (key == 'e')
			door_handler(game);
	}
	if (key == 'm')
	{
		game->map.show_minimap = true;
	}
	return (0);
}

int	ft_quit_game(t_game *game)
{
	//get_next_line(-1);
	free_all(game);
	exit (0);
}