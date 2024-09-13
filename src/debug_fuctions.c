/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_fuctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:46:29 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/13 12:33:53 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//cub3d.h"

void	show_map(t_game *game)
{
	int	i;

	i = 0;
	printf("map name: %s\n", game->map_name);
	while(i < game->map.height)
	{
		ft_printf("%s", game->map.map[i]);
		i++;
	}
}