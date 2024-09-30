/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:44:29 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/30 15:31:00 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

bool	has_only_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	has_only_tabs(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

size_t	ft_count_char(const char *str, char find)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == find)
			count++;
		i++;
	}
	return (count);
}

int	ft_count_colours(char **colours)
{
	int	i;

	i = 0;
	while (colours[i])
		i++;
	return (i);
}

void	ft_check_color(t_game *game)
{
	ft_parse_and_set_color(game, game->map.ceiling_path,
		&game->map.ceiling_color, "CEILING");
	ft_parse_and_set_color(game, game->map.floor_path,
		&game->map.floor_color, "FLOOR");
}
