/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:00:35 by bde-souz          #+#    #+#             */
/*   Updated: 2024/09/10 15:36:45 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../header/cub3d.h"

// void	fill_map(int fd, t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	while (i < game->map_h)
// 	{
// 		game->map[i] = get_next_line(fd);
// 		i++;
// 	}
// }

int	count_lines(char *map_name)
{
	char	*tmp;
	int		rows;
	int		fd;

	rows = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nFailed to open the map!\n");
		return (-1);
	}
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		rows++;
		tmp = get_next_line(fd);
	}
	close(fd);
	free (tmp);
	return (rows);
}

// void	read_map(char *map_name, t_game *game)
// {
// 	int	fd;

// 	game->map_h = count_lines(map_name); //caunts how many rows the map have to alloc in the future
// 	if (game->map_h <= 0)
// 	{
// 		ft_printf("Error\nEmpty map! Check the map again...\n");
// 		ft_quit_game(game);
// 	}
// 	fd = open(map_name, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_printf("Error\nProblem with the map file!");
// 		return ;
// 	}
// 	game->map = malloc(sizeof(char *) * (game->map_h));
// 	if (!game->map)
// 		return ;
// 	fill_map (fd, game); // Fill the game->map
// 	game->map_w = 25; //#TODO map width (RIGHT)
// 	close (fd);
// }
