/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:37 by bsousa-d          #+#    #+#             */
/*   Updated: 2024/09/30 15:30:25 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	ft_check_args(const int ac)
{
	if (ac != 2)
	{
		if (ac > 2)
			printf("Error: Too Many Arguments!\n");
		if (ac < 2)
			printf("Error: Not Enough Arguments!\n");
		exit(1);
	}
}

bool	is_cub_file(const char *argv)
{
	char	*dot_position;

	dot_position = ft_strrchr(argv, '.');
	if (dot_position)
		if (ft_strcmp(dot_position, ".cub") == 0)
			if (dot_position > argv && *(dot_position - 1) != '/')
				return (true);
	printf("Error: File not valid!\n");
	exit(1);
}

void	file_exist(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: File does not exist!\n");
		exit(1);
	}
}
