/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:25:56 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/25 13:29:20 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_vector(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	look_direction(t_game *game, const bool is_left)
{
	double	angle;

	if (is_left)
		angle = PLAYER_SENS;
	else
		angle = -PLAYER_SENS;
	rotate_vector(&game->dirx, &game->diry, angle);
	rotate_vector(&game->plane_x, &game->plane_y, angle);
}
