/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:49:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/30 15:33:08 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes_bonus/cub3d_bonus.h"

static void	ft_check_file(const int ac, char **av)
{
	ft_check_args(ac);
	is_cub_file(av[1]);
	file_exist(av[1]);
}

int	main(const int ac, char **av)
{
	t_game	*game;

	ft_check_file(ac, av);
	game = ft_init_structs(av[1]);
	init_game(game);
}
