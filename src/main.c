/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/03 14:11:52 by bsousa-d         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_game	*game;
	int	fd;

	(void)fd;
	(void)ac;
	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	//if(ac == 2 && syntax_error(av[1]))
	//{
	ft_check_map(game, av);
	init_game(game);
	game->map_name = av[1];
	printf("map name: %s\n", game->map_name);
	//}
	// --read_map func--
	
	open_window(game);
}
