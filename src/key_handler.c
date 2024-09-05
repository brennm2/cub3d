/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:14:31 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/05 14:29:25 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/cub3d.h"

int	key_handler(int key, t_game *game)
{
	(void)game;
	if (key == ESC)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		ft_quit_game(game);
	}
	if (key == W)
		printf("moveup\n");//test_move_up(game);
	if (key == S)
		printf("movedown\n");//test_move_down(game);
	if (key == A)
		printf("moveleft\n");//test_move_left(game);
	if (key == D)
		printf("moveright\n");//test_move_right(game);
	if (key == LEFT)
		printf("looked left\n");
	if (key == RIGHT)
		printf("looked right\n");
	return (0);
}

int	ft_quit_game(t_game *game)
{
	//get_next_line(-1);
	free_all(game);
	exit (0);
}