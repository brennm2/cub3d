/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/24 14:17:14 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void ft_check_file(const int ac, char **av)
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
