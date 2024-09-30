/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsousa-d <bsousa-d@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:14:52 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/27 16:04:54 by bsousa-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_color_check(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]) && !(str[i][j] == ','
				|| str[i][j] == ' '))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	has_trailing_text_after_empty_line(const char *line, bool found_empty)
{
	return (found_empty && !ft_check_empty_line(line, 2));
}

void	validate_map_line(t_game *game)
{
	if (!has_valid_chars(game->map.line, " 10NSWE\n"))
	{
		game->map.map[game->map.height] = NULL;
		printf("Invalid character!\n");
		ft_quit_game(game);
	}
	game->map.map[game->map.height] = ft_strdup(game->map.line);
	game->map.height++;
	game->map.map[game->map.height] = NULL;
	ft_extend_map(game);
}
