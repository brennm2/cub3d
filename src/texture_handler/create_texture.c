// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   create_texture.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/11 10:55:25 by bde-souz          #+#    #+#             */
// /*   Updated: 2024/09/26 10:25:56 by bde-souz         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include    "../../includes/cub3d.h"

// int	create_north_texture(t_game *game)
// {
// 	game->texture[0]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/north_wall.xpm", &game->texture[0]->w,
// 			&game->texture[0]->h);
// 	if (!game->texture[0]->img->mlx_img)
// 	{
// 		printf("\nNo texture created(NORTH)\n\n");
// 		return (1);
// 	}
// 	game->texture[0]->img->addr = mlx_get_data_addr(
// 		game->texture[0]->img->mlx_img, &game->texture[0]->img->bpp,
// 			&game->texture[0]->img->line_len,
// 				&game->texture[0]->img->endian);
// 	if (!game->texture[0]->img->addr)
// 	{
// 		printf("\nNo texture addr created(NORTH)\n\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	create_south_texture(t_game *game)
// {
// 	game->texture[1]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/south_wall.xpm", &game->texture[1]->w,
// 			&game->texture[1]->h);
// 	if (!game->texture[1]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (south)\n\n");
// 		return (1);
// 	}
// 	game->texture[1]->img->addr = mlx_get_data_addr(
// 			game->texture[1]->img->mlx_img, &game->texture[1]->img->bpp,
// 				&game->texture[1]->img->line_len,
// 					&game->texture[1]->img->endian);
// 	if (!game->texture[1]->img->addr)
// 	{
// 		printf("\nNo texture addr created(SOUTH)\n\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	create_east_texture(t_game *game)
// {
// 	game->texture[2]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/east_wall.xpm", &game->texture[2]->w,
// 			&game->texture[2]->h);
// 	if (!game->texture[2]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (EAST)\n\n");
// 		return (1);
// 	}
// 	game->texture[2]->img->addr = mlx_get_data_addr(
// 			game->texture[2]->img->mlx_img, &game->texture[2]->img->bpp,
// 				&game->texture[2]->img->line_len,
// 					&game->texture[2]->img->endian);
// 	if (!game->texture[2]->img->addr)
// 	{
// 		printf("\nNo texture addr created(EAST)\n\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	create_west_texture(t_game *game)
// {
// 	game->texture[3]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/west_wall.xpm", &game->texture[3]->w,
// 			&game->texture[3]->h);
// 	if (!game->texture[3]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (WEST)\n\n");
// 		return (1);
// 	}
// 	game->texture[3]->img->addr = mlx_get_data_addr(
// 			game->texture[3]->img->mlx_img, &game->texture[3]->img->bpp,
// 				&game->texture[3]->img->line_len,
// 					&game->texture[3]->img->endian);
// 	if (!game->texture[3]->img->addr)
// 	{
// 		printf("\nNo texture addr created(WEST)\n\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	create_door_texture (t_game *game)
// {
// 	game->texture[4]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/door.xpm", &game->texture[4]->w,
// 			&game->texture[4]->h);
// 	if (!game->texture[4]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (DOOR)\n\n");
// 		return (1);
// 	}
// 	game->texture[4]->img->addr = mlx_get_data_addr(
// 			game->texture[4]->img->mlx_img, &game->texture[4]->img->bpp,
// 				&game->texture[4]->img->line_len,
// 					&game->texture[4]->img->endian);
// 	if (!game->texture[4]->img->addr)
// 	{
// 		printf("\nNo texture addr created(DOOR)\n\n");
// 		return (1);
// 	}


// 	game->texture[5]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/door_mid.xpm", &game->texture[5]->w,
// 			&game->texture[5]->h);
// 	if (!game->texture[5]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (MID_DOOR)\n\n");
// 		return (1);
// 	}
// 	game->texture[5]->img->addr = mlx_get_data_addr(
// 			game->texture[5]->img->mlx_img, &game->texture[5]->img->bpp,
// 				&game->texture[5]->img->line_len,
// 					&game->texture[5]->img->endian);
// 	if (!game->texture[5]->img->addr)
// 	{
// 		printf("\nNo texture addr created(MID_DOOR)\n\n");
// 		return (1);
// 	}


// 	game->texture[6]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/door_side.xpm", &game->texture[6]->w,
// 			&game->texture[6]->h);
// 	if (!game->texture[6]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (door_side)\n\n");
// 		return (1);
// 	}
// 	game->texture[6]->img->addr = mlx_get_data_addr(
// 			game->texture[6]->img->mlx_img, &game->texture[6]->img->bpp,
// 				&game->texture[6]->img->line_len,
// 					&game->texture[6]->img->endian);
// 	if (!game->texture[6]->img->addr)
// 	{
// 		printf("\nNo texture addr created(door_side)\n\n");
// 		return (1);
// 	}


// 	game->texture[7]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/handmap.xpm", &game->texture[7]->w,
// 			&game->texture[7]->h);
// 	if (!game->texture[7]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (hand_map)\n\n");
// 		return (1);
// 	}
// 	game->texture[7]->img->addr = mlx_get_data_addr(
// 			game->texture[7]->img->mlx_img, &game->texture[7]->img->bpp,
// 				&game->texture[7]->img->line_len,
// 					&game->texture[7]->img->endian);
// 	if (!game->texture[7]->img->addr)
// 	{
// 		printf("\nNo texture addr created(hand_map)\n\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	create_texture_all(t_game *game, int index)
// {
// 	game->texture[index]->img->mlx_img = mlx_xpm_file_to_image(
// 		game->mlx_ptr, "sprites/door_mid.xpm", &game->texture[index]->w,
// 			&game->texture[index]->h);
// 	if (!game->texture[index]->img->mlx_img)
// 	{
// 		printf("\nNo texture created (%d)\n\n", index);
// 		return (1);
// 	}
// 	game->texture[index]->img->addr = mlx_get_data_addr(
// 			game->texture[index]->img->mlx_img, &game->texture[index]->img->bpp,
// 				&game->texture[index]->img->line_len,
// 					&game->texture[index]->img->endian);
// 	if (!game->texture[index]->img->addr)
// 	{
// 		printf("\nNo texture addr created(%d)\n\n", index);
// 		return (1);
// 	}
// 	return (0);
// }

// void	create_texture(t_game *game)
// {
// 	if (create_north_texture(game) == 1)
// 		ft_quit_game(game);
// 		//#TODO free_all func
// 	if (create_south_texture(game) == 1)
// 		ft_quit_game(game);
// 		//#TODO free_all func
// 	if (create_east_texture(game) == 1)
// 		ft_quit_game(game);
// 		//#TODO free_all func
// 	if (create_west_texture(game) == 1)
// 		ft_quit_game(game);
// 		//#TODO free_all func

// 	create_door_texture(game);
// 	//create_texture_all(game, 6);
// }
