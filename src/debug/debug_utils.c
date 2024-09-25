/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:41:32 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/25 14:14:13 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	show_fps_debug(void)
{
	static clock_t	old_time = 0;
	clock_t			time;
	clock_t			frametime;
	double			fps;

	time = clock();
	frametime = time - old_time;
	old_time = time;
	ft_putstr_fd("\rFPS:", 1);
	if (frametime > 0)
		fps = CLOCKS_PER_SEC / (double)frametime;
	else
		fps = 0.0;
	if (fps >= 36)
		ft_putnbr_fd(fps, 1);
	else if (fps <= 34)
		ft_putnbr_fd(fps, 1);
	else
		ft_putnbr_fd(fps, 1);
}
