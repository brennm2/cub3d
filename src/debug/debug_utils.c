/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:46:29 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/27 13:51:05 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes//cub3d.h"

void	show_map(const t_game *game)
{
	int	i;

	i = 0;
	printf("map name: %s\n", game->map_name);
	while (i < game->map.height)
	{
		ft_printf("%s", game->map.map[i]);
		i++;
	}
}
