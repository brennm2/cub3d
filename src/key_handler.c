/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:14:31 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/30 16:14:07 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../header/cub3d.h"

int	key_handler(int key, t_game *game)
{
	(void)game;
	if (key == XK_Escape)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		ft_quit_game(game);
	}
	if (key == 'w')
		printf("moveup\n");//test_move_up(game);
	if (key == 's')
		printf("movedown\n");//test_move_down(game);
	if (key == 'a')
		printf("moveleft\n");//test_move_left(game);
	if (key == 'd')
		printf("moveright\n");//test_move_right(game);
	if (key == XK_Left)
		printf("looked left\n");
	if (key == XK_Right)
		printf("looked right\n");
	return (0);
}

int	ft_quit_game(t_game *game)
{
	//get_next_line(-1);
	free_all(game);
	exit (0);
}