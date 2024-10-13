/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:24:42 by bde-souz          #+#    #+#             */
/*   Updated: 2024/10/13 19:25:09 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void calculate_ray_direction(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->raydir_x = game->dirx + game->plane_x * camera_x;
	ray->raydir_y = game->diry + game->plane_y * camera_x;
	ray->map_x = (int)game->player.player_x;
	ray->map_y = (int)game->player.player_y;
	if (ray->raydir_x == 0)
		ray->deltadist_x = 1e30;
	else
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = fabs(1 / ray->raydir_y);
}

void calculate_lines(t_game *game, t_ray *ray)
{
	int	line_height;

	line_height = (int)(SCREEN_HEIGHT / ray->distance);
	ray->line_height = line_height;
	ray->h_pixel = -line_height / 2 + (SCREEN_HEIGHT / 2) \
		+ ray->mouse_height;
	ray->l_pixel = line_height / 2 + (SCREEN_HEIGHT / 2) \
		+ ray->mouse_height;
	if (ray->h_pixel < 0)
		ray->h_pixel = 0;
	if (ray->l_pixel >= SCREEN_HEIGHT)
		ray->l_pixel = SCREEN_HEIGHT - 1;
}

void dda(t_game *game, t_ray *ray) {
    bool wall_hit = false;

    while (!wall_hit) {
        if (ray->raydist_x < ray->raydist_y) {
            ray->raydist_x += ray->deltadist_x;
            ray->map_x += ray->step_x;
            ray->side = false;
        } else {
            ray->raydist_y += ray->deltadist_y;
            ray->map_y += ray->step_y;
            ray->side = true;
        }
        wall_hit = check_wall_hit(game, ray);
    }
    if (!ray->side)
        ray->distance = (ray->raydist_x - ray->deltadist_x);
    else
        ray->distance = (ray->raydist_y - ray->deltadist_y);
}

void calculate_ray_steps(t_game *game, t_ray *ray) {
    if (ray->raydir_x < 0) {
        ray->step_x = -1;
        ray->raydist_x = (game->player.player_x - ray->map_x) * ray->deltadist_x;
    } else {
        ray->step_x = 1;
        ray->raydist_x = (ray->map_x + 1.0 - game->player.player_x) * ray->deltadist_x;
    }
    if (ray->raydir_y < 0) {
        ray->step_y = -1;
        ray->raydist_y = (game->player.player_y - ray->map_y) * ray->deltadist_y;
    } else {
        ray->step_y = 1;
        ray->raydist_y = (ray->map_y + 1.0 - game->player.player_y) * ray->deltadist_y;
    }
}

//pthread_barrier_t barrier;

void *thread_shoot_rays(void *arg) {
    t_thread_data *data = (t_thread_data *)arg;
    int x = data->start;

    while (x < data->end) {
        calculate_ray_direction(data->game, data->ray, x);
        calculate_ray_steps(data->game, data->ray);
        dda(data->game, data->ray);
        calculate_lines(data->game, data->ray);

        pthread_mutex_lock(&data->game->ray_mutex);
        if (data->game->map.show_minimap == false) {
            draw_floor_ceiling(data->game, x, data->ray->h_pixel, data->ray->l_pixel, data->ray);
            draw_wall(data->game, data->ray->h_pixel, data->ray->l_pixel, x, data->ray);
        }
        pthread_mutex_unlock(&data->game->ray_mutex);

        x++;
    }

    return NULL;
}

void init_ray(t_ray *ray) {
    ray->raydir_x = 0;
    ray->raydir_y = 0;
    ray->map_x = 0;
    ray->map_y = 0;
    ray->deltadist_x = 0;
    ray->deltadist_y = 0;
    ray->step_x = 0;
    ray->step_y = 0;
    ray->raydist_x = 0;
    ray->raydist_y = 0;
    ray->side = false;
    ray->distance = 0;
    ray->h_pixel = 0;
    ray->l_pixel = 0;
    ray->mouse_height = 0;
}

void init_threads(t_game *game) {
    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    int width_per_thread = SCREEN_WIDTH / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].game = game;
        thread_data[i].start = i * width_per_thread;
        thread_data[i].end = (i + 1) * width_per_thread;
        thread_data[i].ray = malloc(sizeof(t_ray)); // Alocar memória para t_ray
		init_ray(thread_data[i].ray);

        if (pthread_create(&threads[i], NULL, thread_shoot_rays, &thread_data[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        free(thread_data[i].ray); // Liberar memória alocada para t_ray
    }
}


void	shoot_rays(t_game *game)
{
	init_threads(game);
	// int	x;

	// x = 0;
	// while (x++ < SCREEN_WIDTH - 1)
	// {
	// 	calculate_ray_direction(game, x);
	// 	calculate_ray_steps(game);
	// 	dda(game);
	// 	calculate_lines(game);
	// 	if (game->map.show_minimap == false)
	// 	{
	// 		draw_floor_ceiling(game, x, game->ray->h_pixel, game->ray->l_pixel);
	// 		draw_wall(game, game->ray->h_pixel, game->ray->l_pixel, x);
	// 	}
	// }
}
